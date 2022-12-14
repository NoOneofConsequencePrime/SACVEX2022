#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RB = motor(PORT18, ratio18_1, true);
motor RF = motor(PORT17, ratio18_1, true);
motor LB = motor(PORT19, ratio18_1, false);
motor LF = motor(PORT11, ratio18_1, false);
motor Intake = motor(PORT21, ratio18_1, false);
motor ShooterRight = motor(PORT15, ratio6_1, false);
motor ShooterLeft = motor(PORT16, ratio6_1, true);
motor Feeder = motor(PORT14, ratio18_1, true);
inertial Gyro = inertial(PORT10);
/*vex-vision-config:begin*/
signature Vision__REDBASKET = signature (1, 6697, 7203, 6950, -541, 1, -270, 11, 0);
signature Vision__BG = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision = vision (PORT9, 50, Vision__REDBASKET, Vision__BG);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}