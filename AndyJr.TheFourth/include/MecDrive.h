#ifndef MECDRIVE_H
#define MECDRIVE_H

class MecDrive {
  // private:
  
  public:
    void drive(double joyY, double joyX, double rotX, double spd, double strafeCorrection);
    void driveFwd(double spd);
};

#endif