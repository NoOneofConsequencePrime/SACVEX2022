#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

class motorControl {
  public:
    void drive(double joystickY, double joystickX, double rotationX, double maxSpeed, double strafeCorrection);
};

#endif