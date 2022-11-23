// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         12              
// RF                   motor         16              
// LB                   motor         14              
// LF                   motor         18              
// Intake               motor         13              
// ShooterRight         motor         20              
// ShooterLeft          motor         19              
// Feeder               motor         11              
// YEncoder             encoder       A, B            
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         12              
// RF                   motor         16              
// LB                   motor         14              
// LF                   motor         18              
// Intake               motor         13              
// ShooterRight         motor         20              
// ShooterLeft          motor         19              
// Feeder               motor         11              
// XEncoder             encoder       A, B            
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RB                   motor         12              
// RF                   motor         16              
// LB                   motor         14              
// LF                   motor         18              
// Intake               motor         13              
// ShooterRight         motor         20              
// ShooterLeft          motor         19              
// Feeder               motor         11              
// Encoder              encoder       A, B            
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
const double SlowShooterRPM = 300, FastShooterRPM = 400;

// Global Variables
double shooterRPM = 300;

void debug() {
  Brain.Screen.clearScreen();
  // setCursor(1, 1);
  // print("EncoderRot: ");
  // print(YEncoder.position(degrees));
  // setCursor(2, 1);
  // print("EncoderVel: ");
  // print(YEncoder.velocity(rpm));

  setCursor(1, 1);
  print("ShooterEff: ");
  print(ShooterRight.efficiency(pct));
  setCursor(2, 1);
  print("ShooterVelRPM: ");
  print(ShooterRight.velocity(rpm));
  setCursor(3, 1);
  print("ShooterVelPCT: ");
  print(ShooterRight.velocity(pct));
  setCursor(4, 1);
  print("ShooterTemp: ");
  print(ShooterRight.temperature(pct));
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

    // Mecanum Drive
    mecDrive.drive(Ct1.getCh3(), Ct1.getCh4(), Ct1.getCh1(), 100, MecDriveStrafeCorrection);
    
    // Robot Controls
    if (Ct1.getLeftHighTrig()) commisso.spinIntake(100);
    else if (Ct1.getLeftLowTrig()) commisso.spinIntake(-100);
    else commisso.spinIntake(0);
    if (Ct1.getRightLowTrig()) commisso.spinFeeder(100);
    else commisso.spinFeeder(0);
    if (Ct1.getRightHighTrig()) commisso.spinShooter(shooterRPM);
    else commisso.spinShooter(0);
    if (Ct1.getButtonUp()) shooterRPM = FastShooterRPM;
    if (Ct1.getButtonDown()) shooterRPM = SlowShooterRPM;

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
