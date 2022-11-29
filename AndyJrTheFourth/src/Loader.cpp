#include <vex.h>
#include "Loader.h"
#include "Input.h"

using namespace vex;

// Program Init

// Program Parameters

// Program Variables/Objects

void Loader::spinLoader(double maxSpd) {
  LoaderM.spin(forward, maxSpd, pct);
}