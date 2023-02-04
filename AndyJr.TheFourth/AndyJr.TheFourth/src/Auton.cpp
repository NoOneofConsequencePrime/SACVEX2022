#include "main.h"
#include "robot-config.h"
#include "Commisso.h"
#include "MecDrive.h"
#include "Sensor.h"
#include "Auton.h"

// Init objects
Sensor prezi;
MecDrive mec;

bool Auton::chkDistRange() {
    return false;
}
bool Auton::chkRotRange(double target) {
    bool ucRange = abs(target-prezi.getRot()) < ROT_UC_RANGE;
    bool rateRange = abs(target-prezi.getRot()-lastError)/elapsedTime < ROT_RATE_ERROR;
    return ucRange && rateRange;
}
double Auton::getPID(double input, double setPoint, double KP, double KI, double KD) {
    double curTime = millis();
    elapsedTime = (curTime-prevTime)/1000;

    double error = setPoint-input;
    cumError += error*elapsedTime;
    double rateError = (error-lastError)/elapsedTime;

    double out = KP*error;
    out += KI*cumError;
    out += KD*rateError;

    lastError = error;
    prevTime = curTime;

    return out;
}
void Auton::pidMove(double dist, double dir, double spd) {
    double baseRot = prezi.getRot(); cumError = 0;
    prezi.resetEncoders();
    while (1) {
        double tmpPID = getPID(prezi.getDisplacement(), dist, MKP, MKI, MKD);
        delay(10);
    }
}
void Auton::pidTurn(double target, double spd) {
    double baseRot = prezi.getRot(); cumError = 0;
    while (!chkRotRange(target)) {
        mec.turn(getPID(prezi.getRot()-baseRot, target, RKP, RKI, RKD));
        delay(10);
    }

    mec.set_brake();
    mec.brakeAll();
}