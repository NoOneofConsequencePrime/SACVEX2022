#include <vex.h>
#include <algorithm>
#include <math.h>
#include "MecDrive.h"
#include "Input.h"

using namespace vex;

// Program Init

// Program Parameters

// Program Variables/Objects

void MecDrive::drive(double joyY, double joyX, double rotX, double spd, double strafeCorrection) {
  joyX *= strafeCorrection;
  double ratioCorrection = std::max(std::abs(joyY) + std::abs(joyX) + std::abs(rotX), 100.0);

  double LFPow = (joyY + joyX + rotX) / ratioCorrection * spd*100.0;
  double LBPow = (joyY - joyX + rotX) / ratioCorrection * spd*100.0;
  double RFPow = (joyY - joyX - rotX) / ratioCorrection * spd*100.0;
  double RBPow = (joyY + joyX - rotX) / ratioCorrection * spd*100.0;

  LF.spin(fwd, LFPow, pct);
  LB.spin(fwd, LBPow, pct);
  RF.spin(fwd, RFPow, pct);
  RB.spin(fwd, RBPow, pct);
}

void MecDrive::driveFwd(double spd) {
  LF.spin(fwd, spd*100.0, pct);
  LB.spin(fwd, spd*100.0, pct);
  RF.spin(fwd, spd*100.0, pct);
  RB.spin(fwd, spd*100.0, pct);
}