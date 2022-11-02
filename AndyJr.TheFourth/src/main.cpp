#include <vex.h>
#include "Input.h"
#include "MecDrive.h"

using namespace vex;

// Program init
#define print Brain.Screen.print
#define setCursor Brain.Screen.setCursor

competition Competition;

// // Global Variables
// int threshold = 10, negThreshold = -10;
// double Channel1, Channel2, Channel3, Channel4;

// void getChannel() {// General deadzone check
//   Channel1 = (Ct1.Axis1.position(pct) >= threshold || Ct1.Axis1.position(pct) <= negThreshold)? Ct1.Axis1.position(pct) : 0;
//   Channel2 = (Ct1.Axis2.position(pct) >= threshold || Ct1.Axis2.position(pct) <= negThreshold)? Ct1.Axis2.position(pct) : 0;
//   Channel3 = (Ct1.Axis3.position(pct) >= threshold || Ct1.Axis3.position(pct) <= negThreshold)? Ct1.Axis3.position(pct) : 0;
//   Channel4 = (Ct1.Axis4.position(pct) >= threshold || Ct1.Axis4.position(pct) <= negThreshold)? Ct1.Axis4.position(pct) : 0;
// }

// void moveMotors(double LFVal, double RFVal, double LBVal, double RBVal) {
//   LF.spin(forward, LFVal, pct);
//   RF.spin(forward, RFVal, pct);
//   LB.spin(forward, LBVal, pct);
//   RB.spin(forward, RBVal, pct);
// }

// double spd = 10;
// void mecDrive() {
//   if (Ct1.ButtonUp.pressing()) {
//     moveMotors(spd,spd, spd, spd);
//   } else if (Ct1.ButtonDown.pressing()) {
//     moveMotors(-spd, -spd, -spd, -spd);
//   } else if (Ct1.ButtonLeft.pressing()) {
//     moveMotors(-spd, spd, spd, -spd);
//   } else if (Ct1.ButtonRight.pressing()) {
//     moveMotors(spd, -spd, -spd, spd);
//   }
// }

void debug() {
  Brain.Screen.clearScreen();
  setCursor(1, 1);
  print("running");
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
}

MecDrive mecDrive;
void usercontrol(void) {
  while (1) {
    mecDrive.drive(100.0);

    debug();
    wait(5, msec); 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
