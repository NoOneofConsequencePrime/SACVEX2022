#include <vex.h>
#include "Commisso.h"
#include "Input.h"

using namespace vex;

// Program Init

// Program Parameters

// Program Variables/Objects

void Commisso::spinIntake(double maxSpd) {
  Intake.spin(forward, maxSpd, pct);
}
void Commisso::spinFeeder(double maxSpd) {
  Feeder.spin(forward, maxSpd, pct);
}
void Commisso::spinShooter(double spd) {
  ShooterRight.spin(fwd, spd, rpm);
  ShooterLeft.spin(fwd, spd, rpm);
}