#ifndef _EERROM24_H
#define _EEPROM24_H

#include <Arduino.h>
#include <Wire.h>

class EEPROM24 {
    protected:  
        uint8_t _i2caddr;
        uint32_t _bytes;
        uint32_t _page;

    public:
        EEPROM24(uint8_t a, uint32_t b, uint32_t p) : _i2caddr(a), _bytes(b), _page(p) {}

        void begin();
        void begin(uint8_t addr);
        size_t write(uint32_t addr, uint8_t b);
        size_t write(uint32_t addr, const char *str);
        size_t write(uint32_t addr, const uint8_t *bytes, size_t len);
        uint8_t read(uint32_t addr);
};

class EEPROM24_512 : public EEPROM24 {
    public:
        EEPROM24_512() : EEPROM24(0x50, 65536, 16) {}
        EEPROM24_512(uint8_t addr) : EEPROM24(addr, 65536, 16) {}
};
                
class EEPROM24_256 : public EEPROM24 {
    public:
        EEPROM24_256() : EEPROM24(0x50, 32768, 16) {}
        EEPROM24_256(uint8_t addr) : EEPROM24(addr, 32768, 16) {}
};
                
class EEPROM24_128 : public EEPROM24 {
    public:
        EEPROM24_128() : EEPROM24(0x50, 16384, 16) {}
        EEPROM24_128(uint8_t addr) : EEPROM24(addr, 16384, 16) {}
};
                
class EEPROM24_64 : public EEPROM24 {
    public:
        EEPROM24_64() : EEPROM24(0x50, 8192, 16) {}
        EEPROM24_64(uint8_t addr) : EEPROM24(addr, 8192, 16) {}
};
                
class EEPROM24_32 : public EEPROM24 {
    public:
        EEPROM24_32() : EEPROM24(0x50, 4096, 16) {}
        EEPROM24_32(uint8_t addr) : EEPROM24(addr, 4096, 16) {}
};
                
class EEPROM24_16 : public EEPROM24 {
    public:
        EEPROM24_16() : EEPROM24(0x50, 2048, 16) {}
        EEPROM24_16(uint8_t addr) : EEPROM24(addr, 2048, 16) {}
};
                
class EEPROM24_08 : public EEPROM24 {
    public:
        EEPROM24_08() : EEPROM24(0x50, 1024, 16) {}
        EEPROM24_08(uint8_t addr) : EEPROM24(addr, 1024, 16) {}
};
                
class EEPROM24_04 : public EEPROM24 {
    public:
        EEPROM24_04() : EEPROM24(0x50, 512, 16) {}
        EEPROM24_04(uint8_t addr) : EEPROM24(addr, 512, 16) {}
};
                
class EEPROM24_02 : public EEPROM24 {
    public:
        EEPROM24_02() : EEPROM24(0x50, 256, 8) {}
        EEPROM24_02(uint8_t addr) : EEPROM24(addr, 256, 8) {}
};
                
class EEPROM24_01 : public EEPROM24 {
    public:
        EEPROM24_01() : EEPROM24(0x50, 128, 8) {}
        EEPROM24_01(uint8_t addr) : EEPROM24(addr, 128, 8) {}
};
                
class EEPROM24_00 : public EEPROM24 {
    public:
        EEPROM24_00() : EEPROM24(0x50, 16, 1) {}
        EEPROM24_00(uint8_t addr) : EEPROM24(addr, 16, 1) {}
};
                
#endif
