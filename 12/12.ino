void setup() {
  //pinMode(13, OUTPUT);
  DDRB |= 0x20;
}

void loop() {
  //digitalWrite(13, HIGH);
  PORTB |= 0x20;
  delay(1000);
  //digitalWrite(13, LOW);
  PORTB &= ~0x20;
  delay(1000);                                                
}
