#ifndef COMMISSO_H
#define COMMISSO_H

class Commisso {
  private:
    const double KP = 0.25, KI = 3.5, KD = 0.1, BASE_MOTOR_POWER = 20;
    // const double KP = 0.21, KI = 0, KD = 0, BASE_MOTOR_POWER = 20;
    unsigned int prevTime, elapsedTime;
    double lastError, cumError;
  public:
    void spinShooter(double rpm);// rpm (0.0 ~ 600.0)
    void spinIntake(double spd);// -1.0 ~ 1.0
    // void extendIndexer(bool pneuState);// true(load disc) false(retract)
    void spinIndexer(double rpm);// rpm (-200.0 ~ 200.0)
    void extendExpansion(bool pneuState);// false(resting) true(release)
};

void tracking_commisso(void* ignore);
void shoot(double rpm);
void intake(double spd);
// void index(bool pneuState);
void index(double rpm);
void expand(bool pneuState);

#endif