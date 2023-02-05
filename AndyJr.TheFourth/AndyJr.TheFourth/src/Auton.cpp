#include "main.h"
#include "robot-config.h"
#include "Commisso.h"
#include "MecDrive.h"
#include "Sensor.h"
#include "Auton.h"

// Init objects
Sensor prezi;
MecDrive mec;

bool Auton::chkDistRange(double target) {
    bool ucRange = abs(target-prezi.getDisplacement()) < DIST_UC_RANGE;
    // bool rateRange = abs(target-prezi.getDisplacement()-lastError)/elapsedTime < DIST_RATE_ERROR;
    // return ucRange && rateRange;
    return ucRange;
}
bool Auton::chkRotRange(double target) {
    bool ucRange = abs(target-prezi.getRot()) < ROT_UC_RANGE;
    // bool rateRange = abs(target-prezi.getRot()-lastError)/elapsedTime < ROT_RATE_ERROR;
    // return ucRange && rateRange;
    return ucRange;
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
    while (!chkDistRange(dist)) {
        mec.move(dir, getPID(prezi.getDisplacement(), dist, MKP, MKI, MKD));
        // double tmpPID = getPID(prezi.getDisplacement(), dist, MKP, MKI, MKD);
        // if (tmpPID > 0) mec.move(dir, min(tmpPID, spd));
        // else if (tmpPID < 0) mec.move(180, min(tmpPID, spd));
        delay(10);
    }

    mec.set_brake();
    mec.brakeAll();
}
void Auton::pidTurn(double target, double spd) {
    double baseRot = prezi.getRot(); cumError = 0;
    while (!chkRotRange(target+baseRot)) {
        // mec.turn(min(getPID(prezi.getRot()-baseRot, target, RKP, RKI, RKD), spd));
        mec.turn(getPID(prezi.getRot()-baseRot, target, RKP, RKI, RKD));
        delay(10);
    }

    mec.set_brake();
    mec.brakeAll();
}