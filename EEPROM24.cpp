#include <EEPROM24.h>

void EEPROM24::begin() {
    Wire.begin();
}

void EEPROM24::begin(uint8_t addr) {
    _i2caddr = addr;
    Wire.begin();
}

size_t EEPROM24::write(uint32_t addr, uint8_t byte) {
    if (addr >= _bytes) return 0;

    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)((addr > 8)  & 0xFF));
    Wire.write((uint8_t)(addr & 0xFF));
    Wire.write(byte);
    Wire.endTransmission();

    Wire.beginTransmission(_i2caddr);
    int res = Wire.endTransmission();
    uint32_t to = 1000;
    while (res != 0) {
        Wire.beginTransmission(_i2caddr);
        res = Wire.endTransmission();
        to--;
        if (to == 0) {
            return 0;
        }
    }
    return 1;
}

uint8_t EEPROM24::read(uint32_t addr) {
    if (addr >= _bytes) return 0;

    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)((addr > 8)  & 0xFF));
    Wire.write((uint8_t)(addr & 0xFF));
    Wire.endTransmission(false);
    Wire.requestFrom(_i2caddr, (uint8_t)1);
    return Wire.read();
}
