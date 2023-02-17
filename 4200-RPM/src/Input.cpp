#include <vex.h>
#include "Input.h"

using namespace vex;

// Program Init
#define Ct1 Controller1

void Input::setChannels(double deadzone) {
  Ch1 = (Ct1.Axis1.position(pct) >= deadzone || Ct1.Axis1.position(pct) <= -deadzone)? Ct1.Axis1.position(pct) : 0;
  Ch2 = (Ct1.Axis2.position(pct) >= deadzone || Ct1.Axis2.position(pct) <= -deadzone)? Ct1.Axis2.position(pct) : 0;
  Ch3 = (Ct1.Axis3.position(pct) >= deadzone || Ct1.Axis3.position(pct) <= -deadzone)? Ct1.Axis3.position(pct) : 0;
  Ch4 = (Ct1.Axis4.position(pct) >= deadzone || Ct1.Axis4.position(pct) <= -deadzone)? Ct1.Axis4.position(pct) : 0;
}
void Input::setButtons() {
  leftHighTrig = Ct1.ButtonL1.pressing();
  leftLowTrig = Ct1.ButtonL2.pressing();
  rightHighTrig = Ct1.ButtonR1.pressing();
  rightLowTrig = Ct1.ButtonR2.pressing();
  buttonA = Ct1.ButtonA.pressing();
  buttonB = Ct1.ButtonB.pressing();
  buttonX = Ct1.ButtonX.pressing();
  buttonY = Ct1.ButtonY.pressing();
  buttonUp = Ct1.ButtonUp.pressing();
  buttonDown = Ct1.ButtonDown.pressing();
  buttonLeft = Ct1.ButtonLeft.pressing();
  buttonRight = Ct1.ButtonRight.pressing();
}

double Input::getCh1() {
  return Ch1;
}
double Input::getCh2() {
  return Ch2;
}
double Input::getCh3() {
  return Ch3;
}
double Input::getCh4() {
  return Ch4;
}
bool Input::getLeftHighTrig() {
  return leftHighTrig;
}
bool Input::getLeftLowTrig() {
  return leftLowTrig;
}
bool Input::getRightHighTrig() {
  return rightHighTrig;
}
bool Input::getRightLowTrig() {
  return rightLowTrig;
}
bool Input::getButtonA() {
  return buttonA;
}
bool Input::getButtonB() {
  return buttonB;
}
bool Input::getButtonX() {
  return buttonX;
}
bool Input::getButtonY() {
  return buttonY;
}
bool Input::getButtonUp() {
  return buttonUp;
}
bool Input::getButtonDown() {
  return buttonDown;
}
bool Input::getButtonLeft() {
  return buttonLeft;
}
bool Input::getButtonRight() {
  return buttonRight;
}