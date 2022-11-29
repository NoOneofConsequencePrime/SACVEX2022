using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor RB;
extern motor RF;
extern motor LB;
extern motor LF;
extern motor Intake;
<<<<<<< HEAD:AndyJr.TheFourth/include/robot-config.h
extern motor ShooterRight;
extern motor ShooterLeft;
extern motor Feeder;
=======
extern motor FlywheelR;
extern motor FlywheelL;
extern motor LoaderM;
>>>>>>> parent of e400e9a (Merge branch 'bryan' of https://github.com/NoOneofConsequencePrime/SACVEX2022 into bryan):AndyJrTheFourth/include/robot-config.h

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );