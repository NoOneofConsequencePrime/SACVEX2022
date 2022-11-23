using namespace vex;

extern brain Brain;

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
extern encoder YEncoder;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );