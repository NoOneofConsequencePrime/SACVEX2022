#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

// Motors
extern Motor shooter;
extern Motor intakeA, intakeB;
extern Motor LF, LB, RF, RB;
extern Motor indexer;

// Triport
extern ADIDigitalOut expA, expB;// expansion
extern ADIUltrasonic magSense;

// Other
extern Controller master;
extern ADIEncoder encoder;
extern Imu gyro;
extern Optical optL, optR;

#endif