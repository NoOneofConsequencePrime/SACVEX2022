#ifndef INPUT_H
#define INPUT_H

class Input {
  private:
    double Ch1, Ch2, Ch3, Ch4;
    bool leftHighTrig, leftLowTrig, rightHighTrig, rightLowTrig;
  
  public:
    void setChannels(double threshold), setButtons();
    double getCh1(), getCh2(), getCh3(), getCh4();
    bool getLeftHighTrig(), getLeftLowTrig(), getRightHighTrig(), getRightLowTrig();
};

#endif