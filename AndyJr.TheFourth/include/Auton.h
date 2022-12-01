#ifndef AUTON_H
#define AUTON_H

#include <vex.h>

class Auton {
  private:
    struct motorPos {
      double LF, LB, RF, RB;
    };
    double WasteDelay;
    double lastDeg, lastTime;// msec
    motorPos lastMotorPos;
    double getAvgMotorPos(double LF, double LB, double RF, double RB);
    double getAvgMotorError(double LFTarget, double LBTarget, double RFTarget, double RBTarget);
    double getRotError(double initRot, double targetRot);
    double getRotOverTime();// (d)deg/(d)msec

  public:
    Auton(double WasteDelay);
    void moveFwdPID(double dist, double spd, double distErrorMargin, double distKP, double dirErrorMargin, double dirKP, double moveDelay);
    void turn(double targetRot, double spd, double errorMargin, double KP, double iroc, double moveDelay);
    double getDistOverTime(); // (d)cm/(d)msec
};

#endif