#include "main.h"

// Motors
Motor leftShooter(0, E_MOTOR_GEAR_600, true), rightShooter(0, E_MOTOR_GEAR_600, false);
Motor intakeA(0, E_MOTOR_GEAR_200, true), intakeB(0, E_MOTOR_GEAR_200, false);
Motor LF(0, E_MOTOR_GEAR_200, false), LB(0, E_MOTOR_GEAR_200, false), RF(0, E_MOTOR_GEAR_200, false), RB(0, E_MOTOR_GEAR_200, false);

// Triport
ADIDigitalOut indexer(1, true);
ADIDigitalOut expansion(0, false);

// Other
Controller master(CONTROLLER_MASTER);
ADIEncoder xEncoder(0, 0, false), yEncoder(0, 0, false);
Imu gyro(0);