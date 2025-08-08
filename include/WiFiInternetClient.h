#pragma once

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "IInternetClient.h"
#include "constants.h"

class WiFiInternetClient : public IInternetClient
{
private:
    // This class now OWNS the secure client object.
    WiFiClientSecure _secureClient; 

    void _connectToWiFi();
    void _configureCertificates();

public:
    // The constructor is now responsible for setup.
    WiFiInternetClient();

    void connect() override;
    bool isConnected() override;
    Client& getClient() override;
};
