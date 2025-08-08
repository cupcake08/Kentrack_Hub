#pragma once

#include "modem_config.h"
#include "IInternetClient.h"
#include "constants.h"

#include <HardwareSerial.h>
#include <TinyGsmClient.h> 
#include <SSLClient.h>
#include <memory>

class SimInternetClient : public IInternetClient
{
private:
    HardwareSerial* _modemSerial;
    TinyGsm* _modem;
    TinyGsmClient _gsmClient;
    SSLClient _sslClient;

    // Use a unique_ptr to manage the lifetime of the mTLS parameters
    // and allow for initialization within the constructor body.
    std::unique_ptr<SSLClientParameters> _mTLS;

public:
    // Constructor now takes the modem's UART pins.
    SimInternetClient(int8_t rxPin, int8_t txPin, uint32_t baud, int uart_nr = 2);

    void connect() override;
    bool isConnected() override;
    Client& getClient() override;
};
