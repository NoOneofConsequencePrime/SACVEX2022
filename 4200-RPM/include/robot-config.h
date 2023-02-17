using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Intake;
extern motor RF;
extern motor LF;
extern motor Feeder;
extern motor Shooter;
extern motor RB;
extern motor LB;
extern digital_out Expansion;
extern inertial Gyro;
extern digital_out Feed;
extern motor Shooter1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );