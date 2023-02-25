#include "main.h"
#include "robot-config.h"
#include "Input.h"
#include "Commisso.h"
#include "Drive.h"
#include "Sensor.h"
#include "Auton.h"

// Parameters
double driveSpd = 1.0;// -1.0 ~ 1.0

// Init objects
Input Ct1;
Drive drive;
Sensor tmpSensor;
Auton auton;

double tmpRPM = 0;

void initialize() {
	lcd::initialize();
	Task shooter_task(tracking_commisso);
	Task mecdrive_task(tracking_drive);
}

void disabled() {
}
void competition_initialize() {
}

void leftField() {
	driveMove(0.2);
	intake(-1.0);
	delay(270);
	driveMove(0);
	intake(0);
	auton.pidMove(-10, 1.0);
	auton.pidTurn(-15, 1.0);

	shoot(480);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(450);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(0);
}

void rightField() {
	auton.pidMove(35, 1.0);
	auton.pidTurn(27, 1.0);
	driveMove(0.3);
	intake(-1.0);
	delay(800);
	driveMove(0);
	intake(0);
	auton.pidMove(-15, 1.0);
	auton.pidTurn(63, 1.0);

	shoot(490);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(495);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(0);
}

void autonSkills() {
	// mecMove(0, 1.0);
	intake(1.0);
	delay(650);
	// mecMove(0, 0);
	intake(0.0);
	auton.pidMove(10, 1.0);
	auton.pidTurn(87, 1.0);
	
	shoot(405);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(395);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(0);

	auton.pidTurn(-87, 1.0);
	auton.pidMove(45, 1.0);
	auton.pidTurn(90, 1.0);
	// mecMove(0, 0.4);
	intake(1.0);
	delay(2050);
	intake(0.0);
	// mecMove(0, 0.0);
	auton.pidMove(10, 1.0);
	auton.pidTurn(-90, 1.0);
	auton.pidMove(30, 1.0);
	auton.pidTurn(45, 1.0);
	expand(true);
}

void autonomous() {
	// leftField();
	rightField();
	// autonSkills();
	// auton.pidTurn(90, 1.0);
}

void opcontrol() {
	const double FAST_RPM = 410, SLOW_RPM = 370;
	double shooterRPM = SLOW_RPM;

	bool tmpF = 0;
	while (true) {
		if (Ct1.getA()) tmpF = 1;
		else if (Ct1.getB()) tmpF = 0;

		if (tmpF) shoot(350);
		else shoot(0);

		if (Ct1.getX()) index(100);
		else index(0);

		// // Arcade Drive
		// drive.arcadeDrive(Ct1.getJoyLY(), Ct1.getJoyRX(), 1.0);

		// // Robot Controls
		// if (Ct1.getL1()) intake(1.0);
		// else if (Ct1.getL2()) intake(-1.0);
		// else intake(0.0);

		// if (Ct1.getR2()) index(true);
		// else index(false);

		// if (Ct1.getA()) shooterRPM = SLOW_RPM;
		// else if (Ct1.getB()) shooterRPM = FAST_RPM;

		// if (Ct1.getR1()) shoot(shooterRPM);
		// else if (Ct1.getUp()) shoot(-100);
		// else shoot(0);

		// if (Ct1.getDown()) expand(true);
		// else if (Ct1.getLeft()) expand(false);

		delay(10);
	}
}