#include <vex.h>
#include "Shooter.h"
#include "Input.h"

using namespace vex;

// Program Init

// Program Parameters

// Program Variables/Objects

void Shooter::spinShooter(double maxSpd) {
  FlywheelR.spin(forward, maxSpd, pct);
  FlywheelL.spin(forward, maxSpd, pct);
}