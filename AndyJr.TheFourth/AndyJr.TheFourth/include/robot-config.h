#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

// Motors
extern Motor leftShooter, rightShooter;
extern Motor intakeA, intakeB;
extern Motor LF, LB, RF, RB;

// Triport
extern ADIDigitalOut indexer;
extern ADIDigitalOut expansion;

// Other
extern Controller master;
extern ADIEncoder xEncoder, yEncoder;
extern Imu gyro;

#endif