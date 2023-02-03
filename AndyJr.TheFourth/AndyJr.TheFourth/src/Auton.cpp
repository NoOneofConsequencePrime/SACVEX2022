#include "main.h"
#include "robot-config.h"
#include "Commisso.h"
#include "MecDrive.h"
#include "Sensor.h"
#include "Auton.h"

// Init objects
Sensor prezi;

bool Auton::chkDistRange() {
    return false;
}
bool Auton::chkRotRange(double target) {
    bool ucRange = abs(target-prezi.getRot()) < ROT_UC_RANGE;
    // bool rateRange = 
    return false;
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

}
void Auton::pidTurn(double target, double spd) {
    prezi.resetGyro(); cumError = 0;
    // while ()
}