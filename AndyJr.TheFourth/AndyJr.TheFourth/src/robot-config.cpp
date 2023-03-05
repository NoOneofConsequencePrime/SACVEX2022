#include "main.h"

// Motors
Motor shooter(7, E_MOTOR_GEAR_600, true);
Motor intakeA(9, E_MOTOR_GEAR_600, false), intakeB(10, E_MOTOR_GEAR_600, false);
Motor LF(11, E_MOTOR_GEAR_600, true), LB(12, E_MOTOR_GEAR_600, false), RF(19, E_MOTOR_GEAR_600, true), RB(20, E_MOTOR_GEAR_600, false);
Motor indexer(8, E_MOTOR_GEAR_200, true);

// Triport
ADIDigitalOut expA(5, false), expB(6, false);
ADIUltrasonic magSense(1, 2);

// Other
Controller master(CONTROLLER_MASTER);
ADIEncoder encoder(7, 8, false);
Imu gyro(4);
Optical optL(6), optR(5);