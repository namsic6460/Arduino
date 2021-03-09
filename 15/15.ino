//void setup() {
//  Serial.begin(9600);
//  pinMode(13, OUTPUT);
//
//  TCCR2A = 0x00;
//  TCCR2B = 0x02;
//  TCNT2 = 256 - 40; //216
//  TIMSK2 = 0x01;
//}
//
//unsigned long cMicros;
//unsigned long pMicros = 0;
//unsigned long cMillis;
//unsigned long pMillis = 0;
//
//int count = 0;
//int duty = 0;
//
//void loop() {
////  cMicros = micros();
//  cMillis = millis();
//  
////  if(cMicros - pMicros > 20) {
////    pMicros = cMicros;
////
////    if(count == 100) {
////      digitalWrite(13, HIGH);
////      count = 0;
////    }
////    
////    else if(count == duty) {
////      digitalWrite(13, LOW);
////    }
////    
////    count++;
////  }
//
//  if(cMillis - pMillis > 10) {
//    pMillis = cMillis;
//    duty++;
//
//    if(duty == 100) {
//      duty = 0;
//    }
//  }
//}
//
//int ovfCount = 0;
//SIGNAL(TIMER2_OVF_vect) {
//  TCNT2 = 256-40; //216
//  ovfCount++;
//
//  if(ovfCount == 100) {
//    digitalWrite(13, HIGH);
//    ovfCount = 0;
//  }
//
//  else if(ovfCount == duty) {
//    digitalWrite(13, LOW);
//  }
//}

//---------------------------------

//void setup() {
//  Serial.begin(9600);
//  pinMode(13, OUTPUT);
//
//  TCCR2A = 0x02;
//  TCCR2B = 0x02;
//  TCNT2 = 0;
//  OCR2A = 40;
//  TIMSK2 = 0x02;
//}
//
//unsigned long cMicros;
//unsigned long pMicros = 0;
//unsigned long cMillis;
//unsigned long pMillis = 0;
//
//int count = 0;
//int duty = 0;
//
//void loop() {
////  cMicros = micros();
//  cMillis = millis();
//  
////  if(cMicros - pMicros > 20) {
////    pMicros = cMicros;
////
////    if(count == 100) {
////      digitalWrite(13, HIGH);
////      count = 0;
////    }
////    
////    else if(count == duty) {
////      digitalWrite(13, LOW);
////    }
////    
////    count++;
////  }
//
//  if(cMillis - pMillis > 10) {
//    pMillis = cMillis;
//    duty++;
//
//    if(duty == 100) {
//      duty = 0;
//    }
//  }
//}
//
//int compCount = 0;
//SIGNAL(TIMER2_COMPA_vect) {
//  compCount++;
//
//  if(compCount == 100) {
//    digitalWrite(13, HIGH);
//    compCount = 0;
//  }
//
//  else if(compCount == duty) {
//    digitalWrite(13, LOW);
//  }
//}

//--------------------------------

//void setup() {
//  Serial.begin(9600);
//  pinMode(13, OUTPUT);
//
//  TCCR2A = 0x03;
//  TCCR2B = 0x05;
//  TCNT2 = 0;
//  OCR2A = 25;
//  TIMSK2 = 0x03;
//}
//
//unsigned long cMillis;
//unsigned long pMillis = 0;
//
//int count = 0;
//float duty = 0;
//
//void loop() {
//  cMillis = millis();
//
//  if(cMillis - pMillis > 10) {
//    pMillis = cMillis;
//    duty += 2.5;
//
//    if(duty > 249)
//      duty = 0;
//  }
//}
//
//SIGNAL(TIMER2_OVF_vect) {
//  OCR2A = duty;
//  digitalWrite(13, HIGH);
//}
//SIGNAL(TIMER2_COMPA_vect) {
//  digitalWrite(13, LOW);
//}

//-------------------------------

//void setup() {
//  Serial.begin(9600);
//  DDRB |= 0x20;
//
//  TCCR2A = 0x03;
//  TCCR2B = 0x05;
//  TCNT2 = 0;
//  OCR2A = 25;
//  TIMSK2 = 0x03;
//}
//
//unsigned long cMillis;
//unsigned long pMillis = 0;
//
//int count = 0;
//float duty = 0;
//
//void loop() {
//  cMillis = millis();
//
//  if(cMillis - pMillis > 10) {
//    pMillis = cMillis;
//    duty += 2.5;
//
//    if(duty > 249)
//      duty = 0;
//  }
//}
//
//SIGNAL(TIMER2_OVF_vect) {
//  OCR2A = duty;
//  PORTB |= 0x20;
//}
//SIGNAL(TIMER2_COMPA_vect) {
//  PORTB &= !0x20;
//}

//------------------------------------

//void setup() {
//  Serial.begin(9600);
//  
//  ADMUX = 0x40;
//  ADCSRA = 0x87;
//}
//
//unsigned short adcX;
//unsigned short adcY;
//void loop() {
//  ADMUX = 0x40;
//  ADCSRA |= 0x40;
//  delay(1);
//  adcX = ADC;
//                                                                                      
//  ADMUX = 0x41;
//  ADCSRA |= 0x40;
//  delay(1);
//  adcY = ADC;
//  
//  Serial.print("{");
//  Serial.print(adcX);
//  Serial.print(", ");
//  Serial.print(adcY);
//  Serial.println("}");
//
//  delay(100);
//}

//-------------------------------------

//void setup() {
//  pinMode(1, OUTPUT);
//  digitalWrite(1, HIGH);
//}
//
//void loop() {
//  digitalWrite(1, LOW);
//  delayMicroseconds(102);
//  
//  digitalWrite(1, HIGH);
//  delayMicroseconds(102);
//  digitalWrite(1, LOW);
//  delayMicroseconds(102);
//  digitalWrite(1, LOW);
//  delayMicroseconds(102);
//  digitalWrite(1, LOW);
//  delayMicroseconds(102);
//  digitalWrite(1, HIGH);
//  delayMicroseconds(102);
//  digitalWrite(1, HIGH);
//  delayMicroseconds(102);
//  digitalWrite(1, LOW);
//  delayMicroseconds(102);
//  digitalWrite(1, LOW);
//  delayMicroseconds(102);
//  
//  digitalWrite(1, HIGH);
//  delayMicroseconds(102);
//}

//-------------------------------------

//void setup() {
//  pinMode(0, INPUT);
//  pinMode(1, OUTPUT);
//
//  UCSR0A = 0x00;
//  UCSR0B = 0x18;
//  UCSR0C = 0x06;
//  UBRR0 = 103;
//}
//
//unsigned long cMillis;
//unsigned long pMillis = 0;
//
//void loop() {
//  cMillis = millis();
//
//  if(cMillis - pMillis >= 1000) {
//    pMillis = cMillis;
//
//    for(int i = 0; i < 11; i++) {
//      while(!(UCSR0A & 0x20));
//
//      if(i != 10)
//        UDR0 = 0x30 + i;
//      else
//        UDR0 = 0x0A;
//    }
//  }
//
//  if(UCSR0A & 0x80) {
//    char input = UDR0;
//    
//    while(!(UCSR0A & 0x20));
//    UDR0 = input;
//  }
//}

//----------------------------------------------
//#include <Wire.h>
// 
//void setup()
//{
//  Wire.begin();
// 
//  Serial.begin(9600);
//  while (!Serial);
//  Serial.println("\nI2C Scanner");
//}
// 
// 
//void loop()
//{
//  byte error, address;
//  int nDevices;
// 
//  Serial.println("Scanning...");
// 
//  nDevices = 0;
//  for(address = 1; address < 127; address++ )
//  {
//    Wire.beginTransmission(address);
//    error = Wire.endTransmission();
// 
//    if (error == 0)
//    {
//      Serial.print("I2C device found at address 0x");
//      if (address<16)
//        Serial.print("0");
//      Serial.println(address,HEX);
// 
//      nDevices++;
//    }
//    else if (error==4)
//    {
//      Serial.print("Unknown error at address 0x");
//      if (address<16)
//        Serial.print("0");
//      Serial.println(address, HEX);
//    }    
//  }
//  
//  if (nDevices == 0)
//    Serial.println("No I2C devices found\n");
//  else
//    Serial.println("done\n");
// 
//  delay(5000);
//}

//-------------------------------

//SDA : PC4
//SCL : PC5

#define SDA 18
#define SCL 19

void setup() {
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);

  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}
  

void loop() {
  backLightOn();
  delay(1000);
  backLightOff();
  delay(1000);
}

void backLightOn() {
  start();
  data(0x8E);
  ack();
  data(0x08);
  stop_();
}

void backLightOff() {
  start();
  data(0x4E);
  ack();
  data(0x00);
  stop_();
}

void start() {
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);
}

void stop_() {
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}

void ack() {
  digitalWrite(SCL, HIGH);
  digitalWrite(SCL, LOW);
}

void data(char hex) {
  for(int i = 0; i < 8; i++) {
    if(hex & (0x80 >> i))
      digitalWrite(SDA, HIGH);
    else
      digitalWrite(SDA, LOW);

    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);
  }
}
