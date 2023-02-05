#include "main.h"
#include "robot-config.h"
#include "Commisso.h"

double taskRPM;// rpm
double taskIntake;// spd -1.0 ~ 1.0
bool taskIndexer;
bool taskExpansion;

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
        cumError = 0; prevTime = millis();
        return;
    }

    unsigned int curTime = millis();
    elapsedTime = curTime - prevTime;

    double input = getShooterRPM();
    double error = rpm - input;
    cumError += error*elapsedTime/1000;
    double rateError = (error-lastError)/elapsedTime;

    // double out = KP*error + KI*cumError + KD*rateError;
    // double out = KP*error + input*0.25;
    double out = KP*error + KD*rateError + input*127/600+BASE_MOTOR_POWER;

    lastError = error;
    prevTime = curTime;

    leftShooter.move(out); rightShooter.move(out);
}

void tracking_commisso(void* ignore) {
    Commisso tmp;
    while (1) {
        tmp.spinShooter(taskRPM);
        tmp.spinIntake(taskIntake);
        tmp.extendIndexer(taskIndexer);
        tmp.extendExpansion(taskExpansion);
        print(1, "%.1f", tmp.getShooterRPM());
        printf("%.1f\n", tmp.getShooterRPM());

        delay(10);
    }
}

void shoot(double rpm) {
    taskRPM = rpm;
}
void intake(double spd) {
    taskIntake = spd;
}
void index(bool pneuState) {
    taskIndexer = pneuState;
}
void expand(bool pneuState) {
    taskExpansion = pneuState;
}