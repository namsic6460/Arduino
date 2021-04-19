#include <SPI.h>

void setup() {
//  SPI.begin();
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  
  SPCR |= _BV(SPE);
  SPCR &= ~_BV(MSTR);
  SPCR |= _BV(SPIE);
  
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  Serial.begin(9600);
}

int B = 0;

ISR(SPI_STC_vect) {
  byte confirm = SPDR;

  Serial.print((char) confirm);

  SPDR = B;
}

void loop() {
  B++;
}
