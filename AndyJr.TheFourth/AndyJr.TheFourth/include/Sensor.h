#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  private:
    const double ENCODER_WHEEL_DIAMETER = 6.985;// cm
    // const int dep[4] = {90, 70, 50, 30};// mm, "greater than" disc cnt = idx
  
  public:
    void resetEncoders();
    double getEncoderDist();// cm
    void resetGyro();
    double getRot();
    void setOptLED(double val);// 0.0 ~ 1.0
    int getHueL(), getHueR();// 0 blue up [220, 260],  1 red up [340, 20], -1 invalid
    int getMagDepth();// cnt (<80 mm: have disk)
};

#endif