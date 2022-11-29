#include <vex.h>
#include "Input.h"

using namespace vex;

// Program Init
#define Ct1 Controller1

void Input::setChannels(double threshold) {
  Ch1 = (Ct1.Axis1.position(pct) >= threshold || Ct1.Axis1.position(pct) <= -threshold)? Ct1.Axis1.position(pct) : 0;
  Ch2 = (Ct1.Axis2.position(pct) >= threshold || Ct1.Axis2.position(pct) <= -threshold)? Ct1.Axis2.position(pct) : 0;
  Ch3 = (Ct1.Axis3.position(pct) >= threshold || Ct1.Axis3.position(pct) <= -threshold)? Ct1.Axis3.position(pct) : 0;
  Ch4 = (Ct1.Axis4.position(pct) >= threshold || Ct1.Axis4.position(pct) <= -threshold)? Ct1.Axis4.position(pct) : 0;
}
void Input::setButtons() {
  leftHighTrig = Ct1.ButtonL1.pressing();
  leftLowTrig = Ct1.ButtonL2.pressing();
  rightHighTrig = Ct1.ButtonR1.pressing();
  rightLowTrig = Ct1.ButtonR2.pressing();
  A = Ct1.ButtonA.pressing();
  B = Ct1.ButtonB.pressing();
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
bool Input::getA() {
  return A;
}
bool Input::getB() {
  return B;
}