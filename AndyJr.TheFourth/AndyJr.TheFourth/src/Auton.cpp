#include "main.h"
#include "robot-config.h"
#include "Commisso.h"
#include "Drive.h"
#include "Sensor.h"
#include "Auton.h"

// Init objects
Sensor prezi;
Drive tmpDrive;

const int MOVE_TO = 3000;// ms

double tDist, tTarget, tSpd;
double turnSpd;// -1.0 ~ 1.0
double moveSpd;// -1.0 ~ 1.0
double tJoyY, tRotX;

bool Auton::chkDistRange(double target) {
    bool ucRange = abs(target-prezi.getEncoderDist()) < DIST_UC_RANGE;
    // bool rateRange = abs(target-prezi.getDisplacement()-lastError)/elapsedTime < DIST_RATE_ERROR;
    // return ucRange && rateRange;
    return ucRange;
}
bool Auton::chkRotRange(double target) {
    bool ucRange = abs(target-prezi.getRot()) < ROT_UC_RANGE;
    bool rateRange = abs(target-prezi.getRot()-lastError)/elapsedTime < ROT_RATE_ERROR;
    return ucRange && rateRange;
    // return ucRange;
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
void Auton::pidMove(double dist, double spd) {
    double baseRot = prezi.getRot(); cumError = 0;
    prezi.resetEncoders();
    int stTime = millis();
    while (!chkDistRange(dist) && millis() < stTime+MOVE_TO) {
        double pidVal = getPID(prezi.getEncoderDist(), dist, MKP, MKI, MKD);
        if (pidVal > 1) pidVal = 1;
        else if (pidVal < -1) pidVal = -1;
        tmpDrive.moveFwd(pidVal * spd);
        delay(30);
    }

    tmpDrive.set_brake();
    tmpDrive.brakeAll();
    delay(150);
}
void Auton::pidTurn(double target, double spd) {
    double baseRot = prezi.getRot(); cumError = 0;
    int stTime = millis();
    while (!chkRotRange(target+baseRot) && millis() < stTime+MOVE_TO) {
        double pidVal = getPID(prezi.getRot()-baseRot, target, RKP, RKI, RKD);
        if (pidVal > 1) pidVal = 1;
        else if (pidVal < -1) pidVal = -1;
        tmpDrive.turn(pidVal * spd);
        delay(30);
    }

    tmpDrive.set_brake();
    tmpDrive.brakeAll();
    delay(150);
}

bool chkMotor() {
    return LF.is_stopped() && LB.is_stopped() && RF.is_stopped() && RB.is_stopped();
}

void tracking_auton(void* ignore) {
    Auton tmp;
    Drive tmpDrive;
    while (1) {
        if (tDist != 0) {
            tmp.pidMove(tDist, tSpd);
            tDist = 0;
        } else if (tTarget != 0) {
            tmp.pidTurn(tTarget, tSpd);
            tTarget = 0;
        } else if (moveSpd != 0) {
            tmpDrive.moveFwd(moveSpd);
        } else if (turnSpd != 0) {
            tmpDrive.turn(turnSpd);
        } else {
            tmpDrive.arcadeDrive(tJoyY, tRotX, tSpd);
        }

        delay(10);
    }
}

void autonMove(double dist, double spd) {
    tDist = dist; tSpd = spd;
}
void autonTurn(double target, double spd) {
    tTarget = target; tSpd = spd;
}
void driveTurn(double spd) {
    turnSpd == spd;
}
void driveMove(double spd) {
    moveSpd = spd;
}
void arcadeDrive(double joyY, double rotX, double spd) {
    tJoyY = joyY;
    tRotX = rotX;
    tSpd = spd;
}