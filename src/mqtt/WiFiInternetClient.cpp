#include "WiFiInternetClient.h"

// The constructor calls the configuration method.
WiFiInternetClient::WiFiInternetClient()
{
    _configureCertificates();
}

// The certificate logic now lives here, where it belongs.
void WiFiInternetClient::_configureCertificates()
{
    _secureClient.setCACert(AWS_CERT_CA);
    _secureClient.setCertificate(AWS_CERT_CRT);
    _secureClient.setPrivateKey(AWS_CERT_PRIVATE);
}

void WiFiInternetClient::_connectToWiFi()
{
    Serial.print("Connecting to Wi-Fi: ");
    Serial.print(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void WiFiInternetClient::connect()
{
    _connectToWiFi();
}

bool WiFiInternetClient::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

// Returns a reference to its privately-owned secure client,
// but upcast to the generic Client base class.
Client& WiFiInternetClient::getClient()
{
    return _secureClient;
}
