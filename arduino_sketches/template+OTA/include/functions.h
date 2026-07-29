#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//// HARDWARE SETTINGS ////
#define VELOSTAT_WIDTH 14
#define LED_WIDTH 13
#define NUM_LEDS 169

#define LED_PIN 15
#define VELOSTAT_PIN A0

#define S0a 9
#define S1a 10
#define S2a 46
#define S3a 3

#define S0b 6
#define S1b 7
#define S2b 4
#define S3b 5



#include <Arduino.h> // Allows the use of Arduino types like String, digitalRead, etc.
#include <FastLED.h>  // for CRGB

// Declare your function signatures here (ended with semicolons)

// fills each Pressure_m[y][x] with the velostat reading at (x,y) on the velostat mat
void Read_pressure_all(int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH]);

// returns the pressure value at (velostat_x, velostat_y) on the velostat mat
int Read_pressure_xy(int velostat_x, int velostat_y);

// Put this in setup() to initialise LED_m, which maps the LED strip to the matrix so it's easier to code
void init_LED_ptrs(CRGB* LED_m[LED_WIDTH][LED_WIDTH], CRGB LEDs[NUM_LEDS]);

#endif
