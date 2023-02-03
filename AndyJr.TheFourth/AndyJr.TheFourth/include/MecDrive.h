#ifndef MECDRIVE_H
#define MECDRIVE_H

class MecDrive {
  private:
  
  public:
    void set_coast(), set_brake(), set_hold(), brakeAll();
    void drive(double joyY, double joyX, double rotX, double spd);// -127 ~ 127 (*3), -1.0 ~ 1.0
    void turn(double spd);// -1.0 ~ 1.0
    void move(double dir, double spd);// degs, -1.0 ~ 1.0
};

#endif