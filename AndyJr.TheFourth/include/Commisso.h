#ifndef COMMISSO_H
#define COMMISSO_H

class Commisso {
  private:
    bool RPMReached = 0;
  
  public:
    void spinIntake(double maxSpd), spinFeeder(double maxSpd), spinShooter(double maxSpd, double targetUncertainty);
};

#endif