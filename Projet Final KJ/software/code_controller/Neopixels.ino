#include "Controller.h"
#include <Adafruit_NeoPixel.h>

void vInitNeopixels(void) {
  strip1.begin();
  strip2.begin();
  strip3.begin();

  strip1.setBrightness(10);
  strip2.setBrightness(10);
  strip3.setBrightness(10);

  strip1.show();
  strip2.show();
  strip3.show();
}


void vSetLedKnob(int iValeur, Adafruit_NeoPixel &strip) {
  if (iValeur == 0) {
    strip.setPixelColor(2, 0);
    strip.setPixelColor(1, 0);
    strip.setPixelColor(0, 0);
  }
  if (iValeur == 1) {
    strip.setPixelColor(2, strip.Color(255, 0, 128));
    strip.setPixelColor(1, 0);
    strip.setPixelColor(0, 0);
  }
  if (iValeur == 2) {
    strip.setPixelColor(2, strip.Color(255, 0, 128));
    strip.setPixelColor(1, strip.Color(255, 0, 128));
    strip.setPixelColor(0, 0);
  }
  if (iValeur == 3) {
    strip.setPixelColor(2, strip.Color(255, 0, 128));
    strip.setPixelColor(1, strip.Color(255, 0, 128));
    strip.setPixelColor(0, strip.Color(255, 0, 128));
  }
  strip.show();
}



void vAnimationLED() {
  static unsigned long lastUpdate = 0;
  static int currentPixel = 3 - 1;  // Start at last pixel

  unsigned long now = millis();
  if (now - lastUpdate >= 250) {
    lastUpdate = now;

    // Clear all pixels
    strip1.clear();

    // Light up only the current pixel
    strip1.setPixelColor(currentPixel, strip1.Color(255, 0, 1228));
    strip1.show();

    // Move to the previous pixel, loop back after 0
    currentPixel--;
    if (currentPixel < 0) {
      currentPixel = 3 - 1;
    }
  }
}