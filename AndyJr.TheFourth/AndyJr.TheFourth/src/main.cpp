#include "main.h"

void initialize() {
	lcd::initialize();
	set_text(1, "Running...");
}

void disabled() {}
void competition_initialize() {}

void autonomous() {

}

unsigned int curTime = 0, prevTime = 0;
// double kp = 0.375, ki = 0.0001, kd = 0.00002;// 0.75
// double kp = 0.48, ki = 0.001, kd = 2;
// double kp = 0.3, ki = 0.00035, kd = 0;
// double kp = 0.3, ki = 0.001, kd = 0.2;
/* double kp = 0.3, ki = 0.0003, kd = 0.2; */
double kp = 0.3, ki = 0.00017, kd = 0.2;
double elapsedTime = 0;
double error = 0;
double lastError = 0;
double input = 0, output = 0, setPoint = 250;
double cumError = 0, rateError = 0;
void opcontrol() {
	Motor leftShooter(9, E_MOTOR_GEAR_600, false), rightShooter(7, E_MOTOR_GEAR_600, true);

	Controller master(CONTROLLER_MASTER);
	while (true) {
		if (master.get_digital(DIGITAL_A)) {
			input = (leftShooter.get_actual_velocity()+rightShooter.get_actual_velocity())/2.0;

			curTime = millis();
			elapsedTime = (double)(curTime-prevTime);

			error = setPoint - input;
			cumError += error*elapsedTime;
			rateError = (error-lastError)/elapsedTime;

			double out = kp*error;
			out += ki*cumError;
			out += kd*rateError;

			lastError = error;
			prevTime = curTime;

			leftShooter.move(out); rightShooter.move(out);

			// print(2, "volt: %.2f", out);
			// print(3, "rpm: %.2f", (leftShooter.get_actual_velocity()+rightShooter.get_actual_velocity())/2.0);
			printf("%.1f\n", (leftShooter.get_actual_velocity()+rightShooter.get_actual_velocity())/2.0);
		} else if (master.get_digital(DIGITAL_B)) {
			cumError = 0;
			leftShooter.move(90);
			rightShooter.move(90);
		} else {
			cumError = 0;
			leftShooter.move(0);
			rightShooter.move(0);
		}
		// lcd::print(3, "%.2f", leftShooter.get_voltage()/1000.0);
		delay(20);
		// lcd::clear_line(2);
		// lcd::clear_line(3);
	}
}