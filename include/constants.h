#pragma once

// --- Wi-Fi Configuration (kept for flexibility) ---
extern const char *WIFI_SSID;
extern const char *WIFI_PASSWORD;

// --- GPRS Configuration ---
extern const char *GPRS_APN;
extern const char *GPRS_USER;
extern const char *GPRS_PASS;

// --- AWS IoT Core Configuration ---
extern const char *AWS_IOT_ENDPOINT;
extern const char *AWS_IOT_TOPIC;
extern const int AWS_IOT_PORT;

// --- AWS Certificates (for SSLClient) ---
// Device Certificate in DER format
extern const unsigned char AWS_CERT_CRT_DER[];
extern const unsigned int AWS_CERT_CRT_DER_LEN;

// Device Private Key in DER format
extern const unsigned char AWS_CERT_PRIVATE_DER[];
extern const unsigned int AWS_CERT_PRIVATE_DER_LEN;

// --- Certificates ---
extern const char *AWS_CERT_CA;
extern const char *AWS_CERT_CRT;
extern const char *AWS_CERT_PRIVATE;

