// hi! if you're wondering, I put some useful functions in functions.cpp
// this version of the template has ArduinoOTA! I thought it might be useful for game dev... if you don't wanna enter wifi stuff then use the other template, or there's another library that hosts a web interface on the microcontroller where you can upload code to it...

#include <Arduino.h>
#include <FastLED.h>
#include "functions.h"

#include <WiFi.h>          // Use <ESP8266WiFi.h> if you are using an ESP8266 board
#include <ArduinoOTA.h>


// enter your wifi details here to use OTA
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define HOSTNAME "super_cat_game"  // name that microcontroller uses to connect to others
#define PASSWORD "supersigm@67"  // password microcontroller uses to let people connect over wifi


//// variables ////
// LEDs
CRGB LEDs[NUM_LEDS];  // Linear array representing LED strip
CRGB* LED_m[LED_WIDTH][LED_WIDTH];  // LED matrix (will be reorganised from ^ linear array)
// LED_m[Y][X]

int Pressure_m[VELOSTAT_WIDTH][VELOSTAT_WIDTH];  // array of arrays storing pressure readings for the board
// Pressure_m[y][x] for the pressure reading at (x,y)


void setup() {


  //// FastLED ////
  init_LED_ptrs(LED_m, LEDs);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(LEDs, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2500);


  //// ArduinoOTA ////
  Serial.begin(115200);
  
  // 1. Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // 2. Optional configurations (Security and Identification)
  ArduinoOTA.setHostname(HOSTNAME); // Name that shows up in Arduino IDE
  ArduinoOTA.setPassword(PASSWORD);          // Protects device from unauthorized flashes

  // 3. Initialize the OTA service
  ArduinoOTA.begin();

  // put your setup code here, to run once:

  
}


void loop() {
  ArduinoOTA.handle();  // required for OTA; this may slow down the program, should probably remove this (and all the other OTA stuff for that matter) before finishing your project
  // put your main code here, to run repeatedly:
  // "*(LED_m[Y][X]) = CRGB:: " to set CRGB of LEDs
  

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
