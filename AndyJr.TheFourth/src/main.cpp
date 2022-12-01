#include <vex.h>
#include "Input.h"
#include "MecDrive.h"
#include "Commisso.h"
#include "Auton.h"

using namespace vex;

// Program init
#define print Brain.Screen.print
#define setCursor Brain.Screen.setCursor

competition Competition;

// Parameters
const double WasteDelay = 5;// msec
const double MecDriveStrafeCorrection = 1.0;
const double ControllerJoystickThreshold = 2;
const double FastShooterRPM = 350, SlowShooterRPM = 310;
const double ShooterRPMUncertainty = 30;
const double DistErrorMargin = 1;// cm
const double DistKP = 0.35;
const double DirErrorMargin = 1;// deg
const double DirKP = 3.0;
const double RotErrorMargin = 0.5;// deg
const double RotKP = 2.5;
const double MoveDelay = 100;// msec
const double AmbientRotDer = 500;// dr/dt (deg)

// Global Variables
double shooterRPM = FastShooterRPM;
bool dirFwd = 1;

// Init all objects
Input Ct1;
MecDrive mecDrive;
Commisso commisso;
Auton auton(WasteDelay);

double lastTime;

void debug() {
  Brain.Screen.clearScreen();

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

  // setCursor(1, 1);
  // print("dy/dx: ");
  // double tmp = auton.getRotOverTime();
  // double tmpV = 500;
  // if (tmp > tmpV || tmp < -tmpV) print(tmp);

  setCursor(1, 1);
  print("dydx: ");
  double tmp = auton.getDistOverTime();
  if (tmp != 0) print(tmp*1e2);
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
  auton.turn(90, 1.0, RotErrorMargin, RotKP, AmbientRotDer, MoveDelay);
  debug();

  // mecDrive.driveFwd(1.0);
  // commisso.spinIntake(1.0);
  // wait(1.5, sec);
  // auton.moveFwdPID(-10, 0.8, DistErrorMargin, DistKP, DirErrorMargin, DirKP, MoveDelay);
  // commisso.spinIntake(0.0);
  // auton.moveFwdPID(-40, 0.8, DistErrorMargin, DistKP, DirErrorMargin, DirKP, MoveDelay);
  // // auton.turn(90, 1.0, RotErrorMargin, RotKP, MoveDelay);
  // commisso.spinIntake(-1.0);
  // mecDrive.driveFwd(1.0);
  // wait(1.5, sec);
  // auton.moveFwdPID(-20, 0.8, DistErrorMargin, DistKP, DirErrorMargin, DirKP, MoveDelay);
  // commisso.spinIntake(0.0);
}

void usercontrol(void) {
  while (1) {
    // Get Input
    Ct1.setChannels(ControllerJoystickThreshold); Ct1.setButtons();

    // Mecanum Drive
    if (dirFwd) mecDrive.drive(Ct1.getCh3(), Ct1.getCh4(), Ct1.getCh1(), 100, MecDriveStrafeCorrection);
    // else mecDrive.drive(-Ct1.getCh3(), -Ct1.getCh4(), -Ct1.getCh1(), 100, MecDriveStrafeCorrection);
    
    // Robot Controls
    if (Ct1.getLeftHighTrig()) commisso.spinIntake(100);
    else if (Ct1.getLeftLowTrig()) commisso.spinIntake(-100);
    else commisso.spinIntake(0);

    if (Ct1.getRightLowTrig()) commisso.spinFeeder(100);
    else commisso.spinFeeder(0);

    if (Ct1.getButtonA()) shooterRPM = FastShooterRPM;
    else if (Ct1.getButtonB()) shooterRPM = SlowShooterRPM;

    if (Ct1.getRightHighTrig()) commisso.spinShooter(shooterRPM, ShooterRPMUncertainty);
    else if (Ct1.getButtonDown()) commisso.spinShooter(-30, ShooterRPMUncertainty);
    else commisso.spinShooter(0, ShooterRPMUncertainty);

    // if (Ct1.getButtonX()) auton.turn(-20, 1.0, RotErrorMargin, RotKP, MoveDelay);
    // if (Ct1.getButtonX()) dirFwd = 1;
    // else if (Ct1.getButtonY()) dirFwd = 0;

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