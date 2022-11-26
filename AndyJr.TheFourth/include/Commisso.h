#ifndef COMMISSO_H
#define COMMISSO_H

class Commisso {
  private:
    bool RPMReached = 0;
  
  public:
    void spinIntake(double spd), spinFeeder(double spd), spinShooter(double spd, double targetUncertainty);
};

#endif