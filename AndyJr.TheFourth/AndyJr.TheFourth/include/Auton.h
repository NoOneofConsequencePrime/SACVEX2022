#ifndef AUTON_H
#define AUTON_H

class Auton {
  private:
    const double DIST_UC_RANGE = 3.0, DIST_RATE_ERROR = 0.0;// +/- cm
    const double ROT_UC_RANGE = 0.5, ROT_RATE_ERROR = 0.1;// +/- degs
    const double MKP = 0.0, MKI = 0.0, MKD = 0.0;
    const double RKP = 0.022, RKI = 0.0, RKD = 0.0;
    double prevTime, elapsedTime;
    double lastError, cumError;
    bool chkDistRange(), chkRotRange(double target);// continue pid?
  
  public:
    double getPID(double input, double setPoint, double KP, double KI, double KD);// wtv (based on input)
    void pidMove(double dist, double dir, double spd);// cm, degs, -1.0 ~ 1.0
    void pidTurn(double target, double spd);// degs, -1.0 ~ 1.0
};

#endif