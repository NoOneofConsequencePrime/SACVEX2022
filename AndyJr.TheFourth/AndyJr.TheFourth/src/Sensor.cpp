#include "main.h"
#include "robot-config.h"
#include "Sensor.h"

void Sensor::resetEncoders() {
    xEncoder.reset(); yEncoder.reset();
}
double Sensor::getXEncoderDist() {
    return xEncoder.get_value()/360.0*ENCODER_WHEEL_DIAMETER*M_PI;
}
double Sensor::getYEncoderDist() {
    return yEncoder.get_value()/360.0*ENCODER_WHEEL_DIAMETER*M_PI;
}
// void Sensor::resetGyro() {
//     gyro.reset();
// }
double Sensor::getRot() {
    return gyro.get_rotation();
}
double Sensor::getDisplacement() {
    return sqrt(getXEncoderDist()*getXEncoderDist()+getYEncoderDist()*getYEncoderDist());
}