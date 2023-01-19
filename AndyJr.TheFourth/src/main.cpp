#include <vex.h>
#include <algorithm>
#include "Input.h"
#include "MecDrive.h"
#include "Commisso.h"
#include "Auton.h"
#include "Camera.h"

using namespace vex;

// Program init
#define print Brain.Screen.print
#define setCursor Brain.Screen.setCursor

competition Competition;

// Parameters
const double WasteDelay = 5;// msec
const double MecDriveCorrection = 1.0;
const double ControllerJoystickThreshold = 2;
const double FastShooterRPM = 365, SlowShooterRPM = 320;
const double ShooterRPMUncertainty = 30;
const double DistErrorMargin = 0.5;// cm
const double DistKP = 0.3;
const double AmbientDistDer = 2;
const double DirErrorMargin = 0.5;// deg
const double DirKP = 0.2;
const double RotErrorMargin = 0.5;// deg
const double RotKP = 2.5;
const double MoveDelay = 100;// msec
const double AmbientRotDer = 800;// dr/dt (deg)

// Global Variables
double shooterRPM = FastShooterRPM;
bool dirFwd = 1;

// Init all objects
Input Ct1;
MecDrive mecDrive;
Commisso commisso;
Auton auton(WasteDelay, DistErrorMargin, DistKP, AmbientDistDer, DirErrorMargin, DirKP, RotErrorMargin, RotKP, AmbientRotDer, MoveDelay);
Camera cam;

void debug() {
  Brain.Screen.clearScreen();

  cam.showView();
}

void pre_auton(void) {
  vexcodeInit();
}

void autonLeft() {// left setup, touch roller, 2 shots mid-field; roller: 0 - up, 1 - down (with respect to closest side)
  // Setup
  commisso.setAutonOverride(true);

  mecDrive.driveFwd(1.0);
  commisso.spinRoller(1.0);
  wait(0.15, sec);
  auton.motorBrake(MoveDelay);
  auton.moveFwd(-10, 0.8);
  commisso.spinRoller(0.0);
  commisso.spinIntake(1.0);
  auton.turn(-90, 1.0);
  auton.moveFwd(120, 1.0);
  commisso.spinIntake(0.0);
  auton.turn(55.5, 0.7);
  auton.moveFwd(-75, 0.8);

  commisso.spinShooter(shooterRPM+5, ShooterRPMUncertainty);
  wait(3, sec);
  commisso.spinFeeder(1.0);
  wait(0.3, sec);
  commisso.spinFeeder(0.0);
  commisso.spinShooter(shooterRPM+9, ShooterRPMUncertainty);
  wait(3, sec);
  commisso.spinFeeder(1.0);
  wait(1.0, sec);
  commisso.spinShooter(0.0, ShooterRPMUncertainty); commisso.spinFeeder(0.0);
}

void autonRight() {// right setup, corner of auton zone, 2 shots far-field: 0 - up, 1 - down (with respect to closest side)
  // Setup
  commisso.setAutonOverride(true);

  auton.moveFwd(65, 0.8);
  auton.turn(90, 1.0);
  mecDrive.driveFwd(1.0);
  commisso.spinRoller(1.0);
  wait(0.4, sec);
  auton.motorBrake(MoveDelay);
  commisso.spinRoller(0.0);
  commisso.spinIntake(1.0);
  auton.moveFwd(-10, 0.8);
  wait(1, sec);
  commisso.spinIntake(0.0);
  auton.turn(-5, 0.7);
  
  commisso.spinShooter(shooterRPM+28, ShooterRPMUncertainty);
  wait(3, sec);
  commisso.spinFeeder(1.0);
  wait(0.25, sec);
  commisso.spinFeeder(0.0);
  commisso.spinShooter(shooterRPM+29, ShooterRPMUncertainty);
  wait(3, sec);
  commisso.spinFeeder(1.0);
  wait(1.0, sec);
  commisso.spinShooter(0.0, ShooterRPMUncertainty); commisso.spinFeeder(0.0);
}

void autonSkill() {
  // Setup
  commisso.setAutonOverride(true);

  mecDrive.driveFwd(1.0);
  commisso.spinRoller(-1.0);
  wait(0.4, sec);
  auton.motorBrake(MoveDelay);
  commisso.spinIntake(1.0);
  auton.moveFwd(-47, 0.8);
  commisso.spinRoller(0.0);
  auton.turn(90.0, 1.0);
  commisso.spinIntake(0.0);
  mecDrive.driveFwd(1.0);
  commisso.spinRoller(-1.0);
  wait(1.0, sec);
  auton.motorBrake(MoveDelay);
  auton.moveFwd(-20, 0.8);
  commisso.spinRoller(0.0);
  auton.turn(180.0, 1.0);
  auton.moveFwd(100, 0.8);
  auton.turn(57, 0.7);
  auton.moveFwd(-30, 0.8);

  commisso.spinShooter(shooterRPM+2, ShooterRPMUncertainty);
  wait(5, sec);
  commisso.spinFeeder(1.0);
  wait(1, sec);
  commisso.spinFeeder(0.0);
  commisso.spinShooter(shooterRPM+6, ShooterRPMUncertainty);
  wait(3, sec);
  commisso.spinFeeder(1.0);
  wait(1.0, sec);
  commisso.spinShooter(0.0, ShooterRPMUncertainty); commisso.spinFeeder(0.0);
}

void autonomous(void) {
  // autonLeft();
  autonRight();
  // autonSkill();
}

double lastMotorAvg = 0, lastTime = 0, lastVolt = 8;

double getMotorAvg() {
  return (ShooterLeft.velocity(rpm)+ShooterRight.velocity(rpm))/2.0;
}
void usercontrol(void) {
  commisso.setAutonOverride(true);

  while (1) {
    // Get Input
    Ct1.setChannels(ControllerJoystickThreshold); Ct1.setButtons();

    // Mecanum Drive
    if (dirFwd) mecDrive.drive(Ct1.getCh3(), Ct1.getCh4(), Ct1.getCh1(), 1.0, MecDriveCorrection);
    // else mecDrive.drive(-Ct1.getCh3(), -Ct1.getCh4(), -Ct1.getCh1(), 100, MecDriveStrafeCorrection);
    
    // Robot Controls
    if (Ct1.getLeftHighTrig()) commisso.spinIntake(1.0);
    else if (Ct1.getLeftLowTrig()) commisso.spinIntake(-100);
    else commisso.spinIntake(0);

    if (Ct1.getRightLowTrig()) commisso.spinFeeder(1.0);
    else if (Ct1.getButtonUp()) commisso.spinRoller(-1.0);
    else commisso.spinFeeder(0);

    if (Ct1.getButtonA()) shooterRPM = FastShooterRPM;
    else if (Ct1.getButtonB()) shooterRPM = SlowShooterRPM;

    if (Ct1.getRightHighTrig()) commisso.spinShooter(shooterRPM, ShooterRPMUncertainty);
    else if (Ct1.getButtonDown()) commisso.spinShooter(-30, ShooterRPMUncertainty);
    // else commisso.spinShooter(0, ShooterRPMUncertainty);

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