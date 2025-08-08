#pragma once

#include <stdint.h>

// A generic structure to hold a CAN frame, independent of any specific library.
struct CanFrame {
    uint32_t id;      // CAN ID
    uint8_t len;      // Data Length Code (0-8)
    uint8_t data[8];  // Data payload
};

// The interface for any CAN controller.
class ICanController
{
public:
    virtual ~ICanController() {}

    // Initializes the CAN controller hardware.
    virtual bool begin() = 0;

    // Reads a message from the CAN bus.
    // Returns true if a message was received, false otherwise.
    virtual bool readMessage(CanFrame& frame) = 0;
};
