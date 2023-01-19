#ifndef CAMERA_H
#define CAMERA_H

class Camera {
  private:
    double minW = 38, minH = 10, maxW = 60, maxH = 32;
  public:
    void showView();
};

#endif