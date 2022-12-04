#ifndef CONTROLLERSCRIPT_H
#define CONTROLLERSCRIPT_H

class controllerScript {
  private:
    double Chan1, Chan2, Chan3, Chan4;
    bool leftTrigTop, leftTrigDown, rightTrigTop, rightTrigDown;
  
  public:
    void setChannels(double threshold), setButtons();
    double getChan1(), getChan2(), getChan3(), getChan4();
    bool getLeftTrigTop(), getLeftTrigDown(), getRightTrigTop(), getRightTrigDown();

};

#endif