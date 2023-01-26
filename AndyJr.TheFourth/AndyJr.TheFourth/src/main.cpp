#include "main.h"

using namespace pros;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

unsigned int curTime = 0, prevTime = 0;
// double kp = 0.375, ki = 0.0001, kd = 0.00002;// 0.75
double kp = 0.48, ki = 0.001, kd = 2;
double elapsedTime = 0;
double error = 0;
double lastError = 0;
double input = 0, output = 0, setPoint = 350;
double cumError = 0, rateError = 0;
void opcontrol() {
	Motor leftShooter(19, E_MOTOR_GEAR_600, false), rightShooter(20, E_MOTOR_GEAR_600, true);

	Controller master(pros::E_CONTROLLER_MASTER);

	screen::set_pen(COLOR_BLUE);
	while (true) {
		if (master.get_digital(DIGITAL_A)) {
			input = (leftShooter.get_actual_velocity()+rightShooter.get_actual_velocity())/2.0;

			curTime = millis();
			if (prevTime != 0) elapsedTime = (double)(curTime-prevTime);

			error = setPoint - input;
			cumError += error*elapsedTime;
			rateError = (error-lastError)/elapsedTime;

			double out = kp*error;
			out += ki*cumError;
			out += kd*rateError;

			lastError = error;
			prevTime = curTime;

			leftShooter.move(out); rightShooter.move(out);

			lcd::print(2, "volt: %.2f", out);
			lcd::print(3, "rpm: %.2f", (leftShooter.get_actual_velocity()+rightShooter.get_actual_velocity())/2.0);
		} else if (master.get_digital(DIGITAL_B)) {
			cumError = 0; prevTime = 0;
			leftShooter.move(90);
			rightShooter.move(90);
		} else {
			cumError = 0; prevTime = 0;
			leftShooter.move(0);
			rightShooter.move(0);
		}
		// lcd::print(3, "%.2f", leftShooter.get_voltage()/1000.0);
		pros::delay(5);
		// lcd::clear_line(2);
		// lcd::clear_line(3);
	}
}