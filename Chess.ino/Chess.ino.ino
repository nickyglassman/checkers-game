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
                    
char val;
String inputread = "";
String pos;


void setup() {
  Serial.begin(9600);
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
}

// void recvWithEndMarker(){
//  static byte ndx = 0;
//  char endMarker = "/pos";
//  char val;
// }

void loop() {
//  pixels.setPixelColor(33, pixels.Color(209, 139, 71));
//  pixels.show();   // Send the updated pixel colors to the hardware.
  //pixels.clear(); // Set all pixel colors to 'off'
  //pixels.setPixelColor(25, pixels.Color(255, 255, 255));
  //pixels.show();
  // delay(DELAYVAL); // Pause before next pass through loop
  if (Serial.available())
  { // If data is available to read,
    do{
      val = Serial.read(); // read it and store it in val
      if (val != -1) {
        if (val == '<') { //start character
          inputread = "";
        } else if (val == '>') { //end character
            int delim = inputread.indexOf(",");
            String type = inputread.substring(0, delim);

            Serial.print("input: ");
            Serial.println(inputread);
            Serial.print("type: ");
            Serial.println(type);
            Serial.print("pos: ");
            Serial.println(pos);
            
            if (type == "wP") { // If 1 was received
              pos = inputread.substring(delim + 1);
              pixels.setPixelColor(pos.toInt(), pixels.Color(255, 0, 0));
              pixels.show();   // Send the updated pixel colors to the hardware.
            }
            if (type == "wK") { // If 1 was received
              pos = inputread.substring(delim + 1);  
              pixels.setPixelColor(pos.toInt(), pixels.Color(0, 255, 0));
              pixels.show();   // Send the updated pixel colors to the hardware.
            }
            if (type == "bP") { // If 1 was received
              pos = inputread.substring(delim + 1);
              pixels.setPixelColor(pos.toInt(), pixels.Color(0, 0, 255));
              pixels.show();   // Send the updated pixel colors to the hardware.
            }
            if (type == "bK") { // If 1 was received
              pos = inputread.substring(delim + 1);
              pixels.setPixelColor(pos.toInt(), pixels.Color(160, 39, 200));
              pixels.show();   // Send the updated pixel colors to the hardware.
            }
            if (type == "off") { // If 1 was received
              pos = inputread.substring(delim + 1);
              pixels.setPixelColor(pos.toInt(), pixels.Color(0, 0, 0));
              pixels.show();   // Send the updated pixel colors to the hardware.
            }
        } else {
          inputread = inputread + val;
        }
      }
      } while(val != -1);
  }

//  delay(10);

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
//  recvWithEndMarker();
//
//  if (Serial.available()) {
//    message = Serial.readString();
//
//   if (message == "pawn") {
//      pixels.setPixelColor(20, pixels.Color(209, 139, 71));
//      pixels.show();   // Send the updated pixel colors to the hardware.
//    }
//    
//    message = "";
//  }
//  if (message == "pawn") {
//    pixels.setPixelColor(20, pixels.Color(209, 139, 71));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    message = "";
//  }
  
//  while (Serial.available() > 0) {
//    val = Serial.read();
////    message = Serial.readString();
////    if (message == "pawn") {
////        pixels.setPixelColor(33, pixels.Color(209, 139, 71));
////        pixels.show();   // Send the updated pixel colors to the hardware.
////    }
//
//   message += val;
//   
//   if (val == 'E') {
//        pixels.setPixelColor(15, pixels.Color(209, 139, 71));
//        pixels.show();   // Send the updated pixel colors to the hardware.
//        if (message == "p2E") {
//          pixels.setPixelColor(20, pixels.Color(209, 139, 71));
//          pixels.show();   // Send the updated pixel colors to the hardware.
//          message = "";
//        }
//    }
//    
////    if (val == 'E') {
////      pixels.setPixelColor(20, pixels.Color(209, 139, 71));
////      pixels.show();   // Send the updated pixel colors to the hardware.
////      if (message == "pawnE") {
////        pixels.setPixelColor(33, pixels.Color(209, 139, 71));
////        pixels.show();   // Send the updated pixel colors to the hardware.
////        message = "";
////      }
//////      if (message == "kingE") {
//////        pixels.setPixelColor(10, pixels.Color(209, 139, 71));
//////        pixels.show();   // Send the updated pixel colors to the hardware.
//////        message = "";
//////      }  
////    }
//  }
//  if (Serial.available()) { 
//    val = Serial.read();
//
//    if (val == 'w') {
//      pixels.setPixelColor(33, pixels.Color(209, 139, 71));
//      pixels.show();   // Send the updated pixel colors to the hardware.
//    }  
//  }
}

//  static byte ndx = 0;
//  char endMarker = "/pos";
//  char val;
//    if (val != endMarker) {
//      if (val == "pos");
//      int numpixel = Serial.read();
//    if (Serial.read() == 'w'){
//      pixels.setPixelColor(numpixel, pixels.Color(255, 255, 255));
//      
////      receivedChars[ndx] = val;
////      ndx++;
////      if (ndx >= numChars) {
////        ndx = numChars - 1;
//      }
//    }
//     pixels.setPixelColor(numpixel, pixels.Color(255, 255, 255));
//     pixels.show();   // Send the updated pixel colors to the hardware.
//     delay(50);
//     Serial.print(val);


