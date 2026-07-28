#include <Arduino.h>
#include <FastLED.h>

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






///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  init_LED_ptrs(LED_m, LEDs);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(LEDs, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2500);
}

void loop() {
  Read_pressure(Pressure_m);
  // put your main code here, to run repeatedly:
  // "*(LED_m[Y][X]) = " to set CRGB of LEDs

  // press test V0:
  //  - using velostat intersections as the coordinates, so a 14*14 grid
  //  - light up the LEDs adjacent to detected (low resistance)

  fill_solid(LEDs, NUM_LEDS, CRGB::Black);  // reset all LEDs before drawing

  // for every cell:
  for (int Y=0; Y<VELOSTAT_WIDTH; Y+=1) {
    for (int X=0; X<VELOSTAT_WIDTH; X+=1) {
      if (Pressure_m[Y][X] < 4095*SENSITIVITY) {  // if the cell is pressed enough,
        // light up the LEDs around it (n and n+1) (x,y)
        *LED_m[Y][X] = CRGB::Red;
        *LED_m[Y+1][X] = CRGB::Red;
        *LED_m[Y][X+1] = CRGB::Red;
        *LED_m[Y+1][X+1] = CRGB::Red;
        // the * changes the LEDs value corresponding to the LED_m value

      }
    }
  }



  FastLED.show();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








