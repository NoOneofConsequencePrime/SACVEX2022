#include <vex.h>
#include <algorithm>
#include "Auton.h"

using namespace vex;

// Program Init

// Program Parameters

// Program Variables/Objects

void Auton::moveFwdPID(double dist, double spd, double distErrorMargin, double distKP, double dirErrorMargin, double dirKP, double moveDelay) {// cm, deg
  double targetRot = dist/(M_PI*10.16)*360, distErrorDeg = distErrorMargin/(M_PI*10.16)*360;
  double LFi = LF.position(deg), LBi = LB.position(deg), RFi = RF.position(deg), RBi = RB.position(deg);
  double LFf = LFi+targetRot, LBf = LBi+targetRot, RFf = RFi+targetRot, RBf = RBi+targetRot;
  double initDir = Gyro.rotation(deg);
  while (std::abs(getAvgMotorError(LFf, LBf, RFf, RBf)) > distErrorDeg) {
    double distError = getAvgMotorError(LFf, LBf, RFf, RBf)*distKP;
    double distNetError = distError;

    double dirError = (initDir-Gyro.rotation(deg))*dirKP;
    double dirNetError = dirError;

    double leftError = distNetError+dirNetError, rightError = distNetError-dirNetError;
    double maxError = std::max(std::abs(leftError), std::abs(rightError));
    leftError = leftError/maxError*spd*100.0; rightError = rightError/maxError*spd*100.0;

    LF.spin(fwd, leftError, pct);
    LB.spin(fwd, leftError, pct);
    RF.spin(fwd, rightError, pct);
    RB.spin(fwd, rightError, pct);
  }

  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
  wait(moveDelay, msec);
}

void Auton::turn(double targetRot, double spd, double errorMargin, double KP, double moveDelay) {
  double initDir = Gyro.rotation(deg);
  while (std::abs(getRotError(initDir, targetRot)) > errorMargin) {
    double error = getRotError(initDir, targetRot)*KP;
    double netError = (error)*spd;

    LF.spin(fwd, netError, pct);
    LB.spin(fwd, netError, pct);
    RF.spin(fwd, -netError, pct);
    RB.spin(fwd, -netError, pct);
  }

  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
  wait(moveDelay, msec);
}

// Helper Methods
double Auton::getAvgMotorError(double LFTarget, double LBTarget, double RFTarget, double RBTarget) {
  double LFError = LFTarget-LF.position(deg);
  double LBError = LBTarget-LB.position(deg);
  double RFError = RFTarget-RF.position(deg);
  double RBError = RBTarget-RB.position(deg);
  
  return (LFError+LBError+RFError+RBError)/4.0;
}

double Auton::getRotError(double initRot, double targetRot) {
  return targetRot-(Gyro.rotation(deg)-initRot);
}