/*
  Velocity.h - Read from the I2C pressure sensor and convert
  that value into a usable MIDI velocity.
*/
#ifndef Velocity_h
#define Velocity_h

class Velocity
{
  public:
    Velocity();
    void init();
    int getVelocity();
  private:
    int _getPressure();
    int _baseline;
    int _sensorPin;
    float _pressureScalingFactor;

    const unsigned int _SDA_PIN = 2;
    const unsigned int _SCL_PIN = 3;
    const int _ADDR_PRESSURE_SENSOR = 0x4D;
    const float _PRESSURE_SCALING_FACTOR = 3.0;
};

#endif
