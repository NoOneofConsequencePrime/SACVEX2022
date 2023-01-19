#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RB = motor(PORT12, ratio18_1, false);
motor RF = motor(PORT14, ratio18_1, false);
motor LB = motor(PORT11, ratio18_1, true);
motor LF = motor(PORT13, ratio18_1, true);
motor Intake = motor(PORT21, ratio18_1, false);
motor ShooterRight = motor(PORT15, ratio6_1, false);
motor ShooterLeft = motor(PORT16, ratio6_1, true);
motor Feeder = motor(PORT6, ratio18_1, true);
inertial Gyro = inertial(PORT10);
/*vex-vision-config:begin*/
signature Vision__REDBASKET = signature (1, 5835, 8953, 7394, -2419, -783, -1601, 2.8, 0);
signature Vision__BLUEBASKET = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision = vision (PORT9, 90, Vision__REDBASKET, Vision__BLUEBASKET, Vision__SIG_3, Vision__SIG_4, Vision__SIG_5, Vision__SIG_6, Vision__SIG_7);
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