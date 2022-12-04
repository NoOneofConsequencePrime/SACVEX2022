#include <vex.h>
#include "controllerScript.h"

using namespace vex;

#define controllerObject Controller1

void controllerScript::setChannels(double threshold) {
  Chan1 = (Controller1.Axis4.position(pct) >= threshold || Controller1.Axis4.position(pct) <= threshold)? Controller1.Axis4.position(pct) : 0;
  Chan2 = (Controller1.Axis3.position(pct) >= threshold || Controller1.Axis3.position(pct) <= threshold)? Controller1.Axis3.position(pct) : 0;
  Chan3 = (Controller1.Axis2.position(pct) >= threshold || Controller1.Axis2.position(pct) <= threshold)? Controller1.Axis2.position(pct) : 0;
  Chan4 = (Controller1.Axis1.position(pct) >= threshold || Controller1.Axis1.position(pct) <= threshold)? Controller1.Axis1.position(pct) : 0;
}

void controllerScript::setButtons() {
  leftTrigTop = Controller1.ButtonL1.pressing();
  leftTrigDown = Controller1.ButtonL2.pressing();
  rightTrigTop = Controller1.ButtonR1.pressing();
  rightTrigDown = Controller1.ButtonR2.pressing();
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

bool controllerScript::getLeftTrigTop() {
  return leftTrigTop;
}

bool controllerScript::getLeftTrigDown(){
  return leftTrigDown;
}

bool controllerScript::getRightTrigTop(){
  return rightTrigTop;
}

bool controllerScript::getRightTrigDown(){
  return rightTrigDown;
} 