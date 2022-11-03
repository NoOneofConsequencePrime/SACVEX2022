#ifndef INTAKE_H
#define INTAKE_H

class intake {
  private:
    double Ch1, Ch2, Ch3, Ch4;
  
  public:
    void updateChannel();
    double getCh1(), getCh2(), getCh3(), getCh4();
};

#endif