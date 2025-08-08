#include "AWSIoTMqttClient.h"
#include "IInternetClient.h"

AWSIoTMqttClient::AWSIoTMqttClient(IInternetClient &internetClient, const char *endpoint, int port)
    : _mqttClient(internetClient.getClient()), _endpoint(endpoint), _port(port)
{
}

// Destructor implementation
AWSIoTMqttClient::~AWSIoTMqttClient()
{
}

// connect() method implementation
void AWSIoTMqttClient::connect(const char *clientId)
{
    _mqttClient.setServer(_endpoint, _port);

    // Loop until we're reconnected
    if (!_mqttClient.connected())
    {
        Serial.println("Attempting AWS IoT MQTT connection...");

        // Attempt to connect
        if (_mqttClient.connect(clientId))
        {
            Serial.println("AWS IoT Connected!");
        }
        else
        {
            Serial.print("Failed to connect, rc=");
            Serial.print(_mqttClient.state());
            Serial.println(" Try again in 5 seconds");
        }
    }
}

bool AWSIoTMqttClient::isConnected()
{
    return _mqttClient.connected();
}

void AWSIoTMqttClient::loop()
{
    // This is crucial to maintain the connection and check for incoming messages
    if (isConnected())
    {
        _mqttClient.loop();
    }
}

bool AWSIoTMqttClient::publish(const char *topic, const char *payload)
{
    if (!isConnected())
    {
        Serial.println("Cannot publish, MQTT client not connected.");
        return false;
    }
    return _mqttClient.publish(topic, payload);
}
