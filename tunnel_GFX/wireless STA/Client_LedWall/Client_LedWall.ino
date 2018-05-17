#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <WiFiClient.h>



char ssid[] = "ledwall";           // SSID of your home WiFi
char pass[] = "antonio151991";            // password of your home WiFi

IPAddress server(192, 168, 4, 1);    // the fix IP address of the server


unsigned long askTimer = 0;
int audio;

Adafruit_NeoMatrix
matrix = Adafruit_NeoMatrix
         (45, 15, D4,
          NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
          NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
          NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass); // connects to the WiFi router
  //  WiFi.config(IP, NETMASK, NETWORK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  matrix.begin();
  matrix.setBrightness(150);
  matrix.show();
}

void loop () {
  WiFiClient client;
  
  if (millis() - askTimer > 50) {
    client.connect(server, 80);

    while (client.connected()) {
      String spectrum = client.readStringUntil('\r');
      client.flush();
      audio = spectrum.toInt();
      Serial.println(audio);
    }
  }
  for (int i = -1 ; i <= 44; i++) {
    if (i <= audio) {
      matrix.drawFastVLine( i, 0, 15, 0xFFFF);
    }
    else {
      matrix.drawFastVLine( i, 0, 15, 0x0000);
    }
  }
  matrix.show();
}
