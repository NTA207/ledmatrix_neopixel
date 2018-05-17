#include <SPI.h>
#include <ESP8266WiFi.h>

char ssid [] = "ledwall";
char pass [] = "meglioinsieme1234";

//WiFiServer server(80);
//IPAddress local_IP(192, 168, 4, 1);
//IPAddress gateway(192, 168, 4, 1);
//IPAddress subnet(255, 255, 255, 0);

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup () {
  Serial.begin(115200);                   // only for debug
  Serial.println();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass, 4);
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP()); 
  Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum());
  //server.begin();
}

void loop () {
 
  unsigned long startMillis = millis();
  unsigned int peakToPeak = 0;

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
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
  //  double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
  int displayPeak = map(peakToPeak, 0, 1023, -1, 44);
  //Serial.println(displayPeak);
}
