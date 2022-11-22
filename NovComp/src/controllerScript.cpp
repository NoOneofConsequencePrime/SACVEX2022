#include <vex.h>
#include "controllerScript.h"

using namespace vex;

#define controllerObject Controller1

void controllerScript::setChannels(double threshold) {
  Chan1 = (Controller1.Axis1.position(pct) >= threshold || Controller1.Axis1.position(pct) <= threshold)? Controller1.Axis1.position(pct) : 0;
  Chan2 = (Controller1.Axis2.position(pct) >= threshold || Controller1.Axis2.position(pct) <= threshold)? Controller1.Axis2.position(pct) : 0;
  Chan3 = (Controller1.Axis3.position(pct) >= threshold || Controller1.Axis3.position(pct) <= threshold)? Controller1.Axis3.position(pct) : 0;
  Chan4 = (Controller1.Axis4.position(pct) >= threshold || Controller1.Axis4.position(pct) <= threshold)? Controller1.Axis4.position(pct) : 0;
}

void controllerScript::setButtons() {
  leftTrigTop = Controller1.ButtonL1.pressing();
}

double controllerScript::getChan1() {
  return Chan1;
}
double controllerScript::getChan2() {
  return Chan2;
}
double controllerScript::getChan3() {
  return Chan3;
}
double controllerScript::getChan4() {
  return Chan4;
}

double controllerScript::getLeftTrigTop() {
  return leftTrigTop;
}