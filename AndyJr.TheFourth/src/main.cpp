// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         1               
// RF                   motor         2               
// LB                   motor         3               
// LF                   motor         4               
// Intake               motor         6               
// Motor1               motor         9               
// Motor2               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <vex.h>
#include "Input.h"
#include "MecDrive.h"
#include "Roller.h"

using namespace vex;

// Program init
#define print Brain.Screen.print
#define setCursor Brain.Screen.setCursor

competition Competition;

// Parameters
const double MecDriveStrafeCorrection = 1.0;
const double ControllerJoystickThreshold = 2;

// Global Variables

void debug() {
  Brain.Screen.clearScreen();
  setCursor(1, 1);
  print("Motor1Eff: ");
  print(Motor1.efficiency(pct));
  setCursor(2, 1);
  print("Motor1VelRPM: ");
  print(Motor1.velocity(rpm));
  setCursor(3, 1);
  print("Motor1VelPCT: ");
  print(Motor1.velocity(pct));
  setCursor(4, 1);
  print("Motor1Temp: ");
  print(Motor1.temperature(pct));
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
}

Input Ct1;
MecDrive mecDrive;
Roller tmp;
void usercontrol(void) {
  while (1) {
    Ct1.setButtons();
    if (Ct1.getButtonA()) {
      LF.spin(fwd, 0, pct);
      LB.spin(fwd, 0, pct);
      RF.spin(fwd, 0, pct);
      RB.spin(fwd, 0, pct);
      RB.stop();
      RF.stop();
      LB.stop();
      LF.stop();
    } else if (Ct1.getButtonB()) {
      LF.spin(fwd, 100, pct);
      LB.spin(fwd, 27, pct);
      RF.spin(fwd, 27, pct);
      RB.spin(fwd, 100, pct);
    }

    // if (Ct1.getButtonA()) {
    //   Motor1.spin(forward, 0, pct);
    //   Motor2.spin(forward, 0, pct);
    // } else if (Ct1.getButtonB()) {
    //   Motor1.spin(forward, 50, pct);
    //   Motor2.spin(forward, 50, pct);
    // } else if (Ct1.getButtonX()) {
    //   Motor1.spin(forward, 100, pct);
    //   Motor2.spin(forward, 100, pct);
    // }

    // Ct1.setChannels(ControllerJoystickThreshold); Ct1.setButtons();
    // mecDrive.drive(Ct1.getCh3(), Ct1.getCh4(), Ct1.getCh1(), 100, MecDriveStrafeCorrection);
    // if (Ct1.getLeftHighTrig()) tmp.spinRoller(100);
    // else if (Ct1.getLeftLowTrig()) tmp.spinRoller(-100);
    // else tmp.spinRoller(0);

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
