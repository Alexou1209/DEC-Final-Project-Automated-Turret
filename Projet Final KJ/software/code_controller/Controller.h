#ifndef Controller

#define Controller

#define STRIP1_PIN 5
#define STRIP2_PIN 6
#define STRIP3_PIN 7
#define NUM_LEDS 3


#include <Adafruit_NeoPixel.h>  // For the Neopixels
#include <SPI.h>                // for the NRF24L01 module
#include <nRF24L01.h>
#include <RF24.h>

Adafruit_NeoPixel strip1(NUM_LEDS, STRIP1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(NUM_LEDS, STRIP2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(NUM_LEDS, STRIP3_PIN, NEO_GRB + NEO_KHZ800);

void vInitNeopixels();
void vInitNRF24L01();
void vEnvoyerTrame(int FlywheelSpeed, int FanSpeed, int Mode, int X, int Y, int Tir);
void vLireControleManette(int* FlywheelSpeed, int* FanSpeed, int* Mode, int* X, int* Y, int* Tir);
void vSetLedKnob(int iValeur, Adafruit_NeoPixel &strip);
void vReadJoystick(int* X, int* Y);
void vReadICM(int* X, int* Y);
void vAnimationLED();

#endif