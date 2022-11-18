#ifndef INPUT_H
#define INPUT_H

class Input {
  private:
    double Ch1, Ch2, Ch3, Ch4;
    bool leftHighTrig, leftLowTrig;
    bool buttonA, buttonB, buttonX, buttonY;
  
  public:
    void setChannels(double threshold), setButtons();
    double getCh1(), getCh2(), getCh3(), getCh4();
    bool getLeftHighTrig(), getLeftLowTrig();
    bool getButtonA(), getButtonB(), getButtonX(), getButtonY();
};

#endif