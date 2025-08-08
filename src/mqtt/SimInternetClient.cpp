#include "SimInternetClient.h"
#include <TinyGsmClient.h>
#include "AWSRootCA.h"

SimInternetClient::SimInternetClient(int8_t rxPin, int8_t txPin, uint32_t baud, int uart_nr) : _sslClient(_gsmClient, TAs, (size_t)TAs_NUM, 1)
{
    // Dynamically create the serial and modem objects.
    _modemSerial = new HardwareSerial(uart_nr);
    _modemSerial->begin(baud, SERIAL_8N1, rxPin, txPin);

    _modem = new TinyGsm(*_modemSerial);

    _gsmClient.init(_modem);

    _sslClient.setMutualAuthParams(mTLS);
}

void SimInternetClient::connect()
{
    Serial.println("Initializing Modem...");
    // Give modem time to boot
    delay(6000);

    if (!_modem->init()) {
        Serial.println("Failed to init modem. Restarting...");
        _modem->restart();
        return;
    }

    Serial.print("Waiting for network...");
    if (!_modem->waitForNetwork()) {
        Serial.println(" fail");
        delay(10000);
        return;
    }
    Serial.println(" OK");

    Serial.print("Connecting to GPRS: ");
    Serial.print(GPRS_APN);
    if (!_modem->gprsConnect(GPRS_APN, GPRS_USER, GPRS_PASS)) {
        Serial.println(" fail");
        delay(10000);
        return;
    }
    Serial.println(" OK");
}

bool SimInternetClient::isConnected()
{
    return _modem->isGprsConnected();
}

// Returns a reference to the SSLClient, upcast to the generic Client base class.
Client &SimInternetClient::getClient()
{
    return _sslClient;
}
