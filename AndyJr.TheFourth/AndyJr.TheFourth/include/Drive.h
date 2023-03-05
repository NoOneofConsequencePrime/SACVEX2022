#ifndef DRIVE_H
#define DRIVE_H

class Drive {
  private:
  
  public:
    void set_coast(), set_brake(), set_hold(), brakeAll();
    void arcadeDrive(double joyY, double rotX, double spd);// -127 ~ 127 (*2), -1.0 ~ 1.0
    void turn(double spd);// -1.0 ~ 1.0
    void moveFwd(double spd);// -1.0 ~ 1.0
};

#endif