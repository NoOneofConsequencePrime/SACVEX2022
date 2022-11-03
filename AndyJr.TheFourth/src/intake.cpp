#include <vex.h>
#include "intake.h"

using namespace vex;

// Program Init
#define Ct1 Controller1

// Program Parameters
const double threshold = 2;

void intake::updateChannel() {
  Ch1 = (Ct1.Axis1.position(pct) >= threshold || Ct1.Axis1.position(pct) <= -threshold)? Ct1.Axis1.position(pct) : 0;
  Ch2 = (Ct1.Axis2.position(pct) >= threshold || Ct1.Axis2.position(pct) <= -threshold)? Ct1.Axis2.position(pct) : 0;
  Ch3 = (Ct1.Axis3.position(pct) >= threshold || Ct1.Axis3.position(pct) <= -threshold)? Ct1.Axis3.position(pct) : 0;
  Ch4 = (Ct1.Axis4.position(pct) >= threshold || Ct1.Axis4.position(pct) <= -threshold)? Ct1.Axis4.position(pct) : 0;
}

double intake::getCh1() {
  return Ch1;
}
double intake::getCh2() {
  return Ch2;
}