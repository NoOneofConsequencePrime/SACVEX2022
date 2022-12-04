 /*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FL                   motor         1               
// FR                   motor         2               
// BL                   motor         3               
// BR                   motor         4               
// Intake               motor         5               
// Shooter1             motor         6               
// Shooter2             motor         7               
// Dispense             motor         8               
// Rollers              motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "controllerScript.h"
#include "motorControl.h"
#include "intake.h"


using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

const double ControllerJoystickThreshold = 2;
controllerScript controls;
motorControl motors;
intake intakeControl;
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    controls.setChannels(ControllerJoystickThreshold);
    controls.setButtons();
    motors.drive(controls.getChan3(), controls.getChan4(), controls.getChan1(), 200, 1.02);
    if (controls.getLeftTrigTop()) {
      Intake.spin(forward, 100, pct);
    } else {Intake.spin(fwd, 0 ,pct);}
  
    if (controls.getLeftTrigDown()) {
      Shooter1.spin(reverse, 100, pct);
      Shooter2.spin(fwd, 100, pct);
    } else {
      Shooter1.spin(fwd, 0, pct); Shooter2.spin(fwd, 0, pct);
    }

    if (controls.getRightTrigTop()) {
      Dispense.spin(reverse, 100, pct);
    } else {Dispense.spin(reverse, 0, pct);}

    if (controls.getRightTrigDown()) {
      Rollers.spin(fwd, 100, pct);
    } else {Rollers.spin(reverse, 0, pct);}
    
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
