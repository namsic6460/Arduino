#include <SoftwareSerial.h>

#define CDS A0
#define ECHO 12
#define TRIG 13

SoftwareSerial BTSerial(2, 3);

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
}

double getDistance() {
  digitalWrite(TRIG, LOW);
  digitalWrite(ECHO, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long duration = pulseIn(ECHO, HIGH);
  return (340.0 * duration) / 20000;
}
 
void loop(){
  double distance = getDistance();
  distance = distance > 255 ? 255 : distance < 2 ? 2 : distance;
  int type = 0;
    
  BTSerial.write(type);
  BTSerial.write(distance);
  
  int cds = analogRead(CDS) / 4;
  cds = cds < 2 ? 2 : cds;
  type = 1;
  BTSerial.write(type);
  BTSerial.write(cds);
  Serial.println(cds);

  delay(100);
}
