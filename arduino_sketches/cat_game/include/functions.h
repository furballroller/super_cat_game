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
void Read_pressure_all(int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH]);
int Read_pressure_xy(int velostat_x, int velostat_y);
void init_LED_ptrs(CRGB* LED_m[LED_WIDTH][LED_WIDTH], CRGB LEDs[NUM_LEDS]);

#endif
