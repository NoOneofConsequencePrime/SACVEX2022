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
const double FastShooterRPM = 380, SlowShooterRPM = 350;
const double ShooterRPMUncertainty = 20;

// Global Variables
double shooterRPM = SlowShooterRPM;

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

void usercontrol(void) {

  // Init all objects
  Input Ct1;
  MecDrive mecDrive;
  Commisso commisso;

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

    if (Ct1.getButtonA()) shooterRPM = FastShooterRPM;
    else if (Ct1.getButtonB()) shooterRPM = SlowShooterRPM;

    if (Ct1.getRightHighTrig()) commisso.spinShooter(shooterRPM, ShooterRPMUncertainty);
    else if (Ct1.getButtonDown()) commisso.spinShooter(-30, ShooterRPMUncertainty);
    else commisso.spinShooter(0, ShooterRPMUncertainty);

    debug();
    wait(5, msec); 
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
