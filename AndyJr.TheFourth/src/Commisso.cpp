#include <vex.h>
#include <algorithm>
#include "Commisso.h"
#include "Input.h"

using namespace vex;

// Program Init

// Program Parameters

// Program Variables/Objects

void Commisso::spinIntake(double maxSpd) {
  Intake.spin(fwd, maxSpd, pct);
}
void Commisso::spinFeeder(double maxSpd) {
  if (RPMReached) Feeder.spin(fwd, maxSpd, pct);
}
void Commisso::spinShooter(double spd, double targetUncertainty) {
  ShooterRight.spin(fwd, spd, rpm);
  ShooterLeft.spin(fwd, spd, rpm);

  double avgMotorVel = (ShooterRight.velocity(rpm)+ShooterLeft.velocity(rpm))/2.0;
  if (std::abs(spd-avgMotorVel) < targetUncertainty) RPMReached = 1;
  else RPMReached = 0;
}