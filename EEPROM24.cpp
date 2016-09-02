#include <EEPROM24.h>

void EEPROM24::begin() {
    Wire.begin();
}

void EEPROM24::begin(uint8_t addr) {
    _i2caddr = addr;
    Wire.begin();
}

size_t EEPROM24::write(uint32_t addr, uint8_t b) {
    if (addr >= _bytes) return 0;

    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)((addr >> 8)  & 0xFF));
    Wire.write((uint8_t)(addr & 0xFF));
    Wire.write(b);
    int r = Wire.endTransmission();

    Wire.beginTransmission(_i2caddr);
    int res = Wire.endTransmission();
    uint32_t to = 100;
    while (res != 0) {
        delay(1);
        Wire.beginTransmission(_i2caddr);
        res = Wire.endTransmission();
        to--;
        if (to == 0) {
            return 0;
        }
    }
    return 1;
}

size_t EEPROM24::write(uint32_t addr, const uint8_t *bytes, uint32_t len) {

//for (int i = 0; i < len; i++) {
//    write(addr + i, bytes[i]);
//}
//return len;

    if (addr >= _bytes) {
        return 0;
    }

    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)((addr >> 8)  & 0xFF));
    Wire.write((uint8_t)(addr & 0xFF));

    uint32_t written = 0;

    for (uint32_t b = 0; b < len; b++) {
        Wire.write(bytes[b]);
        written++;
        addr++;
        if (addr >= _bytes) { // Terminate early - run out of space
            int res = Wire.endTransmission();
            uint32_t to = 100;
            while (res != 0) {
                delay(1);
                Wire.beginTransmission(_i2caddr);
                res = Wire.endTransmission();
                to--;
                if (to == 0) {
                    return written;
                }
            }
            return written;
        }
        if ((addr & (_page - 1)) == 0) { // Looped to start of page
            int res = Wire.endTransmission();
            uint32_t to = 100;
            while (res != 0) {
                delay(1);
                Wire.beginTransmission(_i2caddr);
                res = Wire.endTransmission();
                to--;
                if (to == 0) {
                    return written;
                }
            }
            Wire.beginTransmission(_i2caddr);
            Wire.write((uint8_t)((addr >> 8)  & 0xFF));
            Wire.write((uint8_t)(addr & 0xFF));
        }
    }
    Wire.endTransmission();
    int res = Wire.endTransmission();
    uint32_t to = 10;
    while (res != 0) {
        delay(1);
        Wire.beginTransmission(_i2caddr);
        res = Wire.endTransmission();
        to--;
        if (to == 0) {
            return written;
        }
    }
    return written;
}

size_t EEPROM24::write(uint32_t addr, const char *str) {
    return write(addr, (const uint8_t *)str, strlen(str));
}

uint8_t EEPROM24::read(uint32_t addr) {
    if (addr >= _bytes) return 0;

    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)((addr >> 8)  & 0xFF));
    Wire.write((uint8_t)(addr & 0xFF));
    Wire.endTransmission(false);
    Wire.requestFrom(_i2caddr, (uint8_t)1);
    return Wire.read();
}
