/*
  Velocity.cpp - Read from the I2C pressure sensor and convert
  that value into a usable MIDI velocity.
*/

#include <Wire.h>
#include "Velocity.h"

Velocity::Velocity() {
  _baseline = 0;
}

void Velocity::init() {
  Wire1.setSDA(_SDA_PIN);
  Wire1.setSCL(_SCL_PIN);
  Wire1.begin();
  _baseline = _getPressure();
}

int Velocity::getVelocity() {
  return min((_getPressure() - _baseline)/_PRESSURE_SCALING_FACTOR, 127);
}

int Velocity::_getPressure() {
  // Pressure reading is 2 bytes
  int numBytes = 2;
  Wire1.requestFrom(_ADDR_PRESSURE_SENSOR, numBytes);
  if (Wire1.available() == numBytes) {
    int highByte = Wire1.read();
    int lowByte = Wire1.read();
    int result = (highByte << 8) | lowByte;
    result -= 2048;  // Adjust to match the sensor's 12-bit range centered at 2048
    return result;
  }
  return 0;
}