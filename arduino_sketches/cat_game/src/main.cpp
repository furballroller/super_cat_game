// hi! the main code is further below, at //// MAIN CODE ////
// the rest is functions and stuff that makes it work
// the functions I thought would be generally useful are in functions.cpp


#include <Arduino.h>
#include <FastLED.h>
#include "functions.h"


//// CAT GAME SETTINGS //// (the hardware settings are in ../include/functions.h)
#define MAX_J 0.001  // jerk in units/frame^3 (how fast the dot's acceleration changes)
#define SENSITIVITY 0.8 * 4095  // 0-1, the maximum resistance value considered as detected (max. is 4095 but in reality max. is less)
// lower reading means lower resistance so higher pressure, reading 0 when max. out pressure
// the pot on the PCB is a more robust adjustment? Voltage divider basically reads Rvelostat/Rtotal so lower (anticlockwise?) increases sensitivity


//// CAT GAME FUNCTIONS ////

// return true if the dot is caught
bool Caught(float x, float y, int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH]) {
  // detect if touching:
  // top left
  if ( Pressure_m[(int) floor(y * VELOSTAT_WIDTH)][(int) floor(x * VELOSTAT_WIDTH)] <= SENSITIVITY) {
    return true;
  }
  // top right
  if ( Pressure_m[(int) floor(y * VELOSTAT_WIDTH)][(int) ceil(x * VELOSTAT_WIDTH)] <= SENSITIVITY) {
    return true;
  }
  // bottom left
  if ( Pressure_m[(int) ceil(y * VELOSTAT_WIDTH)][(int) floor(x * VELOSTAT_WIDTH)] <= SENSITIVITY) {
    return true;
  }
  // bottom right
  if ( Pressure_m[(int) ceil(y * VELOSTAT_WIDTH)][(int) ceil(x * VELOSTAT_WIDTH)] <= SENSITIVITY) {
    return true;
  }
}

// choose a direction to move in, then return the jerk in that direction to the provided jx jy vector
void Set_jerk(float x, float y, float &jx, float &jy, int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH]) {

  // reset the jerk
  jx = 0;
  jy = 0;
  
  //// heuristic for choosing direction ////
  // move away from walls
  jx += 0.5 - x;
  jy += 0.5 - y;

  // move away from nearby pressed cells
  for (int Y=1; Y<=VELOSTAT_WIDTH; Y++) {
    for (int X=1; X<=VELOSTAT_WIDTH; X++) {

      if (Pressure_m[Y][X] <= SENSITIVITY) {  // if cell is pressed
        jx += (X/VELOSTAT_WIDTH - x) - 1;
        jy += (Y/VELOSTAT_WIDTH - y) - 1;
      }
    }
  }

  //// scale the jerk so it has magnitude MAX_J ////
  float mag = sqrt(jx*jx + jy*jy);
  jx == jx / mag * MAX_J;
  jy == jy / mag * MAX_J;

}

// add instructions to light up the 4 LEDs nearest to the dot with 1/4 brightness (but they can overlap too...)
void Draw_dot(float x, float y, CRGB* LED_m[LED_WIDTH][LED_WIDTH]) {
  *LED_m[(int)floor(y*LED_WIDTH)][(int)floor(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to top-left pixel
  *LED_m[(int)ceil(y*LED_WIDTH)][(int)floor(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to top-right pixel
  *LED_m[(int)floor(y*LED_WIDTH)][(int)ceil(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to bottom-left pixel
  *LED_m[(int)ceil(y*LED_WIDTH)][(int)ceil(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to bottom-right pixel
}

void Draw_caught_dot(float x, float y, CRGB* LED_m[LED_WIDTH][LED_WIDTH]) {
  *LED_m[(int)floor(y*LED_WIDTH)][(int)floor(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to top-left pixel
  *LED_m[(int)ceil(y*LED_WIDTH)][(int)floor(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to bottom-left pixel
  *LED_m[(int)floor(y*LED_WIDTH)][(int)ceil(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to top-right pixel
  *LED_m[(int)ceil(y*LED_WIDTH)][(int)ceil(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to bottom-right pixel

  // draw extra stuff, like a cross so you know the dot has been caught
  try {*LED_m[(int)floor(y*LED_WIDTH) -1][(int)floor(x*LED_WIDTH) -1] += CRGB(225/4,0,0);}// add 1/4 brightness red to far top-left pixel
  catch(...) {}  
  try {*LED_m[(int)ceil(y*LED_WIDTH) +1][(int)floor(x*LED_WIDTH) -1] += CRGB(225/4,0,0);}  // add 1/4 brightness red to far bottom-left pixel
  catch(...) {} 
  try {*LED_m[(int)floor(y*LED_WIDTH) -1][(int)ceil(x*LED_WIDTH) +1] += CRGB(225/4,0,0);}  // add 1/4 brightness red to far top-right pixel
  catch(...) {} 
  try {*LED_m[(int)ceil(y*LED_WIDTH) +1][(int)ceil(x*LED_WIDTH) +1] += CRGB(225/4,0,0);}  // add 1/4 brightness red to far bottom-right pixel
  catch(...) {} 

}

// call this to restart the code
void(* Reset) (void) = 0;

//// MAIN CODE ////

//// hardware variables ////
// LEDs
CRGB LEDs[NUM_LEDS];  // Linear array representing LED strip
CRGB* LED_m[LED_WIDTH][LED_WIDTH];  // LED matrix (will be reorganised from ^ linear array)
// LED_m[Y][X]

int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH];  // array of arrays storing pressure readings for the board
// Pressure_m[y][x] for the pressure reading at (x,y)

//// cat game variables ////
// position in proportion_of_screen
float x;  // (0-1, where 0 is far left and 1 is far right)
float y;  // (0-1, where 0 is far top and 1 is far bottom)
 
// velocity in proportion_of_screen/loop_time (loop_time is the time taken for a loop to run)
float vx;
float vy; 

// acceleration in proportion_of_screen/loop_time^2
float ax;
float ay; 

// jerk in proportion_of_screen/loop_time^3
float jx;
float jy;

void setup() {
  // put your setup code here, to run once:
  init_LED_ptrs(LED_m, LEDs);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(LEDs, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2500);

  // acceleration in proportion_of_screen/loop_time^2
  ax = 0;
  ay = 0;

  // initally 0 velocity
  vx=0;
  vy=0;
  
  // initial position in the middle
  x=0.5;
  y=0.5;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // "*(LED_m[Y][X]) = CRGB:: " to set CRGB of LEDs

  Read_pressure_all(Pressure_m);  // read pressure at the start of every loop

  if (Caught(x, y, Pressure_m)) {
    // blink dot 5 times
    for (int i; i<5; i++) {

      //// add instructions to draw the caught dot ////
      fill_solid(LEDs, NUM_LEDS, CRGB::Black);  // reset all LEDs first
      FastLED.show();  

      delay(500);

      Draw_caught_dot(x, y, LED_m);  // draw the dot
      FastLED.show();  

      delay(500);

    }

    Reset();

  }
  else {

    Set_jerk(x, y, jx, jy, Pressure_m);  // choose desired direction and set jerk in that direction
  
    //// move in the chosen direction ////
    // jerk, always using the maximum amount
    ax += jx;
    ay += jy;

    // accelerate
    vx += ax;
    vy += ay;

    // displace
    x += vx;
    y += vy;

    //// add instructions to draw the dot ////
    fill_solid(LEDs, NUM_LEDS, CRGB::Black);  // reset all LEDs first
    Draw_dot(x, y, LED_m);  // draw the dot
  }

  

  // end of main code


  FastLED.show();  // send the instructions to the LEDs every loop
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
