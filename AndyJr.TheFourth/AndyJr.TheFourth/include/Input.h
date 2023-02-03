#ifndef INPUT_H
#define INPUT_H

class Input {
  private:
    const double DEADZONE_THRESHOLD = 5;
  
  public:
    double getJoyLX(), getJoyLY(), getJoyRX(), getJoyRY();
    bool getL1(), getL2(), getR1(), getR2();
    bool getUp(), getDown(), getLeft(), getRight();
    bool getA(), getB(), getX(), getY();
};

#endif