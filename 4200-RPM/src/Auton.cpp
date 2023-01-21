#include <vex.h>
#include <algorithm>
#include <float.h>
#include "Auton.h"

using namespace vex;

// Class Init
Auton::Auton(double wasteDelay, double distErrorMargin, double distKP, double ambientDistDer, double dirErrorMargin, double dirKP, double rotErrorMargin, double rotKP, double ambientRotDer, double moveDelay) {
  this->wasteDelay = wasteDelay;
  this->distErrorMargin = distErrorMargin;
  this->distKP = distKP;
  this->ambientDistDer = ambientDistDer;
  this->dirErrorMargin = dirErrorMargin;
  this->dirKP = dirKP;
  this->rotErrorMargin = rotErrorMargin;
  this->rotKP = rotKP;
  this->ambientRotDer = ambientRotDer;
  this->moveDelay = moveDelay;
}

// Program Parameters

// Program Variables/Objects

// Class Methods
void Auton::motorBrake(double moveDelay) {
  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
  wait(moveDelay, msec);
}

void Auton::moveFwd(double dist, double spd) {// cm, deg
  double targetRot = dist/(M_PI*10.2)*360, distErrorDeg = distErrorMargin/(M_PI*10.2)*360;
  double LFi = LF.position(deg), LBi = LB.position(deg), RFi = RF.position(deg), RBi = RB.position(deg);
  double LFf = LFi+targetRot, LBf = LBi+targetRot, RFf = RFi+targetRot, RBf = RBi+targetRot;
  double initDir = Gyro.rotation(deg);
  while (std::abs(getAvgMotorError(LFf, LBf, RFf, RBf)) > distErrorDeg || std::abs(getDistOverTime()) >= ambientDistDer) {
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

void Auton::turn(double targetRot, double spd) {
  double initDir = Gyro.rotation(deg);
  while (std::abs(getRotError(initDir, targetRot)) > rotErrorMargin || std::abs(getRotOverTime()) >= ambientRotDer) {
    double error = getRotError(initDir, targetRot)*rotKP;
    double netError = (error)*spd;

    LF.spin(fwd, -netError, pct);
    LB.spin(fwd, -netError, pct);
    RF.spin(fwd, netError, pct);
    RB.spin(fwd, netError, pct);
  }

  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
  wait(moveDelay, msec);
}

// Helper Methods
double Auton::getAvgMotorPos(double LF, double LB, double RF, double RB) {
  return (LF+LB+RF+RB)/4.0;
}

double Auton::getAvgMotorError(double LFTarget, double LBTarget, double RFTarget, double RBTarget) {
  double targetAvg = getAvgMotorPos(LFTarget, LBTarget, RFTarget, RBTarget);
  double curAvg = getAvgMotorPos(LF.position(deg), LB.position(deg), RF.position(deg), RB.position(deg));
  
  return targetAvg-curAvg;
}

double Auton::getRotError(double initRot, double targetRot) {
  return targetRot-(Gyro.rotation(deg)-initRot);
}

double Auton::getRotOverTime() {
  double dRot = Gyro.rotation(deg)-lastDeg, dTime = Brain.Timer-lastTime;
  lastDeg = Gyro.rotation(deg); lastTime = Brain.Timer;

  double dydx = dRot/dTime*1e6;
  if (dTime > wasteDelay) return 0;
  return dydx;
}

double Auton::getDistOverTime() {
  double curMotorAvg = getAvgMotorPos(LF.position(deg), LB.position(deg), RF.position(deg), RB.position(deg));
  double lastMotorAvg = getAvgMotorPos(lastMotorPos.LF, lastMotorPos.LB, lastMotorPos.RF, lastMotorPos.RB);
  double dDist = curMotorAvg-lastMotorAvg, dTime = Brain.Timer-lastTime;
  lastMotorPos = {LF.position(deg), LB.position(deg), RF.position(deg), RB.position(deg)}; lastTime = Brain.Timer;

  double dydx = dDist/dTime*1e2;
  if (dTime > wasteDelay) return 0;
  return dydx;
}