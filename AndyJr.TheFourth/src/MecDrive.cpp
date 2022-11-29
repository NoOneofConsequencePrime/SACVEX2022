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

<<<<<<< HEAD:AndyJr.TheFourth/src/MecDrive.cpp
  LF.spin(fwd, LFPow, pct);
  LB.spin(fwd, LBPow, pct);
  RF.spin(fwd, RFPow, pct);
  RB.spin(fwd, RBPow, pct);
=======
  LF.spin(forward, LFPow, pct);
  LB.spin(forward, LBPow, pct);
  RF.spin(forward, RFPow, pct);
  RB.spin(forward, RBPow, pct);
>>>>>>> parent of e400e9a (Merge branch 'bryan' of https://github.com/NoOneofConsequencePrime/SACVEX2022 into bryan):AndyJrTheFourth/src/MecDrive.cpp
}