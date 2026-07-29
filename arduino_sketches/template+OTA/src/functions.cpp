#include "functions.h" // Links this file back to your declarations
#include <FastLED.h>


// velostat channel map (because I messed up all the IDCs to fit them on the PCB :>)
const int Channel_m[2][16] = {
  {1,0,3,2,5,4,7,6,14,15,12,13,10,11,8,9},
  {7,6,5,4,3,2,1,0,8,9,10,11,12,13,14,15}
};  // Set A (x) followed by Set B (y)
// (0,0) is top left; Y goes down, X goes right
// matrices follow Matrix[Y][X]

// fills each Pressure_m[y][x] with the velostat reading at (x,y) on the velostat mat
void Read_pressure_all(int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH]) {
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

      Pressure_m[Y][X] = analogRead(VELOSTAT_PIN);

    }
  }
}

// returns the pressure value at (velostat_x, velostat_y) on the velostat mat
int Read_pressure_xy(int velostat_x, int velostat_y) {
  int Channel;

    Channel = Channel_m[1][velostat_y];
    digitalWrite(S0b, Channel & 0x01);
    digitalWrite(S1b, (Channel >> 1) & 0x01);
    digitalWrite(S2b, (Channel >> 2) & 0x01);
    digitalWrite(S3b, (Channel >> 3) & 0x01);

    Channel = Channel_m[0][velostat_x];
    digitalWrite(S0a, Channel & 0x01);
    digitalWrite(S1a, (Channel >> 1) & 0x01);
    digitalWrite(S2a, (Channel >> 2) & 0x01);
    digitalWrite(S3a, (Channel >> 3) & 0x01);

    return analogRead(VELOSTAT_PIN);

}

// initialise LED_m, which maps the LED strip to the matrix so it's easier to code
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