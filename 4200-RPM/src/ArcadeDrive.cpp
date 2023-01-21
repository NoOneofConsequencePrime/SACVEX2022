#include <vex.h>
#include <math.h>
#include <algorithm>
#include "ArcadeDrive.h"

using namespace vex;

void ArcadeDrive::drive(double joyY, double rotX, double spd) {
  LF.setStopping(brake);
  LB.setStopping(brake);
  RF.setStopping(brake);
  RB.setStopping(brake);

  double ratioCorrection = std::max(std::abs(joyY)+std::abs(rotX), 100.0);

  double LFPow = (joyY-rotX) / ratioCorrection * spd*100.0;
  double LBPow = (joyY-rotX) / ratioCorrection * spd*100.0;
  double RFPow = (joyY+rotX) / ratioCorrection * spd*100.0;
  double RBPow = (joyY+rotX) / ratioCorrection * spd*100.0;

  LF.spin(fwd, LFPow, pct);
  LB.spin(fwd, LBPow, pct);
  RF.spin(fwd, RFPow, pct);
  RB.spin(fwd, RBPow, pct);
}