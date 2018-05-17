

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/FreeMono9pt7b.h> // Qui inserisci il tipo di font, li trovi nella cartella della libreria Adafruit_GFX
 
#define PIN D4

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(45, 15, PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);
 
const uint16_t colors[] = {
  matrix.Color(0, 255, 0), matrix.Color(0, 255, 0), matrix.Color(0, 255, 0),matrix.Color(0, 255, 0), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};

void setup() {
  matrix.begin();
  matrix.setTextSize(2); // qui pui scalare la grandezza del font
  //matrix.setFont(&FreeMono9pt7b); // qui richiami il font
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(100);
  matrix.setTextColor(colors[0]);
}
 
int x    = matrix.width();
int pass = 2;
 
void loop() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0); // modificando il numero pui modificare la posizzione della scritta verticalmente
  matrix.print(F("Quello che il napoletano chiama 'A FINE D'O MUNNO' il resto del mondo lo chiama NAPOLI"));
 
  if(--x < -1100 // modificando il numero modifichi la durata dello scorrimento
  ) {
    x = matrix.width();
 
    if(++pass >= 15) pass = 0; // velocità scorrimento
  /*  matrix.setTextColor(colors[pass]); */
  }
  matrix.show();
  delay(100);
}
