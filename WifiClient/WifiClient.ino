#include <DHT.h>

#include "WiFiEsp.h"
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

DHT dht(A0, DHT11);

char ssid[] = "iptime3";
char pass[] = "classno3";
int status = WL_IDLE_STATUS;

char server[] = "192.168.0.78";

WiFiEspClient client;

void setup()
{
  Serial.begin(9600);

  pinMode(4, INPUT_PULLUP);
  
  Serial1.begin(9600);
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  printWifiStatus();

  Serial.println();
  Serial.println("Starting connection to server...");
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    client.println();
  }
}

boolean disconnected = false;

unsigned long prevMilli = 0;
unsigned long currMilli;

void loop()
{
  while(client.connected()) {
    while(client.available()) {
      char input = client.read();
      Serial.write(input);
      delayMicroseconds(50);
    }

    if(!client.available()) {
      //JoyStick
      int x = analogRead(A1);
      int y = analogRead(A2);
      boolean k = !digitalRead(4);
  
      if(x < 490 || x > 510 || y < 490 || y > 510 || k) {
        String outputString = "";
        outputString += thousandToString(x);
        outputString += ", ";
        outputString += thousandToString(y);
        outputString += ", ";
        outputString += k;
        outputString += '\n';
  
  //      Serial.print(outputString);
        client.print(outputString);
        delay(100);
      }
  
      //Humidity + Temperature
      currMilli = millis();
  
      if(currMilli - prevMilli > 1000) {
        prevMilli = currMilli;
        
        int humidity = dht.readHumidity();
        int temperature = dht.readTemperature();
    
        String outputString = "H: ";
    
        outputString += humidity / 10;
        outputString += humidity % 10;
        
        outputString += ", T: ";
    
        outputString += temperature / 10;
        outputString += temperature % 10;
        
        outputString += '\n';
    
  //      Serial.print(outputString);
        client.print(outputString);
      }
    }
  }

  if (!(client.connected() || disconnected)) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

    disconnected = true;
  }
}

String thousandToString(int value) {
  String output = "";
  output += value / 1000;
  output += (value / 100) % 10;
  output += (value / 10) % 10;
  output += value % 10;

  return output;
}

void printWifiStatus()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
