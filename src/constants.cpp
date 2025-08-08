// constants.cpp
#include "constants.h"

// --- Wi-Fi Configuration ---
const char *WIFI_SSID = "YOUR_WIFI_SSID";
const char *WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// --- GPRS Configuration ---
const char *GPRS_APN = "airtelgprs.com"; 
const char *GPRS_USER = "";
const char *GPRS_PASS = "";

// --- AWS IoT Core Configuration ---
const char *AWS_IOT_ENDPOINT = "YOUR_AWS_IOT_ENDPOINT";
const char *AWS_IOT_TOPIC = "esp32/can/data";
const int AWS_IOT_PORT = 8883;

// --- Certificates ---
const char *AWS_CERT_CA = R"EOF(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----
)EOF";

const char *AWS_CERT_CRT = R"EOF(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----
)EOF";

const char *AWS_CERT_PRIVATE = R"EOF(
-----BEGIN PRIVATE KEY-----
-----END PRIVATE KEY-----
)EOF";