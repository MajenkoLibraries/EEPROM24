#ifndef _EERROM24_H
#define _EEPROM24_H

#include <Arduino.h>
#include <Wire.h>

class EEPROM24 {
    protected:  
        uint8_t _i2caddr;
        uint32_t _bytes;

    public:
        EEPROM24(uint8_t a, uint32_t b) : _i2caddr(a), _bytes(b) {}

        void begin();
        void begin(uint8_t addr);
        size_t write(uint32_t addr, uint8_t byte);
        uint8_t read(uint32_t addr);
};

class EEPROM24_256 : public EEPROM24 {
    public:
        EEPROM24_256() : EEPROM24(0x50, 32768) {}
        EEPROM24_256(uint8_t addr) : EEPROM24(addr, 32768) {}
};
                
#endif
