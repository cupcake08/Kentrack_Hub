#pragma once

#include <PubSubClient.h>
#include "IMqttClient.h"
#include "IInternetClient.h"

// // Forward declaration for the interface it depends on
// class IInternetClient;

class AWSIoTMqttClient : public IMqttClient
{
private:
    // The actual MQTT client library instance. It holds a reference
    // to a generic Client, not a specific type.
    PubSubClient _mqttClient;
    
    // Connection details
    const char* _endpoint;
    int _port;

public:
    // Constructor for dependency injection.
    // It now correctly depends ONLY on the IInternetClient abstraction.
    AWSIoTMqttClient(IInternetClient& internetClient, const char* endpoint, int port);

    // Destructor
    ~AWSIoTMqttClient() override;

    // Public interface methods (implementations are in the .cpp file)
    void connect(const char* clientId) override;
    bool isConnected() override;
    void loop() override;
    bool publish(const char* topic, const char* payload) override;
};
