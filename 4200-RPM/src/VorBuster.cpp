#include <vex.h>
#include "VorBuster.h"

using namespace vex;

void VorBuster::spinIntake(double spd) {
  Intake.spin(fwd, spd*100, pct);
}
void VorBuster::spinFeeder(double spd) {
  Feeder.spin(fwd, spd*100, pct);
}
void VorBuster::spinShooter(double spd) {
  Shooter.spin(fwd, spd, rpm);
  Shooter1.spin(fwd, spd, rpm);
}