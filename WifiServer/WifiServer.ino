#include "WiFiEsp.h"
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

char ssid[] = "iptime3";
char pass[] = "classno3";
int status = WL_IDLE_STATUS;
int reqCount = 0;

WiFiEspServer server(80);

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
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

  server.begin();
}

String inputString = "";
void loop()
{
  WiFiEspClient client = server.available();
  if (client) {
    Serial.println("New client");

    while (client.connected()) {
      if (client.available()) {
        char input = client.read();
        Serial.write(input);
        delayMicroseconds(50);

        if(input == '\n') {
          if(inputString.substring(0, 3).equals("H: ") &&
             inputString.substring(5, 10).equals(", T: ")) {
            client.write("DHT OK\n");
          } else if(inputString.substring(4, 6).equals(", ") &&
             inputString.substring(10, 12).equals(", ")) {
            client.write("JoyStick OK\n");
          } else {
            client.write("ERROR\n");
          }
          
          inputString = "";
        } else {
          inputString += input;
        }
      }
    }

    delay(10);

    client.stop();
    Serial.println("Client disconnected");
  }
}


void printWifiStatus()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}
