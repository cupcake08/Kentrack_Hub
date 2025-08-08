#pragma once

#include "ICanController.h"
#include <mcp2515.h>
#include <SPI.h>

class Mcp2515Controller : public ICanController
{
private:
    MCP2515 _mcp2515;
    SPIClass _spi;
    
    // Pin configuration
    const int8_t _csPin;
    const int8_t _sckPin;
    const int8_t _misoPin;
    const int8_t _mosiPin;

public:
    // Constructor takes all necessary pins to encapsulate hardware setup.
    Mcp2515Controller(int8_t csPin, int8_t sckPin, int8_t misoPin, int8_t mosiPin);

    bool begin() override;
    bool readMessage(CanFrame& frame) override;
};
