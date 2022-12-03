#ifndef AUTON_H
#define AUTON_H

#include <vex.h>

class Auton {
  private:
    struct motorPos {
      double LF, LB, RF, RB;
    };
    double wasteDelay, distErrorMargin, distKP, ambientDistDer, dirErrorMargin, dirKP, rotErrorMargin, rotKP, ambientRotDer, moveDelay;
    double lastDeg, lastTime;// msec
    motorPos lastMotorPos;
    double getAvgMotorPos(double LF, double LB, double RF, double RB);
    double getAvgMotorError(double LFTarget, double LBTarget, double RFTarget, double RBTarget);
    double getRotError(double initRot, double targetRot);
    double getRotOverTime();// (d)deg/(d)msec
    double getDistOverTime(); // (d)cm/(d)msec

  public:
    Auton(double wasteDelay, double distErrorMargin, double distKP, double ambientDistDer, double dirErrorMargin, double dirKP, double rotErrorMargin, double rotKP, double ambientRotDer, double moveDelay);
    void motorBrake(double moveDelay);
    void moveFwd(double dist, double spd);
    void turn(double targetRot, double spd);
};

#endif