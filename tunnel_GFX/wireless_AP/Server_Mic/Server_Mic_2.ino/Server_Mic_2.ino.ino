#include <ESP8266WebServer.h>
#include <SPI.h>
#include <ESP8266WiFi.h>


char ssid[] = "ledwall";               // SSID of your home WiFi
char pass[] = "antonio151991";  // password of your home WiFi

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
unsigned long startMillis = millis();
unsigned int peakToPeak = 0;
unsigned int signalMax = 0;
unsigned int signalMin = 1024;
int displayPeak;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);                   // only for debug
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  server.begin();                         // starts the server
}

void loop () {
  // Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum());
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  displayPeak = map(peakToPeak, 0, 1023, -1, 44);
  Serial.println(displayPeak);
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    if (client.connected())
    {

        client.println("hello world\r");
        //client.println('\r');
        client.flush();
      

    }
  }

  // close the connection:
  // client.stop();
  // Serial.println("client disonnected");
}
