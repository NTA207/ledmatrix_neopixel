#include <ESP8266WebServer.h>
#include <SPI.h>
#include <ESP8266WiFi.h>


char ssid[] = "airport";               // SSID of your home WiFi
char pass[] = "airport360";  // password of your home WiFi

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
int displayPeak;

WiFiServer server(80);
IPAddress ip(10, 0, 1, 80);           // IP address of the server
IPAddress gateway(10, 0, 1, 1);        // gateway of your network
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);  // only for debug
  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, pass);                 // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  server.begin();                         // starts the server
}

void loop () {


  WiFiClient client = server.available();
  if (client) {
    if (client.connected())
    {
        readAudio();
      Serial.println("new client connesso");
      Serial.println(displayPeak);
      client.print(displayPeak);
      client.println('\r');
      client.flush();
      delay(10);
    }
  }
}

void readAudio() {
  //  unsigned long startMillis = millis();
  // unsigned int peakToPeak = 0;
  //  unsigned int signalMax = 0;
  //  unsigned int signalMin = 1024;
  //  while (millis() - startMillis < sampleWindow)
  //  {
  //    sample = analogRead(0);
  //    if (sample < 1024)  // toss out spurious readings
  //    {
  //      if (sample > signalMax)
  //      {
  //        signalMax = sample;  // save just the max levels
  //      }
  //      else if (sample < signalMin)
  //      {
  //        signalMin = sample;  // save just the min levels
  //      }
  //    }
  //  }
//  peakToPeak = (analogRead(0)) * 10;
  displayPeak = map(analogRead(0), 0, 1023, -1, 44);
  Serial.println(displayPeak);
}
