// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#ifndef _SERIAL_PORT_INC
#define _SERIAL_PORT_INC

#include "HardwareComponent.h"

#define TXD_MASK (1 << 2)
#define RXD_MASK (1 << 3)
#define RTS_MASK (1 << 4)
#define CTS_MASK (1 << 5)
#define DSR_MASK (1 << 6)
#define CD_MASK (1 << 8)
#define DTR_MASK (1 << 20)
#define RI_MASK (1 << 22)

class SerialPort : public HardwareComponent {

    // References (for quickly accessing other components)
    class UART *uart;

    // Information shown in the GUI inspector panel
    SerialPortInfo info;


    //
    // Variables
    //

    // The connected device
    SerialPortDevice device = SPD_LOOPBACK;

    // The current values of the port pins
    uint32_t port;

    
    //
    // Constructing and destructing
    //

public:

    SerialPort();


    //
    // Iterating over snapshot items
    //

    template <class T>
    void applyToPersistentItems(T& worker)
    {
        worker

        & device;
    }

    template <class T>
    void applyToResetItems(T& worker)
    {
        worker

        & port;
    }


    //
    // Methods from HardwareComponent
    //

private:

    void _initialize() override;
    void _powerOn() override;
    void _inspect() override;
    void _dump() override;
    size_t _load(uint8_t *buffer) override;
    size_t _save(uint8_t *buffer) override;
    

    //
    // Reading the internal state
    //

public:

    // Returns the latest internal state recorded by inspect()
    SerialPortInfo getInfo();


    //
    // Connecting peripherals
    //

public:

    // Returns the currently connected device
    SerialPortDevice getDevice() { return device; }
    
    // Connects or disconnects a device
    void connectDevice(SerialPortDevice device);


    //
    // Transmitting and receiving data
    //

public:

    // Reads the current value of a certain port pin
    bool getPin(int nr);

    // Modifies the value of a certain port pin
    void setPin(int nr, bool value);

    // Convenience wrappers
    bool getTXD() { return getPin(2); }
    bool getRXD() { return getPin(3); }
    bool getRTS() { return getPin(4); }
    bool getCTS() { return getPin(5); }
    bool getDSR() { return getPin(6); }
    bool getCD() { return getPin(8); }
    bool getDTR() { return getPin(20); }
    bool getRI() { return getPin(22); }

    void setTXD(bool value) { setPin(2, value); }
    void setRXD(bool value) { setPin(3, value); }
    void setRTS(bool value) { setPin(4, value); }
    void setCTS(bool value) { setPin(5, value); }
    void setDSR(bool value) { setPin(6, value); }
    void setCD(bool value) { setPin(8, value); }
    void setDTR(bool value) { setPin(20, value); }
    void setRI(bool value) { setPin(22, value); }

private:

    void setPort(uint32_t mask, bool value);
};

#endif

