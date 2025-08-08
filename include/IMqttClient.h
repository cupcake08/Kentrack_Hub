#pragma once

class IMqttClient
{
public:
    virtual ~IMqttClient() {}
    virtual void connect(const char *clientId) = 0;
    virtual bool isConnected() = 0;
    virtual void loop() = 0;
    virtual bool publish(const char *topic, const char *payload) = 0;
};