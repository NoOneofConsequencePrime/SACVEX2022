class VorBuster {
  private:
    double KD = 0.03, BASE_MOTOR_POWER = 20;
    // const double KP = 0.6, KI = 0.17, KD = 0;
    // const double KP = 0.2, KI = 0.23, KD = 0;
    // const double KP = 0.3;
    uint32_t prevTime, elapsedTime;
    double lastError, cumError;
  
  public:
    void spinShooter(double rpm);// rpm
    void spinIntake(double spd), spinFeeder(double spd);// (1.0)
    double getShooterRPM();
    double KP = 1.2;
};