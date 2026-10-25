#include "Controller.h"
#include <Wire.h>

#define ICM20648_ADDR 0x68
#define PWR_MGMT_1 0x06
#define WHO_AM_I 0x00
#define ACCEL_XOUT_H 0x2D
#define ACCEL_YOUT_H 0x2F




//Constant
const int16_t accMin = -16000;
const int16_t accMax = 16000;





void vInitICM20648() {
  Wire.begin();
  //Init ICM20648
  // Wake up sensor
  writeRegister(PWR_MGMT_1, 0x01);  // Use best clock source

  // Check communication
  Wire.beginTransmission(ICM20648_ADDR);
  Wire.write(WHO_AM_I);
  Wire.endTransmission(false);
  Wire.requestFrom(ICM20648_ADDR, 1);
  uint8_t id = Wire.read();

  if (id != 0xE0) {
    while (1)
      ;
  }
}

void writeRegister(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(ICM20648_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void vReadICM(int* X, int* Y) {
  int16_t ax = read16(ACCEL_XOUT_H);
  int16_t ay = read16(ACCEL_YOUT_H);

  *X = mapToRange(ax, accMin, accMax);
  *Y = mapToRange(ay, accMin, accMax);
}

int16_t read16(uint8_t reg) {
  Wire.beginTransmission(ICM20648_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)ICM20648_ADDR, (uint8_t)2);
  return (Wire.read() << 8) | Wire.read();
}

// Maps raw accelerometer values (16-bit) to range [0–5]
int mapToRange(int16_t val, int16_t minVal, int16_t maxVal) {
  val = constrain(val, minVal, maxVal);
  return map(val, minVal, maxVal, 0, 5);
}