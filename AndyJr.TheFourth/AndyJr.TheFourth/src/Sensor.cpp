#include "main.h"
#include "robot-config.h"
#include "Sensor.h"

void Sensor::resetEncoders() {
    encoder.reset();
}
double Sensor::getEncoderDist() {
    return encoder.get_value()/360.0*ENCODER_WHEEL_DIAMETER*M_PI;
}
// void Sensor::resetGyro() {
//     gyro.reset();
// }
double Sensor::getRot() {
    return gyro.get_rotation();
}