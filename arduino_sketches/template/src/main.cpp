// hi! if you're wondering, I put some useful functions in functions.cpp


#include <Arduino.h>
#include <FastLED.h>
#include "functions.h"


//// variables ////
// LEDs
CRGB LEDs[NUM_LEDS];  // Linear array representing LED strip
CRGB* LED_m[LED_WIDTH][LED_WIDTH];  // LED matrix (will be reorganised from ^ linear array)
// LED_m[Y][X]

int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH];  // array of arrays storing pressure readings for the board
// Pressure_m[y][x] for the pressure reading at (x,y)


void setup() {
  init_LED_ptrs(LED_m, LEDs);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(LEDs, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2500);

  // put your setup code here, to run once:

  
}


void loop() {
  // put your main code here, to run repeatedly:
  // "*(LED_m[Y][X]) = CRGB:: " to set CRGB of LEDs
  

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
