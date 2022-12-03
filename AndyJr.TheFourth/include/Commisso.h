#ifndef COMMISSO_H
#define COMMISSO_H

class Commisso {
  private:
    bool RPMReached = 0, autonOverride = false;
  
  public:
    void spinIntake(double spd), spinRoller(double spd), spinFeeder(double spd), spinShooter(double spd, double targetUncertainty);
    void setAutonOverride(bool autonOverride);
};

#endif