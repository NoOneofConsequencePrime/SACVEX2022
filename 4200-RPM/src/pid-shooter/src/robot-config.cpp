#include "main.h"

// Motors
Motor leftShooter(14, E_MOTOR_GEAR_600, false), rightShooter(15, E_MOTOR_GEAR_600, true);
Motor intakeA(5, E_MOTOR_GEAR_200, true);
Motor LF(7, E_MOTOR_GEAR_200, true), LB(21, E_MOTOR_GEAR_200, true), RF(6, E_MOTOR_GEAR_200, false), RB(20, E_MOTOR_GEAR_200, false);

// Triport
ADIDigitalOut feed(7, true);
// ADIDigitalOut expansion(0, false);

// Other
Controller master(CONTROLLER_MASTER);
// ADIEncoder xEncoder(7, 8, false), yEncoder(6, 5, false);
Imu gyro(4);