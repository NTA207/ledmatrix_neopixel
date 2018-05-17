#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>



// Configurazione Urlo di munc su doppia matrice verticale 15 x 45 = 15 x 90 usando neomatrix_tile
Adafruit_NeoMatrix
matrix = Adafruit_NeoMatrix(15, 45, 1, 2, D4,
                            NEO_TILE_TOP   + NEO_TILE_RIGHT   +
                            NEO_TILE_ROWS   + NEO_TILE_PROGRESSIVE +
                            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB + NEO_KHZ800);

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup()
{
  matrix.begin();
  matrix.setBrightness(200);
  matrix.show();
  Serial.begin(9600);
}
void loop()
{
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

  //double volts = (peakToPeak * 5.0) / 1024;  // convert to volts

  int displayPeak = map(peakToPeak, 2, 1023, -1, 89);
  Serial.println(displayPeak);

  matrix.setRotation(2);

  for (int i = -1 ; i <= 89; i++) {
    if (i <= displayPeak) {
      matrix.drawFastHLine( 0, i, 15, 0xFFFF);

    }
    else {
      matrix.drawFastHLine( 0, i, 15, 0x0000);
    }
  }
  matrix.show();
}


//end

