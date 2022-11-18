#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RB = motor(PORT1, ratio18_1, true);
motor RF = motor(PORT2, ratio18_1, true);
motor LB = motor(PORT3, ratio18_1, false);
motor LF = motor(PORT4, ratio18_1, false);
motor Intake = motor(PORT6, ratio18_1, false);
motor Motor1 = motor(PORT9, ratio6_1, false);
motor Motor2 = motor(PORT10, ratio6_1, true);

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