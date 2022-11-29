#include <vex.h>
#include <algorithm>
#include <math.h>
#include "MecDrive.h"
#include "Input.h"

using namespace vex;

// Program Init

// Program Parameters

// Program Variables/Objects

void MecDrive::drive(double joyY, double joyX, double rotX, double maxSpd, double strafeCorrection) {
  joyX *= strafeCorrection;
  double ratioCorrection = std::max(std::abs(joyY) + std::abs(joyX) + std::abs(rotX), 100.0);

  double LFPow = (joyY + joyX + rotX) / ratioCorrection * maxSpd;
  double LBPow = (joyY - joyX + rotX) / ratioCorrection * maxSpd;
  double RFPow = (joyY - joyX - rotX) / ratioCorrection * maxSpd;
  double RBPow = (joyY + joyX - rotX) / ratioCorrection * maxSpd;

  LF.spin(fwd, LFPow, pct);
  LB.spin(fwd, LBPow, pct);
  RF.spin(fwd, RFPow, pct);
  RB.spin(fwd, RBPow, pct);
}