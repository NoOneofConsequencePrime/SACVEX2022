#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RB = motor(PORT12, ratio18_1, true);
motor RF = motor(PORT16, ratio18_1, true);
motor LB = motor(PORT14, ratio18_1, false);
motor LF = motor(PORT18, ratio18_1, false);
motor Intake = motor(PORT13, ratio18_1, false);
motor ShooterRight = motor(PORT20, ratio6_1, false);
motor ShooterLeft = motor(PORT19, ratio6_1, true);
motor Feeder = motor(PORT11, ratio18_1, true);
encoder YEncoder = encoder(Brain.ThreeWirePort.A);

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