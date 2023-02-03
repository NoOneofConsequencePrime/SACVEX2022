class Commisso {
  private:
    const double KP = 0.6, KD = 0.2, BASE_MOTOR_POWER = 20;// volt
    bool autonOverride = false, rpmReached = false;
    unsigned int prevTime, elapsedTime;
    double lastError;
  
  public:
    void spinShooter(double rpm);// rpm
    void spinIntake(double spd), spinRoller(double spd);// -1.0 ~ 1.0
    void extendIndexer(bool pneuState);// true(load disc) false(extend)
    void extendExpansion(bool pneuState);// false(resting) true(release)
    void setAutonOverride(bool autonOverride);
    double getShooterRPM();
};