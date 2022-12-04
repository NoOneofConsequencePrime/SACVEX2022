#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FL = motor(PORT1, ratio18_1, false);
motor FR = motor(PORT2, ratio18_1, true);
motor BL = motor(PORT3, ratio18_1, false);
motor BR = motor(PORT4, ratio18_1, true);
motor Intake = motor(PORT5, ratio18_1, false);
motor Shooter1 = motor(PORT6, ratio6_1, false);
motor Shooter2 = motor(PORT7, ratio6_1, false);
motor Dispense = motor(PORT8, ratio18_1, false);
motor Rollers = motor(PORT9, ratio18_1, false);

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