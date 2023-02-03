#ifndef AUTON_H
#define AUTON_H

class Auton {
  private:
    const double DIST_UC_RANGE = 3.0, DIST_RATE_ERROR = 0.0;// +/- cm
    const double ROT_UC_RANGE = 1.0, ROT_RATE_ERROR = 0.0;// +/- degs
    const double MKP = 0.0, MKI = 0.0, MKD = 0.0;
    const double TKP = 0.0, TKI = 0.0, TKD = 0.0;
    unsigned int prevTime, elapsedTime;
    double lastError, cumError;
    bool chkDistRange(), chkRotRange(double target);// continue pid?
  
  public:
    double getPID(double input, double setPoint, double KP, double KI, double KD);// wtv (based on input)
    void pidMove(double dist, double dir, double spd);// cm, degs, -1.0 ~ 1.0
    void pidTurn(double target, double spd);// degs, -1.0 ~ 1.0
};

#endif