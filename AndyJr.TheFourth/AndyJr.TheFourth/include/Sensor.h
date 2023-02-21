#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  private:
    const double ENCODER_WHEEL_DIAMETER = 6.985;// cm
  
  public:
    void resetEncoders();
    double getEncoderDist();// cm
    // void resetGyro();
    double getRot();
};

#endif