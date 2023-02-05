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

void autonomous() {
	mecMove(0, 1.0);
	intake(-1.0);
	delay(300);
	mecMove(0, 0);
	intake(0.0);
	auton.pidMove(10, 180, 1.0);
	auton.pidTurn(-7.6, 1.0);
	
	shoot(450);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(445);
	delay(2000);
	index(true);
	delay(500);
	index(false);
	shoot(0);

	/*auton.pidMove(60, 0, 1.0);
	auton.pidTurn(90, 1.0);
	mecMove(0, 0.3);
	intake(-1.0);
	delay(1000);
	intake(0.0);
	mecMove(0, 0.0);
	auton.pidMove(10, 180, 1.0);
	intake(0);
	auton.pidTurn(13, 1.0);

	shoot(460);
	delay(3000);
	index(true);
	delay(500);
	index(false);
	shoot(450);
	delay(2000);
	index(true);
	delay(500);
	index(false);
	shoot(0);*/
}

void opcontrol() {
	const double FAST_RPM = 420, SLOW_RPM = 350;
	double shooterRPM = FAST_RPM;

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