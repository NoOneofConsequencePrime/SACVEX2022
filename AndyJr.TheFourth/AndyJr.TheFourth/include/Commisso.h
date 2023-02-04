#ifndef COMMISSO_H
#define COMMISSO_H

class Commisso {
  private:
    const double KP = 0.6, KD = 0.2, BASE_MOTOR_POWER = 20;// volt
    unsigned int prevTime, elapsedTime;
    double lastError;
  
  public:
    void spinShooter(double rpm);// rpm
    void spinIntake(double spd);// -1.0 ~ 1.0
    void extendIndexer(bool pneuState);// true(load disc) false(extend)
    void extendExpansion(bool pneuState);// false(resting) true(release)
    double getShooterRPM();
    
};

void tracking_commisso(void* ignore);
void shoot(double rpm), intake(double spd), index(bool pneuState), expand(bool pneuState);

#endif