#include "main.h"
#include "robot-config.h"
#include "MecDrive.h"

double turnSpd;// -1.0 ~ 1.0
double moveDir, moveSpd;// degs, -1.0 ~ 1.0

void MecDrive::set_coast() {
    LF.set_brake_mode(MOTOR_BRAKE_COAST);
    LB.set_brake_mode(MOTOR_BRAKE_COAST);
    RF.set_brake_mode(MOTOR_BRAKE_COAST);
    RB.set_brake_mode(MOTOR_BRAKE_COAST);
}
void MecDrive::set_brake() {
    LF.set_brake_mode(MOTOR_BRAKE_BRAKE);
    LB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    RF.set_brake_mode(MOTOR_BRAKE_BRAKE);
    RB.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
void MecDrive::set_hold() {
    LF.set_brake_mode(MOTOR_BRAKE_HOLD);
    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
    RF.set_brake_mode(MOTOR_BRAKE_HOLD);
    RB.set_brake_mode(MOTOR_BRAKE_HOLD);
}
void MecDrive::brakeAll() {
    LF.brake();
    LB.brake();
    RF.brake();
    RB.brake();
}
void MecDrive::drive(double joyY, double joyX, double rotX, double spd) {
    if (joyY == 0 && joyX == 0 && rotX == 0) {
        set_hold();
        brakeAll(); return;
    }
    double ratioCorrection = max(abs(joyY)+abs(joyX)+abs(rotX), 127.0);

    double LFVel = (joyY+joyX+rotX) / ratioCorrection * spd*127.0;
    double LBVel = (joyY-joyX+rotX) / ratioCorrection * spd*127.0;
    double RFVel = (joyY-joyX-rotX) / ratioCorrection * spd*127.0;
    double RBVel = (joyY+joyX-rotX) / ratioCorrection * spd*127.0;

    LF.move(LFVel);
    LB.move(LBVel);
    RF.move(RFVel);
    RB.move(RBVel);
}
void MecDrive::turn(double spd) {
    double vel = spd*200.0;

    LF.move_velocity(vel);
    LB.move_velocity(vel);
    RF.move_velocity(-vel);
    RB.move_velocity(-vel);
}
void MecDrive::move(double dir, double spd) {
    double rad = dir*M_PI/180.0;
    double velX = sin(rad), velY = cos(rad);

    double normalCorrection = 1.0 / max(abs(velX), abs(velY));
    velX *= normalCorrection; velY *= normalCorrection;
    double ratioCorrection = max(abs(velX)+abs(velY), 1.0);

    double LFVel = (velY+velX) / ratioCorrection * spd*200.0;
    double LBVel = (velY-velX) / ratioCorrection * spd*200.0;
    double RFVel = (velY-velX) / ratioCorrection * spd*200.0;
    double RBVel = (velY+velX) / ratioCorrection * spd*200.0;

    LF.move_velocity(LFVel);
    LB.move_velocity(LBVel);
    RF.move_velocity(RFVel);
    RB.move_velocity(RBVel);
    
    // LF.move(LFVel*127/200);
    // LB.move(LBVel*127/200);
    // RF.move(RFVel*127/200);
    // RB.move(RBVel*127/200);
}

void tracking_mec(void* ignore) {
    MecDrive tmp;
    while (1) {
        if (moveSpd != 0) tmp.move(moveDir, moveSpd);
        else if (turnSpd != 0) tmp.turn(turnSpd);

        delay(10);
    }
}

void mecTurn(double spd) {
    turnSpd == spd;
}
void mecMove(double dir, double spd) {
    moveDir = dir; moveSpd = spd;
}