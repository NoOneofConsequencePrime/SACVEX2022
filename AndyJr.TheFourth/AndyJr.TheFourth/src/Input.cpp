#include "main.h"
#include "robot-config.h"
#include "Input.h"

double Input::getJoyLX() {
    return (abs(master.get_analog(ANALOG_LEFT_X)) > DEADZONE_THRESHOLD)? master.get_analog(ANALOG_LEFT_X):0;
}
double Input::getJoyLY() {
    return (abs(master.get_analog(ANALOG_LEFT_Y)) > DEADZONE_THRESHOLD)? master.get_analog(ANALOG_LEFT_Y):0;
}
double Input::getJoyRX() {
    return (abs(master.get_analog(ANALOG_RIGHT_X)) > DEADZONE_THRESHOLD)? master.get_analog(ANALOG_RIGHT_X):0;
}
double Input::getJoyRY() {
    return (abs(master.get_analog(ANALOG_RIGHT_Y)) > DEADZONE_THRESHOLD)? master.get_analog(ANALOG_RIGHT_Y):0;
}
bool Input::getL1() {
    return master.get_digital(DIGITAL_L1);
}
bool Input::getL2() {
    return master.get_digital(DIGITAL_L2);
}
bool Input::getR1() {
    return master.get_digital(DIGITAL_R1);
}
bool Input::getR2() {
    return master.get_digital(DIGITAL_R2);
}
bool Input::getUp() {
    return master.get_digital(DIGITAL_UP);
}
bool Input::getDown() {
    return master.get_digital(DIGITAL_DOWN);
}
bool Input::getLeft() {
    return master.get_digital(DIGITAL_LEFT);
}
bool Input::getRight() {
    return master.get_digital(DIGITAL_RIGHT);
}
bool Input::getA() {
    return master.get_digital(DIGITAL_A);
}
bool Input::getB() {
    return master.get_digital(DIGITAL_B);
}
bool Input::getX() {
    return master.get_digital(DIGITAL_X);
}
bool Input::getY() {
    return master.get_digital(DIGITAL_Y);
}