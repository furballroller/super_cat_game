#include <Arduino.h>
#include <FastLED.h>

// example cat game settings
#define MAX_J 0.001  // jerk in units/frame^3 (how fast acceleration changes)


#define SENSITIVITY 0.8  // 0-1, the proportion of maximum pressure range considered detected (max. is 4095 but in reality max. is less)
// lower reading means lower resistance so higher pressure, reading 0 when max. out pressure
// the pot on the PCB is a more robust adjustment? Voltage divider basically reads Rvelostat/Rtotal so lower (anticlockwise?) increases sensitivity
#define VELOSTAT_WIDTH 14
#define LED_WIDTH 13
#define NUM_LEDS 169

#define LED_PIN 15

#define S0a 9
#define S1a 10
#define S2a 46
#define S3a 3

#define S0b 6
#define S1b 7
#define S2b 4
#define S3b 5

//LEDs
CRGB LEDs[NUM_LEDS];  // LED strip for FastLED
CRGB* LED_m[LED_WIDTH][LED_WIDTH];  // LED matrix (reorganised from linear array)
// LED_m[Y][X]


// mapping out velostat channels
const int Channel_m[2][16] = {
  {1,0,3,2,5,4,7,6,14,15,12,13,10,11,8,9},
  {7,6,5,4,3,2,1,0,8,9,10,11,12,13,14,15}
};  // Set A (x) followed by Set B (y)
// (0,0) is top left; Y goes down, X goes right
// matrices follow Matrix[Y][X]



int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH];




void Read_pressure(int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH]) {
  int Channel;

  for (int Y=0; Y<VELOSTAT_WIDTH; Y+=1) {

    Channel = Channel_m[1][Y];
    digitalWrite(S0b, Channel & 0x01);
    digitalWrite(S1b, (Channel >> 1) & 0x01);
    digitalWrite(S2b, (Channel >> 2) & 0x01);
    digitalWrite(S3b, (Channel >> 3) & 0x01);

    for (int X=0; X<VELOSTAT_WIDTH; X+=1) {

      Channel = Channel_m[0][X];
      digitalWrite(S0a, Channel & 0x01);
      digitalWrite(S1a, (Channel >> 1) & 0x01);
      digitalWrite(S2a, (Channel >> 2) & 0x01);
      digitalWrite(S3a, (Channel >> 3) & 0x01);

      Pressure_m[Y][X] = analogRead(A0);

    }
  }
}

void init_LED_ptrs(CRGB* LED_m[LED_WIDTH][LED_WIDTH], CRGB LEDs[NUM_LEDS]) {
  // map LED_m to the right spots in LEDs
  
  bool right = true;

  for (int Y=0; Y<LED_WIDTH; Y+=1) {
    
    for (int X=0; X<LED_WIDTH; X+=1) {

      if(right = true) {
        right = false;

        //set pixels, moving right
        LED_m[Y][X] = &LEDs[Y*LED_WIDTH + X];

      }
      else {
        right = true;

        //set pixels, moving left
        LED_m[Y][X] = &LEDs[(Y+1)*LED_WIDTH - X - 1];

      }

    }
    
    // change direction when changing rows
    if(right = true) {
      right = false;
    }
    else {
      right = true;
    }

  }

}







// functions for example cat game

// return a unit vector in the desired direction
void Choose_direction(float x, float y, float &x_direction, float &y_direction, int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH]) {

  x_direction = 0;
  y_direction = 0;
  
  // move away from walls
  x_direction += 0.5 - x;
  y_direction += 0.5 - y;

  // move away from nearby pressed cells
  for (int Y=1; Y<=VELOSTAT_WIDTH; Y++) {
    for (int X=1; X<=VELOSTAT_WIDTH; X++) {

      if (Pressure_m[Y][X] <= SENSITIVITY*4095) {  // if cell is pressed
        x_direction += (X/VELOSTAT_WIDTH - x) - 1;
        y_direction += (Y/VELOSTAT_WIDTH - y) - 1;
      }
    }
  }

  // scale down to unit vector
  float mag = sqrt(x_direction*x_direction + y_direction*y_direction);
  x_direction /= mag;
  y_direction /= mag;
}

// ask to light up the nearest 4 LEDs with 1/4 brightness, but they can overlap too...
void Draw_dot(float x, float y, CRGB* LED_m[LED_WIDTH][LED_WIDTH]) {
  *LED_m[(int)floor(y*LED_WIDTH)][(int)floor(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to top-left pixel
  *LED_m[(int)ceil(y*LED_WIDTH)][(int)floor(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to top-right pixel
  *LED_m[(int)floor(y*LED_WIDTH)][(int)ceil(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to bottom-left pixel
  *LED_m[(int)ceil(y*LED_WIDTH)][(int)ceil(x*LED_WIDTH)] += CRGB(225/4,0,0);  // add 1/4 brightness red to bottom-right pixel
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// position in units
float x;
float y;
 
// v in units/frame
float vx;
float vy; 

// a in units/frame^2
float ax;
float ay; 

float x_direction;
float y_direction;

void setup() {
  // put your setup code here, to run once:
  init_LED_ptrs(LED_m, LEDs);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(LEDs, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2500);

  ax = 0;
  ay = 0;

  vx=0;
  vy=0;
  
  x=0.5;
  y=0.5;
  
}

void loop() {
  Read_pressure(Pressure_m);
  // put your main code here, to run repeatedly:
  // "*(LED_m[Y][X]) = CRGB:: " to set CRGB of LEDs

  // cat game V0:
  //  - using coordinates 0-1

  fill_solid(LEDs, NUM_LEDS, CRGB::Black);  // reset all LEDs before drawing

  Choose_direction(x, y, x_direction, y_direction, Pressure_m);
  
  // jerk
  ax += MAX_J * x_direction;
  ay += MAX_J * y_direction;

  // accelerate
  vx += ax;
  vy += ay;

  // displace
  x += vx;
  y += vy;

  Draw_dot(x, y, LED_m);



  FastLED.show();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








