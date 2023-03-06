#include "main.h"
#include "robot-config.h"
#include "Sensor.h"

void Sensor::resetEncoders() {
    encoder.reset();
}
double Sensor::getEncoderDist() {
    return encoder.get_value()/360.0*ENCODER_WHEEL_DIAMETER*M_PI;
}
void Sensor::resetGyro() {
    gyro.reset();
}
double Sensor::getRot() {
    return gyro.get_rotation();
}
void Sensor::setOptLED(double val) {
    int brightness = val*100.0;
    optL.set_led_pwm(brightness);
    optR.set_led_pwm(brightness);
}
int Sensor::getHueL() {
    setOptLED(0.7);
    double hue = optL.get_hue();
    if (optL.get_proximity() < 250) return -1;
    if (hue >= 210 && hue <= 270) return 1;
    else if (hue >= 330 || hue <= 30) return 0;
    
    return -1;
}
int Sensor::getHueR() {
    setOptLED(0.7);
    double hue = optR.get_hue();
    if (optR.get_proximity() < 250) return -1;
    if (hue >= 210 && hue <= 270) return 1;
    else if (hue >= 330 || hue <= 30) return 0;
    
    return -1;
}
int Sensor::getMagDepth() {
    int dep = magSense.get_value();
    if (dep >= 80) return 0;
    else if (dep <= 70 && dep >= 60) return 1;
    else if (dep <= 50 && dep >= 40) return 2;
    else if (dep < 40) return 3;

    return dep < 80;
}