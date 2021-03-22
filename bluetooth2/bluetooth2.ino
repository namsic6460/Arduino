#include <SoftwareSerial.h>
#include <DHT.h>

#define ECHO 12
#define TRIG 13

SoftwareSerial BTSerial(2, 3);
DHT dht(A1, DHT11);

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

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
}

boolean isSerial = false;
void loop(){
  if(Serial.available()) {    
    byte input = Serial.read();
    if(input == (byte) '-') {
      return;
    }
    
    isSerial = true;
    BTSerial.write(input);
  } else if(isSerial) {
    BTSerial.write((byte) '-');

    int distance = getDistance();
    char hun = distance / 100 + '0';
    char ten = distance / 10 % 10 + '0';
    char one = distance % 10 + '0';

    if(distance >= 100) {
      BTSerial.write((byte) hun);
    }
    
    if(distance >= 10) {
      BTSerial.write((byte) ten);
    }
    
    BTSerial.write((byte) one);
    BTSerial.write((byte) '-');

    int humi = dht.readHumidity();
    ten = humi / 10 + '0';
    one = humi % 10 + '0';

    if(humi >= 10) {
      BTSerial.write((byte) ten);
    }

    BTSerial.write((byte) one);
    BTSerial.write((byte) '-');
    
    int temp = dht.readTemperature();
    ten = temp / 10 + '0';
    one = temp % 10 + '0';

    if(temp >= 10) {
      BTSerial.write((byte) ten);
    }

    BTSerial.write((byte) one);
    BTSerial.write((byte) '-');
    
    isSerial = false;
  }

  if(BTSerial.available()) {
    byte input;
    
    input = BTSerial.read();

    if(input != ((byte) '-')) {
      Serial.print((char) input);
    } else {
      Serial.println();
    }    
  }
}
