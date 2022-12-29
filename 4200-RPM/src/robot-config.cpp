#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Intake = motor(PORT5, ratio36_1, true);
motor RF = motor(PORT6, ratio18_1, true);
motor LF = motor(PORT7, ratio18_1, false);
motor Feeder = motor(PORT10, ratio18_1, false);
motor ShooterL = motor(PORT14, ratio6_1, true);
motor ShooterR = motor(PORT15, ratio6_1, false);
motor RB = motor(PORT20, ratio18_1, false);
motor LB = motor(PORT21, ratio18_1, true);

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