void setup() {
  Serial.begin(9600);
  //0 : Arudino 2
  //attachInterrupt(0, myISR, FALLING);
  DDRD &= ~0x04;
  //EICRA = 0x02; //falling edge
  EICRA = 0x01; //falling/rising edge
  EIMSK = 0x01;
}

void loop() {
  
}

SIGNAL(INT0_vect) {
//  int inValue = digitalRead(2);
//
//  if(inValue == 0)
//    Serial.println("Btn Down");
//  else if(inValue == 1)
//    Serial.println("Btn Up");

//------------------------------
  unsigned int inData = PIND;

  if(inData & 0x04)
    Serial.println("Btn Up");
  else
    Serial.println("Btn Down");
}
