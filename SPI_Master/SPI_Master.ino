#include <SPI.h>

void setup() {
  SPI.begin();
//  pinMode(MISO, INPUT);
//  pinMode(MOSI, OUTPUT);
//  pinMode(SCK, OUTPUT);
//  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  Serial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    digitalWrite(SS, LOW);
    byte input = Serial.read();
    char rxData = SPI.transfer(input);
    digitalWrite(SS, HIGH);
    Serial.print((char) input);
  }
}
