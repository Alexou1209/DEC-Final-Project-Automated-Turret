/**********************************************************
* NRF24L01                                                *
* Fonctions pour l'utilisation du module NRF24L01         *
* Champoux Xavier, Dionne Alexandre                       *
*                                                         *
* Code Télécommande                                       *
*                                                         *
**********************************************************/
#include "Controller.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Objects
RF24 radio(10, 8);  // CE, CSN

//Variables
const byte address[6] = "00001";

void vInitNRF24L01(void) {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void vEnvoyerTrame(int FlywheelSpeed, int FanSpeed, int Mode, int X, int Y, int Tir) {
  int DataToSend[7] = { 0x24, 0, 0, 0, 0, 0, 0 };
  DataToSend[1] = FlywheelSpeed;
  DataToSend[2] = FanSpeed;
  DataToSend[3] = Mode;
  DataToSend[4] = X;
  DataToSend[5] = Y;
  DataToSend[6] = Tir;

  radio.write(&DataToSend, sizeof(DataToSend));
}