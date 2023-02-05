#include "main.h"

// Motors
Motor leftShooter(12, E_MOTOR_GEAR_600, false), rightShooter(11, E_MOTOR_GEAR_600, true);
Motor intakeA(19, E_MOTOR_GEAR_200, true), intakeB(20, E_MOTOR_GEAR_200, false);
Motor LF(17, E_MOTOR_GEAR_200, true), LB(14, E_MOTOR_GEAR_200, true), RF(16, E_MOTOR_GEAR_200, false), RB(15, E_MOTOR_GEAR_200, false);

// Triport
ADIDigitalOut indexer(1, true);
ADIDigitalOut expansion(2, false);

// Other
Controller master(CONTROLLER_MASTER);
ADIEncoder xEncoder(7, 8, false), yEncoder(6, 5, false);
Imu gyro(10);