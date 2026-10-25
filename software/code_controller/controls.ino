#include "Controller.h"




void vLireControleManette(int* FlywheelSpeed, int* FanSpeed, int* Mode, int* X, int* Y, int* Tir) {
  *FanSpeed = iReadADC(0);
  *FlywheelSpeed = constrain(map(iReadADC(1), 0, 1000, 0, 3), 0, 3);

  vSetLedKnob(constrain(map(iReadADC(0), 0, 1000, 0, 3), 0, 3), strip2);
  vSetLedKnob(*FlywheelSpeed, strip3);


  if (digitalRead(PIN_PE0) == 0) {
    *Tir = 1;
    vAnimationLED();
  } else {
    *Tir = 0;
    strip1.clear();
    strip1.show();
  }

  if (digitalRead(PIN_PD3) == 0) {
    vReadJoystick(X, Y);
  } else {
    vReadICM(X, Y);
  }
  if (digitalRead(PIN_PD4) == 0) {
    *Mode = 1;
  } else {
    *Mode = 0;
  }
}


int iReadADC(int iADC) {
  if (iADC == 0) { return analogRead(A0); }
  if (iADC == 1) { return analogRead(A1); }
  if (iADC == 6) { return analogRead(A6); }
  if (iADC == 7) { return analogRead(A7); }
}

void vReadJoystick(int* X, int* Y) {
  *X = CheckIncline(iReadADC(6));
  *Y = CheckIncline(iReadADC(7));
}

int CheckIncline(int iValeur) {
  if (iValeur >= 900) { return 1; }
  if (iValeur >= 700 && iValeur < 900) { return 2; }
  if (iValeur >= 600 && iValeur < 700) { return 3; }
  if (iValeur >= 400 && iValeur < 600) { return 4; }
  if (iValeur < 400) { return 5; }
}