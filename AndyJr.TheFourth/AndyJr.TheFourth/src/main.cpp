#include "main.h"
#include "robot-config.h"
#include "Input.h"
#include "Commisso.h"
#include "MecDrive.h"
#include "Sensor.h"
#include "Auton.h"

// Parameters
double driveSpd = 1.0;// -1.0 ~ 1.0

// Init objects
Input Ct1;
MecDrive mecDrive;
Sensor tmpSensor;
Auton auton;

double tmpRPM = 0;

void initialize() {
	lcd::initialize();
	Task shooter_task(tracking_commisso);
	Task mecdrive_task(tracking_mec);
}

void disabled() {
}
void competition_initialize() {
}

void leftField() {
	mecMove(0, 1.0);
	intake(-1.0);
	delay(300);
	mecMove(0, 0);
	intake(0.0);
	auton.pidMove(10, 180, 1.0);
	auton.pidTurn(-7.8, 1.0);
	
	shoot(440);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(430);
	delay(2000);
	index(true);
	delay(500);
	index(false);
	shoot(0);
}

void rightField() {
	auton.pidMove(50, 0, 1.0);
	auton.pidTurn(90, 1.0);
	mecMove(0, 0.3);
	intake(-1.0);
	delay(700);
	intake(0.0);
	mecMove(0, 0.0);
	auton.pidMove(10, 180, 1.0);
	intake(0);
	auton.pidTurn(10.2, 1.0);

	shoot(410);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	// shoot(390);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(0);
}

void autonSkills() {
	mecMove(0, 1.0);
	intake(1.0);
	delay(650);
	mecMove(0, 0);
	intake(0.0);
	auton.pidMove(10, 180, 1.0);
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
	auton.pidMove(45, 180, 1.0);
	auton.pidTurn(90, 1.0);
	mecMove(0, 0.4);
	intake(1.0);
	delay(2050);
	intake(0.0);
	mecMove(0, 0.0);
	auton.pidMove(10, 180, 1.0);
	auton.pidTurn(-90, 1.0);
	auton.pidMove(30, 0, 1.0);
	auton.pidTurn(45, 1.0);
	expand(true);
}

void autonomous() {
	// leftField();
	rightField();
	// autonSkills();
}

void opcontrol() {
	const double FAST_RPM = 390, SLOW_RPM = 320;
	double shooterRPM = SLOW_RPM;

	while (true) {
		// Mecanum Drive
		mecDrive.drive(Ct1.getJoyLY(), Ct1.getJoyLX(), Ct1.getJoyRX(), driveSpd);

		// Robot Controls
		if (Ct1.getL1()) intake(1.0);
		else if (Ct1.getL2()) intake(-0.8);
		else intake(0.0);

		if (Ct1.getR2()) index(true);
		else index(false);

		if (Ct1.getB()) shooterRPM = SLOW_RPM;
		else if (Ct1.getA()) shooterRPM = FAST_RPM;

		if (Ct1.getR1()) shoot(shooterRPM);
		else if (Ct1.getUp()) shoot(-100);
		else shoot(0);

		if (Ct1.getDown()) expand(true);
		else if (Ct1.getRight()) expand(false);

		lcd::clear();
		// lcd::print(1, "%.2f", tmp.getRot());
		lcd::print(2, "%.2f", tmpSensor.getYEncoderDist());
		lcd::print(3, "%.2f", tmpSensor.getXEncoderDist());
		// lcd::print(4, "%d", Ct1.getL1());
		// lcd::print(5, "%.2f", commisso.getShooterRPM());

		delay(10);
	}
}