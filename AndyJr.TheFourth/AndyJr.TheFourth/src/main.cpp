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
Commisso commisso;
MecDrive mecDrive;

void initialize() {
	lcd::initialize();
	set_text(1, "Running...");
}

void disabled() {}
void competition_initialize() {}

void autonomous() {

}

void opcontrol() {
	const double FAST_RPM = 450, SLOW_RPM = 370;
	double shooterRPM = SLOW_RPM;

	while (true) {
		// Mecanum Drive
		mecDrive.drive(Ct1.getJoyLY(), Ct1.getJoyLX(), Ct1.getJoyRX(), driveSpd);

		// Robot Controls
		if (Ct1.getL1()) commisso.spinIntake(1.0);
		else if (Ct1.getL2()) commisso.spinIntake(-1.0);
		else commisso.spinIntake(0.0);

		if (Ct1.getR2()) commisso.extendIndexer(true);
		else commisso.extendIndexer(false);

		if (Ct1.getUp()) commisso.spinRoller(1.0);
		else if (Ct1.getDown()) commisso.spinRoller(-1.0);
		else commisso.spinRoller(0.0);

		if (Ct1.getB()) shooterRPM = SLOW_RPM;
		else if (Ct1.getA()) shooterRPM = FAST_RPM;

		if (Ct1.getR1()) commisso.spinShooter(shooterRPM);
		else commisso.spinShooter(0);

		delay(10);
	}
}