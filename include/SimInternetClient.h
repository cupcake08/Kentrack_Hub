#pragma once

#include "modem_config.h"
#include "IInternetClient.h"
#include "constants.h"

#include <HardwareSerial.h>
#include <TinyGsmClient.h> 
#include <SSLClient.h>

class SimInternetClient : public IInternetClient
{
private:
    HardwareSerial* _modemSerial;
    TinyGsm* _modem;
    TinyGsmClient _gsmClient;
    SSLClient _sslClient;

    SSLClientParameters mTLS = SSLClientParameters::fromPEM(AWS_CERT_CRT, sizeof AWS_CERT_CRT, AWS_CERT_PRIVATE, sizeof AWS_CERT_PRIVATE);

public:
    // Constructor now takes the modem's UART pins.
    SimInternetClient(int8_t rxPin, int8_t txPin, uint32_t baud, int uart_nr = 2);

    void connect() override;
    bool isConnected() override;
    Client& getClient() override;
};
