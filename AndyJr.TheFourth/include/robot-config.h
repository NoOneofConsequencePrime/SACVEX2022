using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor RB;
extern motor RF;
extern motor LB;
extern motor LF;
extern motor Intake;
extern motor ShooterRight;
extern motor ShooterLeft;
extern motor Feeder;
extern inertial Gyro;
extern signature Vision__REDBASKET;
extern signature Vision__BG;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );