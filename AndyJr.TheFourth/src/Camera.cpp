#include <vex.h>
#include "Camera.h"

using namespace vex;

// Program init
#define BS Brain.Screen

void Camera::showView() {
  Vision.takeSnapshot(Vision__REDBASKET);
  Brain.Screen.setFillColor(red);
  for (int i = 0; i < Vision.objectCount; i++) {
    vision::object obj = Vision.objects[i];
    int x = obj.originX*480/316, y = obj.originY*240/212, w = obj.width*480/316, h = obj.height*240/212;
    // BS.drawRectangle(x, y, w, h);
  }
}