#include "main.h"

// Motors
Motor shooter(19, E_MOTOR_GEAR_600, true);
Motor intakeA(11, E_MOTOR_GEAR_200, true), intakeB(20, E_MOTOR_GEAR_200, false);
Motor LF(12, E_MOTOR_GEAR_200, true), LB(9, E_MOTOR_GEAR_200, false), RF(13, E_MOTOR_GEAR_200, true), RB(14, E_MOTOR_GEAR_200, false);
Motor indexer(4, E_MOTOR_GEAR_200, false);

// Triport
// ADIDigitalOut indexer(3, true);
ADIDigitalOut expansion(2, false);

// Other
Controller master(CONTROLLER_MASTER);
ADIEncoder encoder(7, 8, false);
Imu gyro(10);