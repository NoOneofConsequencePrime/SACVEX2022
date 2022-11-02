#ifndef INPUT_H
#define INPUT_H

class Input {
  private:
    double Ch1, Ch2, Ch3, Ch4;
  
  public:
    void updateChannel();
    double getCh1(), getCh2(), getCh3(), getCh4();
};

#endif