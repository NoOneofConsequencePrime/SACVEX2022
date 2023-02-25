#include "main.h"
#include "robot-config.h"
#include "Commisso.h"

double taskRPM;// rpm
double taskIntake;// spd -1.0 ~ 1.0
// bool taskIndexer;
double taskIndex;// rpm -200.0 ~ 200.0
bool taskExpansion;

void Commisso::spinIntake(double spd) {
    double volt = spd*127;
    intakeA.move(volt); intakeB.move(volt);
}
// void Commisso::extendIndexer(bool pneuState) {
//     indexer.set_value(pneuState);
// }
void Commisso::spinIndexer(double rpm) {
    indexer.move_velocity(rpm);
}
void Commisso::extendExpansion(bool pneuState) {
    expansion.set_value(pneuState);
}
void Commisso::spinShooter(double rpm) {
    if (rpm <= 0) {
        shooter.move(rpm*127/600);
        cumError = 0; prevTime = millis();
        return;
    }

    unsigned int curTime = millis();
    elapsedTime = curTime - prevTime;

    double input = shooter.get_actual_velocity();
    double error = rpm - input;
    cumError /= 1.1;
    cumError += error*elapsedTime/1000;
    double rateError = (error-lastError)/elapsedTime;

    // double out = KP*error + KI*cumError + KD*rateError;
    // error = max(0.0, error);
    double out = KP*error + KI*cumError;
    out += rpm*.225 + 10;
    // double out = KP*error + rpm*.25;
    // double out = KP*error + input*0.25;
    // double out = KP*error + rpm/5+BASE_MOTOR_POWER;

    // double out = KP*error + rpm*.225 + 10;
    if (input/rpm < .9) out = 127;

    lastError = error;
    prevTime = curTime;

    shooter.move(out);

    printf("%.1f\n", shooter.get_actual_velocity());
}

void tracking_commisso(void* ignore) {
    Commisso tmp;
    while (1) {
        tmp.spinShooter(taskRPM);
        tmp.spinIntake(taskIntake);
        // tmp.extendIndexer(taskIndexer);
        tmp.spinIndexer(taskIndex);
        tmp.extendExpansion(taskExpansion);

        delay(30);
    }
}

void shoot(double rpm) {
    taskRPM = rpm;
}
void intake(double spd) {
    taskIntake = spd;
}
// void index(bool pneuState) {
//     taskIndexer = pneuState;
// }
void index(double rpm) {
    taskIndex = rpm;
}
void expand(bool pneuState) {
    taskExpansion = pneuState;
}