class Sensor {
  private:
    const double ENCODER_WHEEL_DIAMETER = 6;// cm
  
  public:
    void resetEncoders();
    double getXEncoderDist(), getYEncoderDist();// cm (*2)
    void resetGyro();
    double getRot();
};