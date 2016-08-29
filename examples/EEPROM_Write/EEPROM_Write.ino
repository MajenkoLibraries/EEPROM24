#include <Wire.h>
#include <EEPROM24.h>

EEPROM24_256 eeprom;

void setup() {
    Serial.begin(115200);
    eeprom.begin();

    eeprom.write(0, 0xDE);
    eeprom.write(1, 0xAD);
    eeprom.write(2, 0xBE);
    eeprom.write(3, 0xEF);
    eeprom.write(4, 0xFE);
    eeprom.write(5, 0xED);
    Serial.println("EEPROM written.");
}

void loop() {
}
