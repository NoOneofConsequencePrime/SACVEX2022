using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Intake;
extern motor RF;
extern motor LF;
extern motor Feeder;
extern motor ShooterL;
extern motor ShooterR;
extern motor RB;
extern motor LB;
extern digital_out Expansion;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );