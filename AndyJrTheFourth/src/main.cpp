// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         17              
// Intake               motor         11              
// FlywheelR            motor         12              
// FlywheelL            motor         15              
// Loader               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         17              
// Intake               motor         11              
// FlywheelR            motor         12              
// FlywheelL            motor         15              
// Loader               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         17              
// Intake               motor         11              
// FlywheelR            motor         12              
// FlywheelL            motor         15              
// Loader               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         17              
// Intake               motor         11              
// FlywheelR            motor         12              
// FlywheelL            motor         15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         17              
// Intake               motor         11              
// Flywheel1            motor         12              
// FlywheelL            motor         15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         17              
// Intake               motor         11              
// Flywheel1            motor         12              
// Flywheel             motor         15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         17              
// Intake               motor         11              
// Flywheel1            motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         17              
// Intake               motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         17              
// Intake               motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         16              
// LF                   motor         4               
// Intake               motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         19              
// LB                   motor         3               
// LF                   motor         4               
// Intake               motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         18              
// RF                   motor         2               
// LB                   motor         3               
// LF                   motor         4               
// Intake               motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         1               
// RF                   motor         2               
// LB                   motor         3               
// LF                   motor         4               
// Intake               motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <vex.h>
#include "Input.h"
#include "MecDrive.h"
#include "Roller.h"
#include "Shooter.h"

using namespace vex;

// Program init
#define print Brain.Screen.print
#define setCursor Brain.Screen.setCursor

competition Competition;

// Parameters
const double MecDriveStrafeCorrection = 1.1;
const double ControllerJoystickThreshold = 2;

// Global Variables

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

Input Ct1;
MecDrive mecDrive;
Roller roller;
Shooter shooter;
void usercontrol(void) {
  while (1) {
    Ct1.setChannels(ControllerJoystickThreshold); Ct1.setButtons();
    mecDrive.drive(Ct1.getCh3(), Ct1.getCh4(), Ct1.getCh1(), 100, MecDriveStrafeCorrection);
    if (Ct1.getLeftHighTrig()) roller.spinRoller(100);
    else if (Ct1.getLeftLowTrig()) roller.spinRoller(-100);
    else roller.spinRoller(0);
    if (Ct1.getRightHighTrig()) shooter.spinShooter(100);
    else if (Ct1.getRightLowTrig()) shooter.spinShooter(-100);
    else shooter.spinShooter(0); 
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
