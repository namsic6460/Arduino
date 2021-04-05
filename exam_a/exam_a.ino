#include <SoftwareSerial.h>

#include "WiFiEsp.h"
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

SoftwareSerial BTSerial(4, 5);

char ssid[] = "iptime3";
char pass[] = "classno3";
int status = WL_IDLE_STATUS;

char server[] = "192.168.0.74";

WiFiEspClient client;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  Serial1.begin(9600);
  Serial1.listen();
  
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
  if (client.connect(server, 4321)) {
    Serial.println("Connected to server");
    client.println();
  }
  
  BTSerial.listen();
}

int inputCount = 0;
String wifiString;

void loop() {
  if(BTSerial.available()) {
    char c = BTSerial.read();

    if(c == 'h') {
      Serial.print("\nHumidity: ");
      wifiString = "H: ";
    } else if(c == 't') {
      Serial.print("\nTemperature: ");
      wifiString += ", T: ";
    } else if(c == 'd') {
      Serial.print("\nDistance Alert: ");
    } else if(c == 'c') {
      Serial.print("CLOSE");

      Serial1.listen();
      if(client.connected()) {
        client.print("c");
      }
      BTSerial.listen();
    } else if(c == 'f') {
      Serial.print("FAR");

      Serial1.listen();
      if(client.connected()) {
        client.print("f");
      }
      BTSerial.listen();
    } else if(c == 'l') {
      Serial.print("\nLight: ");
      wifiString += "&L: ";
    } else if(c == '-') {
      Serial1.listen();
      if(client.connected()) {
        client.print(wifiString);
      }
      BTSerial.listen();
    } else {
      Serial.print(c);
      wifiString += c;
    }
  }

  if(Serial.available()) {
    Serial1.listen();
    client.print((char) Serial.read());
    BTSerial.listen();
  }
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
