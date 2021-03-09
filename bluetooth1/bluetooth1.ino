#include <SoftwareSerial.h>

#define DIS_LED 5
#define CDS_LED 6

SoftwareSerial BTSerial(2, 3);
 
void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);
}
 
void loop(){
  if (BTSerial.available()) {
    int type = BTSerial.read();

    while(!BTSerial.available());

    int value = BTSerial.read();
    Serial.print(value);
    
    switch(type) {
      case 0:
        Serial.println("cm");
        analogWrite(DIS_LED, value);
        break;

      case 1:
        Serial.println(" 밝기");
        analogWrite(CDS_LED, value);
        break;
    }
  }
}
