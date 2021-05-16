#include <SoftwareSerial.h>
#include <DHT.h>

SoftwareSerial BTSerial(2, 3);
DHT dht(A0, DHT11);

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);

  Serial.println("Started");
}

void loop(){
  if(BTSerial.available()) {
    byte input;
    
    input = BTSerial.read();

    if(input == ((byte) '-')) {
      int humi = dht.readHumidity();
      int ten = humi / 10 + '0';
      int one = humi % 10 + '0';
  
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

      Serial.print("Sent : ");
      Serial.print(humi);
      Serial.print(", ");
      Serial.println(temp);
    }
  }
}
