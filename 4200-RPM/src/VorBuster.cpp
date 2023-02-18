#include <vex.h>
#include "VorBuster.h"

using namespace vex;

void VorBuster::spinIntake(double spd) {
  Intake.spin(fwd, spd*100, pct);
}
void VorBuster::spinFeeder(double spd) {
  Feeder.spin(fwd, spd*100, pct);
}
double VorBuster::getShooterRPM() {
    return (Shooter.velocity(rpm)+Shooter1.velocity(rpm)/2.0);
}
void VorBuster::spinShooter(double rpm) {
  if (rpm == 0) {
        Shooter.spin(fwd, 0, volt); Shooter1.spin(fwd, 0, volt);
        cumError = 0; prevTime = Brain.Timer;
        return;
    }

    unsigned int curTime = Brain.Timer;
    elapsedTime = curTime - prevTime;


    double input = getShooterRPM();
    double error = rpm - input;
    cumError += error*elapsedTime/1000;
    double rateError = (error-lastError)/elapsedTime;

    // double out = KP*error + KI*cumError + KD*rateError;
    // double out = KP*error + input*0.25;
    double out = KP*error + KD*rateError + input*127/600+BASE_MOTOR_POWER;
    ;

    lastError = error;
    prevTime = curTime;

  Shooter.spin(fwd, out, volt);
  Shooter1.spin(fwd, out, volt);
} 