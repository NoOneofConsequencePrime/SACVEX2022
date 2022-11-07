#ifndef MECDRIVE_H
#define MECDRIVE_H

class MecDrive {
  // private:
  
  public:
    void drive(double joyY, double joyX, double rotX, double maxSpd, double strafeCorrection);
};

#endif