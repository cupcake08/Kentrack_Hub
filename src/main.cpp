/**********************************************************************************
 * ESP32-S3 CAN to AWS IoT Gateway - Main Application
 *
 * This version uses a highly abstracted architecture where hardware details
 * for the CAN bus and Internet connectivity are encapsulated in their
 * own classes. The main file only deals with high-level orchestration.
 **********************************************************************************/

 #include <Arduino.h>
 #include <ArduinoJson.h>
 
 // --- Core Application Abstractions & Implementations ---
 #include "constants.h"
 #include "ICanController.h"
 #include "MCP2515Controller.h"
 #include "IInternetClient.h"
 #include "IMqttClient.h"
 #include "WiFiInternetClient.h"
 #include "SimInternetClient.h"
 #include "AWSIoTMqttClient.h"
 
 // --- Global Objects (Pointers to abstractions) ---
 ICanController* canController;
 IInternetClient* internetClient;
 IMqttClient* mqttClient;
 
 // --- Global Data Structures ---
 CanFrame canFrame; // A generic struct to hold the CAN data
 
 void setup() {
     Serial.begin(115200);
     Serial.println("--- Abstracted CAN to AWS IoT Gateway Starting ---");
 
     // =================================================================
     // == Composition Root: Instantiate and inject all dependencies.  ==
     // =================================================================
     
     // 1. Create the CAN Controller object, providing hardware pins.
     canController = new Mcp2515Controller(5, 12, 13, 11); // CS, SCK, MISO, MOSI
 
     // 2. Create the Internet Client object.
     // --- Option 1: Use SIM/Cellular Client (Currently Active) ---
     // Provide RX, TX pins for the modem and baud rate.
     // For ESP32, Serial2 is often on GPIO 16 (RX) and 17 (TX).
    //  internetClient = new SimInternetClient(16, 17, 115200); 
     
     // --- Option 2: Use Wi-Fi Client ---
     internetClient = new WiFiInternetClient();
 
     // 3. Inject the chosen internet client into our MQTT client.
     mqttClient = new AWSIoTMqttClient(*internetClient, AWS_IOT_ENDPOINT, AWS_IOT_PORT);
     // =================================================================
 
     // Initialize the CAN controller hardware.
     if (!canController->begin()) {
         Serial.println("Halting due to CAN controller initialization failure.");
         while(1);
     }
 
     // Connect to the internet.
     Serial.println("Initializing Internet Connection...");
     internetClient->connect();
 }
 
 void loop() {
     if (!internetClient->isConnected()) {
         Serial.println("Internet disconnected. Attempting to reconnect...");
         internetClient->connect();
         delay(5000);
         return;
     }
 
     if (!mqttClient->isConnected()) {
         Serial.println("MQTT client disconnected. Attempting to reconnect...");
         String clientId = "esp32-s3-can-gateway-";
         clientId += String(random(0xffff), HEX);
         mqttClient->connect(clientId.c_str());
         delay(1000);
     }
 
     mqttClient->loop();
 
     // Read from the CAN bus using our abstracted controller.
     if (canController->readMessage(canFrame)) {
         // Create a JSON payload and publish it.
         JsonDocument doc;
         doc["can_id"] = canFrame.id;
         doc["dlc"] = canFrame.len;
         doc["timestamp"] = millis();
         JsonArray data = doc["data"].to<JsonArray>();
         for (int i = 0; i < canFrame.len; i++) {
             data.add(canFrame.data[i]);
         }
         char jsonBuffer[256];
         serializeJson(doc, jsonBuffer);
         
         if (mqttClient->publish(AWS_IOT_TOPIC, jsonBuffer)) {
             Serial.print("Published to AWS: ");
             Serial.println(jsonBuffer);
         } else {
             Serial.println("Failed to publish message to AWS!");
         }
     }
 }
 