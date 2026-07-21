#include <Arduino.h>


#define VELOSTAT_WIDTH 14
#define LED_WIDTH 13

const int Channel_m[2][16] = {
  {1,0,3,2,5,4,7,6,14,15,12,13,10,11,8,9},
  {7,6,5,4,3,2,1,0,8,9,10,11,12,13,14,15}
};  // Set A (x) followed by Set B (y)
// (0,0) is top left; Y goes down, X goes right
// matrices follow Matrix[Y][X]

void setup() {
  // put your setup code here, to run once:
  
  int Pixel_m[LED_WIDTH][LED_WIDTH][3];
  int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH];

}

void loop() {
  Pressure_m = Read_pressure());
  // put your main code here, to run repeatedly:

  // add led functionality
  // make the press test, knowing Velostat represents space between LEDS
  // DO NOT CONVERT COORDS, VELOSTAT AREA IS LARGER THAN LEDS

  Send_to_LEDs(Pixel_m);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int[13][13] Read_pressure() {
  int[VELOSTAT_WIDTH][VELOSTAT_WIDTH] Data;
  int Channel;

  for (int Y=0; Y<VELOSTAT_WIDTH, Y+=1) {

    Channel = Channel_m[1][Y]
    
    digitalWrite(S0b, Channel & 0x01);
    digitalWrite(S1b, (Channel >> 1) & 0x01);
    digitalWrite(S2b, (Channel >> 2) & 0x01);
    digitalWrite(S3b, (Channel >> 3) & 0x01);

    for (int X=0; X<VELOSTAT_WIDTH, X+=1) {

      Channel = Channel_m[0][X]
      
      digitalWrite(S0a, Channel & 0x01);
      digitalWrite(S1a, (Channel >> 1) & 0x01);
      digitalWrite(S2a, (Channel >> 2) & 0x01);
      digitalWrite(S3a, (Channel >> 3) & 0x01);

      Data[Y][X] = analogRead(A0);

    }
  }

  return Data
}

void Send_to_LEDs(Pixel_m) {
  // command the LED strip based on Pixel_m, the matrix of rgb values
  // show the pixels on the screen
  
  bool right = true;

  for (int Y=0; Y<LED_WIDTH, Y+=1) {
    
    for (int X=0; X<LED_WIDTH, X+=1) {

      if(right = true) {
        right = false;

        //set pixels, moving right
        LED (Y*LED_WIDTH + X) <- Pixel_m[Y][X]

      }
      else {
        right = true;

        //set pixels, moving left
        LED ((Y+1)*LED_WIDTH - X - 1) <- Pixel_m[Y][X]

      }

    }
    
  }

  // show pixels

  return
}
