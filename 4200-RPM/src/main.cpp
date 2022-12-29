// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intake               motor         5               
// RF                   motor         6               
// LF                   motor         7               
// Feeder               motor         10              
// ShooterL             motor         14              
// ShooterR             motor         15              
// RB                   motor         20              
// LB                   motor         21              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <vex.h>
#include "Input.h"
#include "ArcadeDrive.h"
#include "VorBuster.h"

using namespace vex;

competition Competition;

/* Program Init */
#define print Brain.Screen.print
#define setCursor Brain.Screen.setCursor

/* Parameters */
const double wasteDelay = 5;// msec
const double JoystickDeadzone = 2;// 100
const double FWDtoRotSpdMultiplier = 0.3;// 1.0

/* Global */
double shooterRPM = 300;// 600

/* Instantiate all objects */
Input Ct1;
ArcadeDrive arcDrive;
VorBuster vorBuster;

void debug() {
  Brain.Screen.clearScreen();
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
}

void usercontrol(void) {
  while (1) {
    // Get Input
    Ct1.setChannels(JoystickDeadzone); Ct1.setButtons();

    // Arcade Drive
    arcDrive.drive(Ct1.getCh3(), Ct1.getCh1(), 1.0);

    // Robot Controls
    if (Ct1.getLeftHighTrig()) vorBuster.spinIntake(1.0);
    else if (Ct1.getLeftLowTrig()) vorBuster.spinIntake(-100);
    else vorBuster.spinIntake(0);

    if (Ct1.getRightLowTrig()) vorBuster.spinFeeder(1.0);
    else if (Ct1.getButtonDown()) vorBuster.spinFeeder(-1.0);
    else vorBuster.spinFeeder(0);

    if (Ct1.getRightHighTrig()) vorBuster.spinShooter(shooterRPM);
    else if (Ct1.getButtonDown()) vorBuster.spinShooter(-30);
    else vorBuster.spinShooter(0);

    debug();
    wait(wasteDelay, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}