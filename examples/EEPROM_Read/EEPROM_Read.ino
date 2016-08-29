#include <EEPROM24.h>

EEPROM24_256 eeprom;

void setup() {
    Serial.begin(115200);
    eeprom.begin();
    for (int i = 0; i < 24; i++) {
        Serial.printf("%02x ", eeprom.read(i));
    }
    Serial.println();
}

void loop() {
}
