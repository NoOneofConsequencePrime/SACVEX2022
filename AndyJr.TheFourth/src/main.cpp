#include <vex.h>
#include <algorithm>
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

  // setCursor(1, 1);
  // print("dydx: ");
  // double tmp = auton.getDistOverTime();
  // if (tmp != 0) print(tmp);

  // setCursor(1, 1);
  // print("rpm: ");
  // print(std::abs(ShooterRight.velocity(rpm)-300));
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
  // Setup
  commisso.setAutonOverride(true);

  mecDrive.driveFwd(1.0);
  commisso.spinRoller(1.0);
  wait(0.5, sec);
  auton.motorBrake(MoveDelay);
  auton.moveFwd(-10, 0.8);
  commisso.spinRoller(0.0);
  commisso.spinIntake(1.0);
  auton.turn(-90, 1.0);
  commisso.spinIntake(0.0);
  auton.moveFwd(127, 1.0);
  auton.turn(55, 0.7);
  auton.moveFwd(-92, 0.8);

  commisso.spinShooter(shooterRPM, ShooterRPMUncertainty);
  wait(3, sec);
  commisso.spinFeeder(1.0);
  wait(0.3, sec);
  commisso.spinFeeder(0.0);
  wait(3, sec);
  commisso.spinFeeder(1.0);
  wait(1.0, sec);
  commisso.spinShooter(0.0, ShooterRPMUncertainty); commisso.spinFeeder(0.0);
}

/*
double Auton::getDistOverTime() {
  double curMotorAvg = getAvgMotorPos(LF.position(deg), LB.position(deg), RF.position(deg), RB.position(deg));
  double lastMotorAvg = getAvgMotorPos(lastMotorPos.LF, lastMotorPos.LB, lastMotorPos.RF, lastMotorPos.RB);
  double dDist = curMotorAvg-lastMotorAvg, dTime = Brain.Timer-lastTime;
  lastMotorPos = {LF.position(deg), LB.position(deg), RF.position(deg), RB.position(deg)}; lastTime = Brain.Timer;

  double dydx = dDist/dTime*1e2;
  if (dTime > WasteDelay) return 0;
  return dydx;
}
*/

double lastMotorAvg = 0, lastTime = 0, lastVolt = 8;

double getMotorAvg() {
  return (ShooterLeft.velocity(rpm)+ShooterRight.velocity(rpm))/2.0;
}
void usercontrol(void) {
  commisso.setAutonOverride(false);

  while (1) {
    // Get Input
    Ct1.setChannels(ControllerJoystickThreshold); Ct1.setButtons();

    // Mecanum Drive
    if (dirFwd) mecDrive.drive(Ct1.getCh3(), Ct1.getCh4(), Ct1.getCh1(), 1.0, MecDriveStrafeCorrection);
    // else mecDrive.drive(-Ct1.getCh3(), -Ct1.getCh4(), -Ct1.getCh1(), 100, MecDriveStrafeCorrection);
    
    // Robot Controls
    if (Ct1.getLeftHighTrig()) commisso.spinIntake(1.0);
    else if (Ct1.getLeftLowTrig()) commisso.spinIntake(-100);
    else commisso.spinIntake(0);

    if (Ct1.getRightLowTrig()) commisso.spinFeeder(1.0);
    else commisso.spinFeeder(0);

    if (Ct1.getButtonA()) shooterRPM = FastShooterRPM;
    else if (Ct1.getButtonB()) shooterRPM = SlowShooterRPM;

    if (Ct1.getRightHighTrig()) commisso.spinShooter(shooterRPM, ShooterRPMUncertainty);
    else if (Ct1.getButtonDown()) commisso.spinShooter(-30, ShooterRPMUncertainty);
    else commisso.spinShooter(0, ShooterRPMUncertainty);

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