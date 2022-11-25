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
// FL                   motor         7               
// FR                   motor         11              
// BL                   motor         8               
// BR                   motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

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
void fbControl(){
  int y = Controller1.Axis3.position(pct);
    if ((y > 0) || (y < 0)) {
      FL.spin(forward, y, pct);
      FR.spin(forward, y, pct);
      BL.spin(forward, y, pct);
      BR.spin(forward, y, pct);
    }
}

void lrControl(){
  int x = Controller1.Axis4.position(pct);
    if ((x > 0) || (x < 0)) {
      FL.spin(forward, x, pct);
      FR.spin(forward, -x, pct);
      BL.spin(forward, -x, pct);
      BR.spin(forward, x, pct);
    } 
}

void lrTurn(){
  int z = Controller1.Axis1.position(pct);
    if ((z > 10) || (z < -10)){
      FL.spin(forward, z, pct);
      FR.spin(forward, -z, pct);
      BL.spin(forward, z, pct);
      BR.spin(forward, -z, pct);
    } 
}



void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    int y = Controller1.Axis3.position(pct);
    if ((y > 0) || (y < 0)) {
      FL.spin(forward, y, pct);
      FR.spin(forward, y, pct);
      BL.spin(forward, y, pct);
      BR.spin(forward, y, pct);
    }
    int x = Controller1.Axis4.position(pct);
    if ((x > 0) || (x < 0)) {
      FL.spin(forward, x, pct);
      FR.spin(forward, -x, pct);
      BL.spin(forward, -x, pct);
      BR.spin(forward, x, pct);
    } 
    int z = Controller1.Axis1.position(pct);
    if ((z > 10) || (z < -10)){
      FL.spin(forward, z, pct);
      FR.spin(forward, -z, pct);
      BL.spin(forward, z, pct);
      BR.spin(forward, -z, pct);
    } 
    if(z == 0 && y == 0 && x == 0){
    FL.spin(forward, 0, pct);
    FR.spin(forward, 0, pct);
    BL.spin(forward, 0, pct);
    BR.spin(forward, 0, pct);
  } 
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(5, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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
