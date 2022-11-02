#include <vex.h>
#include "Input.h"

using namespace vex;

// Program Init
#define Ct1 Controller1

// Program Parameters
const double threshold = 2;

void Input::updateChannel() {
  Ch1 = (Ct1.Axis1.position(pct) >= threshold || Ct1.Axis1.position(pct) <= -threshold)? Ct1.Axis1.position(pct) : 0;
  Ch2 = (Ct1.Axis2.position(pct) >= threshold || Ct1.Axis2.position(pct) <= -threshold)? Ct1.Axis2.position(pct) : 0;
  Ch3 = (Ct1.Axis3.position(pct) >= threshold || Ct1.Axis3.position(pct) <= -threshold)? Ct1.Axis3.position(pct) : 0;
  Ch4 = (Ct1.Axis4.position(pct) >= threshold || Ct1.Axis4.position(pct) <= -threshold)? Ct1.Axis4.position(pct) : 0;
}

double Input::getCh1() {
  return Ch1;
}
double Input::getCh2() {
  return Ch2;
}
double Input::getCh3() {
  return Ch3;
}
double Input::getCh4() {
  return Ch4;
}