// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define RROW1 8 // Popular NeoPixel ring size
#define RROW2 16
#define RROW3 24
#define GAP 40
#define BROW1 48
#define BROW2 56
#define BROW3 64
#define NUMPIXELS 64


// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 56 // Time (in milliseconds) to pause between pixels
const int X=8;
const int Y=8;
int matrix[Y][X] = { {0,0,0,0,0,0,0,0},
                    {0,0,0,3,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,2,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}};

//int matrixb[Y][X]={};
//for (int i =0; i< Y; i++) {
//  for (int j =0; j < X; j++) {
//    matrixb [i][j] = 1;
//  }
//  }
char val;


void setup() {
  Serial.begin(9600);
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
 // pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
if (Serial.available())
{
  val = Serial.read();
  Serial.println(val);
}
if (val == '1')
{
pixels.setPixelColor(25, pixels.Color(255, 255, 255));  }

  Serial.println(matrix[2][4]);
  for(int i=0; i<RROW1; i=i+2) { // For each pixel...
//    for (int j=0; j<8; j++){
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
   for(int i=RROW1+1; i<RROW2; i=i+2) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
   }
   for(int i=RROW2; i<RROW3; i=i+2) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
   }
   for(int i=GAP+1; i<BROW1; i=i+2) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
   }
   for(int i=BROW1; i<BROW2; i=i+2) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
   }
   for(int i=BROW2+1; i<BROW3; i=i+2) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
   }
}
