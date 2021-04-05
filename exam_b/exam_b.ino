#include <SoftwareSerial.h>
#include <DHT.h>

#define ECHO 12
#define TRIG 13

SoftwareSerial BTSerial(4, 5);
DHT dht(A0, DHT11);

int getDistance() {
  digitalWrite(TRIG, LOW);
  digitalWrite(ECHO, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long duration = pulseIn(ECHO, HIGH);
  double distance = (340.0 * duration) / 20000;
  return distance > 255 ? 255 : (int) distance;
}

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
}

int prevDistance = 100;
int currDistance;
unsigned long skipMilli = 0;
unsigned long prevMilli = 0;
unsigned long currMilli;
void loop() {
  currMilli = millis();

  if(currMilli - skipMilli > 500) {    
    skipMilli = currMilli;
    prevDistance = currDistance;
      
    currDistance = getDistance();
    
    if(prevDistance > 20 && currDistance <= 20) {
      BTSerial.write((byte) 'd');
      BTSerial.write((byte) 'c');
    } else if(prevDistance <= 20 && currDistance > 20) {
      BTSerial.write((byte) 'd');
      BTSerial.write((byte) 'f');
    }
  }

  //Not 2000 because of delay
  if(currMilli - prevMilli > 1850) {
    prevMilli = currMilli;
    
    int humi = dht.readHumidity();
    BTSerial.write((byte) 'h');
    
    char ten = humi / 10 + '0';
    char one = humi % 10 + '0';
  
    if(humi >= 10) {
      BTSerial.write((byte) ten);
    }
  
    BTSerial.write((byte) one);
    
    int temp = dht.readTemperature();
    BTSerial.write((byte) 't');
    
    ten = temp / 10 + '0';
    one = temp % 10 + '0';
  
    if(temp >= 10) {
      BTSerial.write((byte) ten);
    }
  
    BTSerial.write((byte) one);

    int light = analogRead(A1);
    char hun = light / 100 % 10 + '0';
    ten = light / 10 % 10 + '0';
    one = light % 10 + '0';

    BTSerial.write((byte) 'l');

    if(light >= 1000) {
      BTSerial.write((byte) '1');
    }

    if(light >= 100) {
      BTSerial.write((byte) hun);
    }

    if(light >= 10) {
      BTSerial.write((byte) ten);
    }

    BTSerial.write((byte) one);
    BTSerial.write((byte) '-');
  }
}
