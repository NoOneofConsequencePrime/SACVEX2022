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
// Expansion            digital_out   H               
// Gyro                 inertial      4               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <vex.h>
#include "Input.h"
#include "ArcadeDrive.h"
#include "VorBuster.h"
#include "Auton.h"

using namespace vex;

competition Competition;

/* Program Init */
#define print Brain.Screen.print
#define setCursor Brain.Screen.setCursor

/* Parameters */
const double WasteDelay = 2;// msec
const double JoystickDeadzone = 2;// 100
const double FWDtoRotSpdMultiplier = 0.3;// 1.0
const double DistErrorMargin = 0.5;// cm
const double DistKP = 0.2;
const double AmbientDistDer = 2;
const double DirErrorMargin = 0.2;// deg
const double DirKP = 0.5;
const double RotErrorMargin = 0.8;// deg
const double RotKP = 1.1;
const double MoveDelay = 100;// msec
const double AmbientRotDer = 800;// dr/dt (deg)

/* Global */
double shooterRPM = 375;// 600

/* Instantiate all objects */
Input Ct1;
ArcadeDrive arcDrive;
VorBuster vorBuster;
Auton auton(WasteDelay, DistErrorMargin, DistKP, AmbientDistDer, DirErrorMargin, DirKP, RotErrorMargin, RotKP, AmbientRotDer, MoveDelay);

void debug() {
  Brain.Screen.clearScreen();
  setCursor(1, 0);
  print(Gyro.rotation(deg));
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
  // auton.moveFwd(100, 0.7);
  // // auton.turn(180, 0.7);
  // setCursor(1, 0);
  // print("Complete");
}

void usercontrol(void) {
  while (1) {
    // Get Input
    Ct1.setChannels(JoystickDeadzone); Ct1.setButtons();

    // Arcade Drive
    arcDrive.drive(Ct1.getCh2(), Ct1.getCh4()*FWDtoRotSpdMultiplier, 1.0);
    // arcDrive.drive(Ct1.getCh3(), Ct1.getCh4()*FWDtoRotSpdMultiplier, 1.0);

    // Robot Controls
    if (Ct1.getLeftHighTrig()) vorBuster.spinIntake(1.0);
    else if (Ct1.getLeftLowTrig()) vorBuster.spinIntake(-1.0);
    else vorBuster.spinIntake(0);

    if (Ct1.getRightLowTrig()) vorBuster.spinFeeder(1.0);
    else if (Ct1.getButtonDown()) vorBuster.spinFeeder(-1.0);
    else vorBuster.spinFeeder(0);

    if (Ct1.getRightHighTrig()) vorBuster.spinShooter(shooterRPM);
    else if (Ct1.getButtonDown()) vorBuster.spinShooter(-30);
    else vorBuster.spinShooter(0);

    if (Ct1.getButtonUp()) Expansion.set(1);
    else Expansion.set(0);

    debug();
    wait(WasteDelay, msec);
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