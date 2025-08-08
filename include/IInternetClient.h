#pragma once

// Include the base Client class from the Arduino core library
#include <Client.h>

class IInternetClient
{
public:
    virtual ~IInternetClient() {}

    // Connects the device to the internet (e.g., Wi-Fi, Cellular)
    virtual void connect() = 0;

    // Checks if the internet connection is active
    virtual bool isConnected() = 0;

    // Provides access to the underlying client object (e.g., WiFiClientSecure)
    // for use by other libraries like PubSubClient. This is the key to decoupling.
    virtual Client& getClient() = 0;
};
