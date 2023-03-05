#include "main.h"
#include "robot-config.h"
#include "Drive.h"

void Drive::set_coast() {
    LF.set_brake_mode(MOTOR_BRAKE_COAST);
    LB.set_brake_mode(MOTOR_BRAKE_COAST);
    RF.set_brake_mode(MOTOR_BRAKE_COAST);
    RB.set_brake_mode(MOTOR_BRAKE_COAST);
}
void Drive::set_brake() {
    LF.set_brake_mode(MOTOR_BRAKE_BRAKE);
    LB.set_brake_mode(MOTOR_BRAKE_BRAKE);
    RF.set_brake_mode(MOTOR_BRAKE_BRAKE);
    RB.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
void Drive::set_hold() {
    LF.set_brake_mode(MOTOR_BRAKE_HOLD);
    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
    RF.set_brake_mode(MOTOR_BRAKE_HOLD);
    RB.set_brake_mode(MOTOR_BRAKE_HOLD);
}
void Drive::brakeAll() {
    LF.brake();
    LB.brake();
    RF.brake();
    RB.brake();
}
void Drive::arcadeDrive(double joyY, double rotX, double spd) {
    if (joyY == 0 && rotX == 0) {
        // set_hold();
        brakeAll(); return;
    }
    double ratioCorrection = max(abs(joyY)+abs(rotX), 127.0);

    double LFVel = (joyY+rotX) / ratioCorrection * spd*127.0;
    double LBVel = (joyY+rotX) / ratioCorrection * spd*127.0;
    double RFVel = (joyY-rotX) / ratioCorrection * spd*127.0;
    double RBVel = (joyY-rotX) / ratioCorrection * spd*127.0;

    LF.move(LFVel);
    LB.move(LBVel);
    RF.move(RFVel);
    RB.move(RBVel);
}
void Drive::turn(double spd) {
    double vel = spd*600.0;

    LF.move_velocity(vel);
    LB.move_velocity(vel);
    RF.move_velocity(-vel);
    RB.move_velocity(-vel);
}
void Drive::moveFwd(double spd) {
    double vel = spd*600.0;

    LF.move_velocity(vel);
    LB.move_velocity(vel);
    RF.move_velocity(vel);
    RB.move_velocity(vel);
}