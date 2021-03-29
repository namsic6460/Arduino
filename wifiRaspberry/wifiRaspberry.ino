#include "WiFiEsp.h"
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

char ssid[] = "iptime3";
char pass[] = "classno3";
int status = WL_IDLE_STATUS;

char server[] = "192.168.0.74";

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
  if (client.connect(server, 4321)) {
    Serial.println("Connected to server");
    client.println();
  }
}

boolean disconnected = false;
boolean k = 1;
void loop()
{
  while(client.connected()) { 
    while(client.available()) {
      char input = client.read();
      Serial.write(input);
      delayMicroseconds(50);
    }

    //JoyStick
    boolean input = !digitalRead(4);

    if(k && input) {
      client.print("1");
    } else if(!k && !input) {
      k = 1;
    }

    if(Serial.available()) {
      client.print("0");
      Serial.flush();
    }
  }

  if (!(client.connected() || disconnected)) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

    disconnected = true;
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
