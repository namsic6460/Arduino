#include <SoftwareSerial.h>

SoftwareSerial sSerial(2, 3);

void setup() {
  Serial.begin(9600);
  sSerial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    sSerial.write(Serial.read());
  } else if(sSerial.available()) {
    Serial.write(sSerial.read());
  }
}
