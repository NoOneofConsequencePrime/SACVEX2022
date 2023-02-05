#ifndef COMMISSO_H
#define COMMISSO_H

class Commisso {
  private:
    const double KP = 0.2, KD = 0.05, BASE_MOTOR_POWER = 20;
    // const double KP = 0.6, KI = 0.17, KD = 0;
    // const double KP = 0.2, KI = 0.23, KD = 0;
    // const double KP = 0.3;
    unsigned int prevTime, elapsedTime;
    double lastError, cumError;
  
  public:
    void spinShooter(double rpm);// rpm
    void spinIntake(double spd);// -1.0 ~ 1.0
    void extendIndexer(bool pneuState);// true(load disc) false(extend)
    void extendExpansion(bool pneuState);// false(resting) true(release)
    double getShooterRPM();
};

void tracking_commisso(void* ignore);
void shoot(double rpm);
void intake(double spd);
void index(bool pneuState);
void expand(bool pneuState);

#endif