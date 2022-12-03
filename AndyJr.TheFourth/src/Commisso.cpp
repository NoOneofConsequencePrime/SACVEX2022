#include <vex.h>
#include <algorithm>
#include "Commisso.h"
#include "Input.h"

using namespace vex;

// Program Init

// Program Parameters

// Program Variables/Objects

void Commisso::setAutonOverride(bool autonOverride) {
  this->autonOverride = autonOverride;
}

void Commisso::spinIntake(double spd) {
  Intake.spin(fwd, spd*100.0, pct);
}
void Commisso::spinRoller(double spd) {
  Feeder.spin(fwd, spd*100.0, pct);
}
void Commisso::spinFeeder(double spd) {
  if (RPMReached || autonOverride) Feeder.spin(fwd, spd*100.0, pct);
  else Feeder.spin(fwd, 0, pct);
}
void Commisso::spinShooter(double spd, double targetUncertainty) {// rpm
  ShooterRight.spin(fwd, spd, rpm);
  ShooterLeft.spin(fwd, spd, rpm);

  double avgMotorVel = (ShooterRight.velocity(rpm)+ShooterLeft.velocity(rpm))/2.0;
  if (std::abs(spd-avgMotorVel) < targetUncertainty) RPMReached = 1;
  else RPMReached = 0;
}