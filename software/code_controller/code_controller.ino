/**********************************************************
* Projet Guimbarde                                       *
* Fichier principale pour le code de la télécommande      *
* Champoux Xavier, Dionne Alexandre                       *
*                                                         *
* Code Télécommande                                       *
*                                                         *
**********************************************************/

// Includes
#include "Controller.h"


//Variables

int FlywheelSpeed;
int FanSpeed;
int Mode; 
int X;
int Y;
int Tir;




//Main
void setup() {

  pinMode(PIN_PE0, INPUT);
  pinMode(PIN_PD4, INPUT);  //2 switch manette
  pinMode(PIN_PD3, INPUT);

  vInitNeopixels();
  vInitNRF24L01();
  vInitICM20648();
}

void loop() {

  vLireControleManette(&FlywheelSpeed, &FanSpeed, &Mode, &X, &Y, &Tir);

  vEnvoyerTrame(FlywheelSpeed, FanSpeed, Mode, X, Y, Tir);
}
