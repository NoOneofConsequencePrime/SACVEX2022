// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         6               
// LF                   motor         16              
// Intake               motor         4               
// ShooterRight         motor         14              
// ShooterLeft          motor         15              
// Feeder               motor         2               
// Motor1               motor         9               
// Motor2               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         6               
// LF                   motor         16              
// Intake               motor         4               
// ShooterRight         motor         14              
// ShooterLeft          motor         15              
// Feeder               motor         2               
// Motor1               motor         9               
// Motor2               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         6               
// LF                   motor         16              
// Intake               motor         4               
// ShooterRight         motor         14              
// ShooterLeft          motor         15              
// Feeder               motor         2               
// Motor1               motor         9               
// Motor2               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         6               
// LF                   motor         16              
// Intake               motor         4               
// ShooterRight         motor         14              
// ShooterLeft          motor         15              
// Feeder               motor         2               
// Motor1               motor         9               
// Motor2               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         6               
// LF                   motor         16              
// Intake               motor         4               
// ShooterRight         motor         14              
// ShooterLeft          motor         15              
// Feeder               motor         2               
// Motor1               motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <vex.h>
#include "Input.h"
#include "MecDrive.h"
#include "Commisso.h"

using namespace vex;

// Program init
#define print Brain.Screen.print
#define setCursor Brain.Screen.setCursor

competition Competition;

// Parameters
const double MecDriveStrafeCorrection = 1.0;
const double ControllerJoystickThreshold = 2;
const double ShooterRPM = 420;

// Global Variables

void debug() {
  // Brain.Screen.clearScreen();

  // setCursor(1, 1);
  // print("ShooterRightTemp: ");
  // print(ShooterRight.temperature(pct));
  // setCursor(2, 1);
  // print("ShooterLeftTemp: ");
  // print(ShooterLeft.temperature(pct));
  // setCursor(3, 1);
  // print("IntakeTemp: ");
  // print(Intake.temperature(pct));
  // setCursor(4, 1);
  // print("FeederTemp: ");
  // print(Feeder.temperature(pct));
  // setCursor(5, 1);
  // print("RBTemp: ");
  // print(RB.temperature(pct));
  // setCursor(6, 1);
  // print("RFTemp: ");
  // print(RF.temperature(pct));
  // setCursor(7, 1);
  // print("LBTemp: ");
  // print(LB.temperature(pct));
  // setCursor(8, 1);
  // print("LFTemp: ");
  // print(LF.temperature(pct));

  // setCursor(1, 1);
  // print("ShooterEff: ");
  // print(ShooterRight.efficiency(pct));
  // setCursor(2, 1);
  // print("ShooterVelRPM: ");
  // print(ShooterRight.velocity(rpm));
  // setCursor(3, 1);
  // print("ShooterVelPCT: ");
  // print(ShooterRight.velocity(pct));
  // setCursor(4, 1);
  // print("ShooterTemp: ");
  // print(ShooterRight.temperature(pct));
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
}

Input Ct1;
MecDrive mecDrive;
Commisso commisso;
void usercontrol(void) {
  while (1) {
    // Get Input
    Ct1.setChannels(ControllerJoystickThreshold); Ct1.setButtons();

    if (Ct1.getButtonA()) {
      Motor1.spin(fwd, 600, rpm);
      Motor2.spin(fwd, 600, rpm);
    } else {
      Motor1.spin(fwd, 0, rpm);
      Motor2.spin(fwd, 0, rpm);
    }

    // // Mecanum Drive
    // mecDrive.drive(Ct1.getCh3(), Ct1.getCh4(), Ct1.getCh1(), 100, MecDriveStrafeCorrection);
    
    // // Robot Controls
    // if (Ct1.getLeftHighTrig()) commisso.spinIntake(100);
    // else if (Ct1.getLeftLowTrig()) commisso.spinIntake(-100);
    // else commisso.spinIntake(0);
    // if (Ct1.getRightLowTrig()) commisso.spinFeeder(100);
    // else commisso.spinFeeder(0);
    // if (Ct1.getRightHighTrig()) commisso.spinShooter(ShooterRPM);
    // else if (Ct1.getButtonDown()) commisso.spinShooter(-50);
    // else commisso.spinShooter(0);

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
