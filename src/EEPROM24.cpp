#include <EEPROM24.h>

void EEPROM24::begin() {
    Wire.begin();
}

void EEPROM24::begin(uint8_t addr) {
    _i2caddr = addr;
    Wire.begin();
}

size_t EEPROM24::write(size_t addr, uint8_t b) {
    if (addr >= _bytes) return 0;

    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)((addr >> 8)  & 0xFF));
    Wire.write((uint8_t)(addr & 0xFF));
    Wire.write(b);
    int r = Wire.endTransmission();

    Wire.beginTransmission(_i2caddr);
    int res = Wire.endTransmission();
    size_t to = 100;
    while (res == 2) {
        Wire.beginTransmission(_i2caddr);
        res = Wire.endTransmission();
        to--;
        if (to == 0) {
            return 0;
        }
    }
    return 1;
}

size_t EEPROM24::write(size_t addr, const uint8_t *bytes, size_t len) {

    if (addr >= _bytes) {
        return 0;
    }

    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)((addr >> 8)  & 0xFF));
    Wire.write((uint8_t)(addr & 0xFF));

    size_t written = 0;

    for (size_t b = 0; b < len; b++) {
        Wire.write(bytes[b]);
        written++;
        addr++;
        if (addr >= _bytes) { // Terminate early - run out of space
            Wire.endTransmission();
            Wire.beginTransmission(_i2caddr);
            int res = Wire.endTransmission();
            size_t to = 100;
            while (res == 2) {
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
            Wire.endTransmission();
            size_t to = 100;
            Wire.beginTransmission(_i2caddr);
            int res = Wire.endTransmission();
            while (res == 2) {
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
    Wire.beginTransmission(_i2caddr);
    int res = Wire.endTransmission();
    size_t to = 100;
    while (res == 2) {
        Wire.beginTransmission(_i2caddr);
        res = Wire.endTransmission();
        to--;
        if (to == 0) {
            return written;
        }
    }
    return written;
}

size_t EEPROM24::write(size_t addr, const char *str) {
    return write(addr, (const uint8_t *)str, strlen(str) + 1);
}

uint8_t EEPROM24::read(size_t addr) {
    if (addr >= _bytes) return 0;

    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)((addr >> 8)  & 0xFF));
    Wire.write((uint8_t)(addr & 0xFF));
    Wire.endTransmission(false);
    Wire.requestFrom(_i2caddr, (uint8_t)1);
    return Wire.read();
}

size_t EEPROM24::read(size_t addr, uint8_t *b, size_t len) {
    if (addr >= _bytes) return 0;

    for (int i = 0; i < len; i++) {
        b[i] = read(addr + i);
    }
    return len;

/*  Eventually this will be packetted up to read in chunks of 16 bytes at a time.
 *  For now though we will just have to read a byte at a time using the code above.
 *  It is such a shame that the default I2C buffer for Wire.h is only 32 bytes.

    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)((addr >> 8)  & 0xFF));
    Wire.write((uint8_t)(addr & 0xFF));
    Wire.endTransmission(false);
    Wire.requestFrom(_i2caddr, (uint8_t)len);
    for (int i = 0; i < len; i++) {
        b[i] = Wire.read();
    }
    return len;
*/
}
