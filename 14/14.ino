void setup() {
  Serial.begin(9600);
  
  TCCR2A = 0x03;
  TCCR2B = 0x02;
  TCNT2 = 56;   //100us 마다
  OCR2A = 100;  //50us 마다
  TIMSK2 = 0x03;
}

void loop() {
  
}

int compCount = 0;
int ovfCount = 0;

SIGNAL(TIMER2_OVF_vect) {
  TCNT2 = 256 - 200; //56
  ovfCount++;

  if(ovfCount == 10000) {
    ovfCount = 0;
    Serial.println("hello(1sec)");
  }
}

SIGNAL(TIMER2_COMPA_vect) {
  compCount++;

  if(compCount == 5000) {
    compCount = 0;
    Serial.println("hello(0.5s)");
  }
}
//
//void setup() {
//  Serial.begin(9600);
//  
//  TCCR2A = 0x02;
//  TCCR2B = 0x02;
//  TCNT2 = 0x00;
//  TIMSK2 = 0x01;
//}
//
//void loop() {
//  
//}
//
//int count = 0;
//SIGNAL(TIMER2_OVF_vect) {
//  count++;
//
//  if(count == 7812) {
//    Serial.println("hello");
//    count = 0;
//  }
//}
