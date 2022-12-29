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
  ShooterL.spin(fwd, spd, rpm);
  ShooterR.spin(fwd, spd, rpm);
}