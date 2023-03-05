#include "main.h"
#include "robot-config.h"
#include "Input.h"
#include "Commisso.h"
#include "Drive.h"
#include "Sensor.h"
#include "Auton.h"

// Parameters
double driveSpd = 1.0;// -1.0 ~ 1.0
const int ROLLER_TO = 2000;// ms
const int SHOOTER_TO = 4;// cnts

// Init objects
Input Ct1;
Drive drive;
Sensor tmpSensor;
Auton auton;

double tmpRPM = 0;

void initialize() {
	lcd::initialize();
	Task shooter_task(tracking_commisso);
	// Task auton_task(tracking_auton);
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

void rollRedR() {
	intake(0.5);
	int stTime = millis();
	while (tmpSensor.getHueR() != 1 && millis() < stTime+ROLLER_TO) {delay(10);}
	intake(0.0);
}

void rollRedL() {
	intake(0.5);
	int stTime = millis();
	while (tmpSensor.getHueL() != 1 && millis() < stTime+ROLLER_TO) {delay(10);}
	intake(0.0);
}

void emptyMag(double rpm) {
	shoot(rpm);
	delay(1900);
	intake(0.45);
	int stTime = millis();
	for (int i = 1; i <= SHOOTER_TO && tmpSensor.getMagDepth() != 0; i++) {
		index(0.7);
		delay(400);
		index(0.0);
		delay(550);
	}
	shoot(0); intake(0.0);
}

void autonSkills() {
	// ~ 38 secs
	drive.moveFwd(0.04);
	rollRedR();
	drive.moveFwd(0.0);
	delay(100);
	auton.pidMove(-10, 1.0);
	auton.pidTurn(110, 1.0);
	intake(1.0);
	auton.pidMove(30, 0.6);
	intake(0.0);
	auton.pidTurn(-24, 1.0);
	auton.pidMove(32, 1.0);
	drive.moveFwd(0.04);
	rollRedR();
	drive.moveFwd(0.0);
	delay(100);
	auton.pidMove(-10, 1.0);

	auton.pidTurn(-89, 1.0);
	auton.pidMove(-100, 1.0);
	emptyMag(340);

	auton.pidTurn(-37, 1.0);
	auton.pidMove(65, 0.6);
	intake(1.0);
	auton.pidMove(80, 0.08);// 0.04
	auton.pidMove(-90, 1.0);
	intake(0.0);
	auton.pidTurn(40, 1.0);
	emptyMag(340);

	// ~ 16 secs
	auton.pidTurn(-93, 1.0);
	intake(1.0);
	auton.pidMove(45, 0.5);
	auton.pidTurn(-42, 1.0);
	auton.pidMove(85, 0.45);
	intake(0.0);
	auton.pidTurn(92, 1.0);
	emptyMag(345);

	// ~ 6 secs
	auton.pidTurn(80, 1.0);// 1.5
	auton.pidMove(200, 1.0);// 2.5
	auton.pidTurn(10, 1.0);// 2.0
	expand(true);
}

void autonomous() {
	// leftField();
	// rightField();
	autonSkills();
	// auton.pidTurn(90, 1.0);

	print(6, "DONE");
}

void opcontrol() {
	const double FAST_RPM = 380, SLOW_RPM = 365;
	double shooterRPM = SLOW_RPM;
	tmpSensor.setOptLED(0.7);

	// bool tmpF = 0;
	while (true) {
		clear();
		print(1, "%d", optL.get_proximity());
		// printf("%d\n", sens.get_value());

		// if (Ct1.getA()) {
		// 	tmpSensor.setOptLED(10);
		// } else if (Ct1.getB()) {
		// 	tmpSensor.setOptLED(25);
		// } else if (Ct1.getX()) {
		// 	tmpSensor.setOptLED(40);
		// } else if (Ct1.getY()) {
		// 	tmpSensor.setOptLED(55);
		// }

		// printf("%.1f\n", opt.get_proximity());
		// cout << opt.get_proximity() << '\n';

		// if (Ct1.getA()) tmpF = 1;
		// else if (Ct1.getB()) tmpF = 0;

		// if (tmpF) shoot(shooterRPM);
		// else shoot(0);

		// Arcade Drive
		drive.arcadeDrive(Ct1.getJoyLY(), Ct1.getJoyRX(), 1.0);

		// Robot Controls
		if (Ct1.getL1()) intake(1.0);
		else if (Ct1.getL2()) intake(-1.0);
		else if (tmpSensor.getMagDepth() == 1 || tmpSensor.getMagDepth() == 2) intake(0.45);
		else intake(0);

		if (Ct1.getR2()) index(0.7);
		else index(0.0);

		if (Ct1.getA()) shooterRPM = SLOW_RPM;
		else if (Ct1.getB()) shooterRPM = FAST_RPM;

		if (Ct1.getR1()) shoot(shooterRPM);
		else if (Ct1.getUp()) shoot(-100);
		else shoot(0);

		if (Ct1.getDown()) expand(true);
		else if (Ct1.getLeft()) expand(false);

		delay(10);
	}
}