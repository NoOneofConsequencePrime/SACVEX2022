class Commisso {
  private:
    bool autonOverride = false;
    unsigned int curTIme, prevTime, elapsedTime;
    double kp = 0.48, ki = 0.001, kd = 2;
    double error, lastError, cumError, rateError;
  
  public:
    bool spinShooter(double spd);// rpm
    void spinIntake(double spd), spinRoller(double spd), spinFeeder(double spd);
    void setAutonOverride(bool autonOverride), resetShooterPID();
};