#include <vex.h>
#include "Roller.h"
#include "Input.h"

using namespace vex;

// Program Init

// Program Parameters

// Program Variables/Objects

void Roller::spinRoller(double maxSpd) {
  Intake.spin(forward, maxSpd, pct);
}