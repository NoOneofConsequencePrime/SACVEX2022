#ifndef AUTON_H
#define AUTON_H

class Auton {
  private:
    double getAvgMotorError(double LFTarget, double LBTarget, double RFTarget, double RBTarget);
    double getDiff(double a, double b);
    double getRotError(double initRot, double targetRot);

  public:
    void moveFwdPID(double dist, double spd, double distErrorMargin, double distKP, double dirErrorMargin, double dirKP, double moveDelay);
    void turn(double targetRot, double spd, double errorMargin, double KP, double moveDelay);
};

#endif