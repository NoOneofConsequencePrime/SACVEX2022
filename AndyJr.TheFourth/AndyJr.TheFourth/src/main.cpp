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
}

void disabled() {
}
void competition_initialize() {
}

void autonomous() {
}

void opcontrol() {
	const double FAST_RPM = 450, SLOW_RPM = 370;
	double shooterRPM = SLOW_RPM;

	while (true) {
		// Mecanum Drive
		mecDrive.drive(Ct1.getJoyLY(), Ct1.getJoyLX(), Ct1.getJoyRX(), driveSpd);

		// Robot Controls
		if (Ct1.getL1()) intake(1.0);
		else if (Ct1.getL2()) intake(-1.0);
		else intake(0.0);

		if (Ct1.getR2()) index(true);
		else index(false);

		if (Ct1.getB()) shooterRPM = SLOW_RPM;
		else if (Ct1.getA()) shooterRPM = FAST_RPM;

		if (Ct1.getR1()) shoot(shooterRPM);
		else shoot(0);

		lcd::clear();
		// lcd::print(1, "%.2f", tmp.getRot());
		lcd::print(2, "%.2f", tmpSensor.getYEncoderDist());
		lcd::print(3, "%.2f", tmpSensor.getXEncoderDist());
		// lcd::print(4, "%d", Ct1.getL1());
		// lcd::print(5, "%.2f", commisso.getShooterRPM());

		delay(10);
	}
}