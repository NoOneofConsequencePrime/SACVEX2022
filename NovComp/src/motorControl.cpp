#include <vex.h>
#include <algorithm>
#include <math.h>
#include "motorControl.h"
#include "controllerScript.h"

using namespace vex;


void motorControl::drive(double joystickY, double joystickX, double rotationX, double maxSpeed, double strafeCorrection) {
  joystickX *= strafeCorrection;

  double maxValueStatic = std::max(std::abs(joystickY) + std::abs(joystickX) + std::abs(rotationX), 100.0);

  double FLPow = (joystickY + joystickX + rotationX) / maxValueStatic * maxSpeed;
  double FRPow = (joystickY - joystickX - rotationX) / maxValueStatic * maxSpeed;
  double BLPow = (joystickY - joystickX + rotationX) / maxValueStatic * maxSpeed;
  double BRPow = (joystickY + joystickX - rotationX) / maxValueStatic * maxSpeed;

  FL.spin(forward, FLPow, pct);
  FR.spin(forward, FRPow, pct);
  BL.spin(forward, BLPow, pct);
  BR.spin(forward, BRPow, pct);




}
