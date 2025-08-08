#include "MCP2515Controller.h"
#include <Arduino.h>

Mcp2515Controller::Mcp2515Controller(int8_t csPin, int8_t sckPin, int8_t misoPin, int8_t mosiPin) :
    _mcp2515(csPin, 10000000U, &_spi),
    _spi(HSPI),
    _csPin(csPin),
    _sckPin(sckPin),
    _misoPin(misoPin),
    _mosiPin(mosiPin)
{
}

bool Mcp2515Controller::begin()
{
    Serial.println("Initializing MCP2515 CAN Controller...");
    _spi.begin(_sckPin, _misoPin, _mosiPin, _csPin);

    _mcp2515.reset();
    if (_mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ) != MCP2515::ERROR_OK) {
        Serial.println("FATAL: Error setting CAN bitrate!");
        return false;
    }
    if (_mcp2515.setNormalMode() != MCP2515::ERROR_OK) {
        Serial.println("FATAL: Error setting CAN normal mode!");
        return false;
    }
    
    Serial.println("CAN Controller Initialized Successfully.");
    return true;
}

bool Mcp2515Controller::readMessage(CanFrame& frame)
{
    struct can_frame libraryFrame;
    if (_mcp2515.readMessage(&libraryFrame) == MCP2515::ERROR_OK) {
        // Translate from the library's specific struct to our generic one.
        frame.id = libraryFrame.can_id;
        frame.len = libraryFrame.can_dlc;
        for (int i = 0; i < frame.len; i++) {
            frame.data[i] = libraryFrame.data[i];
        }
        return true;
    }
    return false;
}
