#include "main.h"
#include "robot-config.h"
#include "Commisso.h"

void Commisso::spinIntake(double spd) {
    double volt = spd*127;
    intakeA.move_velocity(volt); intakeB.move_velocity(volt);
}
void Commisso::extendIndexer(bool pneuState) {
    indexer.set_value(!pneuState);
}
void Commisso::extendExpansion(bool pneuState) {
    expansion.set_value(pneuState);
}
double Commisso::getShooterRPM() {
    return (leftShooter.get_actual_velocity()+rightShooter.get_actual_velocity())/2.0;
}
void Commisso::spinShooter(double rpm) {
    if (rpm == 0) {
        leftShooter.move(0); rightShooter.move(0);
        return;
    }

    unsigned int curTime = millis();
    elapsedTime = curTime-prevTime;

    double input = getShooterRPM();
    double error = rpm - input;
    double rateError = (error-lastError)/elapsedTime;

    double out = KP*error + KD*rateError + input*127/600+BASE_MOTOR_POWER;

    lastError = error;
    prevTime = curTime;

    leftShooter.move(out); rightShooter.move(out);
}