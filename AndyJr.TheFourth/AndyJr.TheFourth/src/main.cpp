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
const int SHOOTER_TO = 3;// cnts

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

void rollRedR(double spd) {
	intake(spd);
	int stTime = millis();
	while (tmpSensor.getHueR() != 1 && millis() < stTime+ROLLER_TO) {delay(10);}
	intake(0.0);
}

void rollRedL(double spd) {
	intake(spd);
	int stTime = millis();
	while (tmpSensor.getHueL() != 1 && millis() < stTime+ROLLER_TO) {delay(10);}
	intake(0.0);
}

void rollBlueR(double spd) {
	intake(spd);
	int stTime = millis();
	while (tmpSensor.getHueR() != 0 && millis() < stTime+ROLLER_TO) {delay(10);}
	intake(0.0);
}

void rollBlueL(double spd) {
	intake(spd);
	int stTime = millis();
	while (tmpSensor.getHueL() != 0 && millis() < stTime+ROLLER_TO) {delay(10);}
	intake(0.0);
}

void emptyMag(double rpm, bool stable) {
	shoot(rpm);
	delay(1900);
	if (stable) delay(200);
	intake(0.45);
	for (int i = 1; i <= SHOOTER_TO && tmpSensor.getMagDepth() != 0; i++) {
		index(1.0);
		delay(350);
		index(0.0);
		delay(650);
		if (stable) delay(400);
	}
	shoot(0); intake(0.0);
}

void leftFieldRed() {
	drive.moveFwd(0.05);
	rollRedR(0.7);
	drive.moveFwd(0.0);

	auton.pidMove(-10, 1.0);
	auton.pidTurn(-11, 1.0);
	emptyMag(390, true);

	auton.pidTurn(-117, 1.0);
	auton.pidMove(50, 0.6);
	intake(1.0);
	auton.pidMove(80, 0.08);
	intake(0.0);
}

void leftFieldBlue() {
	drive.moveFwd(0.05);
	rollBlueR(0.7);
	drive.moveFwd(0.0);

	auton.pidMove(-10, 1.0);
	auton.pidTurn(-11, 1.0);
	emptyMag(390, true);

	auton.pidTurn(-117, 1.0);
	auton.pidMove(50, 0.6);
	intake(1.0);
	auton.pidMove(80, 0.08);
	intake(0.0);
}

void rightFieldRed() {
	auton.pidMove(40, 1.0);
	auton.pidTurn(90, 1.0);
	drive.moveFwd(0.06);
	rollRedL(-0.7);
	drive.moveFwd(0.0);

	auton.pidMove(-10, 1.0);
	intake(1.0);
	auton.pidTurn(13, 1.0);
	emptyMag(390, true);
	intake(0.0);
}

void rightFieldBlue() {
	auton.pidMove(40, 1.0);
	auton.pidTurn(90, 1.0);
	drive.moveFwd(0.06);
	rollBlueL(-0.7);
	drive.moveFwd(0.0);

	auton.pidMove(-10, 1.0);
	intake(1.0);
	auton.pidTurn(13, 1.0);
	emptyMag(390, true);
	intake(0.0);
}

void autonSkills() {
	// ~ 38 secs
	drive.moveFwd(0.04);
	rollRedR(0.5);
	drive.moveFwd(0.0);
	delay(100);
	auton.pidMove(-10, 1.0);
	intake(1.0);
	auton.pidTurn(110, 1.0);
	auton.pidMove(30, 0.6);
	auton.pidTurn(-22, 1.0);
	intake(0.0);
	auton.pidMove(32, 1.0);
	drive.moveFwd(0.04);
	rollRedR(0.5);
	drive.moveFwd(0.0);
	delay(100);
	auton.pidMove(-10, 1.0);

	auton.pidTurn(-90.5, 1.0);
	auton.pidMove(-100, 1.0);
	emptyMag(345, false);

	auton.pidTurn(-37, 1.0);
	auton.pidMove(75, 0.6);
	intake(1.0);
	auton.pidMove(80, 0.08);// 0.04
	auton.pidMove(-90, 1.0);
	intake(0.0);
	auton.pidTurn(34, 1.0);
	emptyMag(343, false);

	// ~ 16 secs
	intake(1.0);
	auton.pidTurn(-90, 1.0);
	auton.pidMove(45, 0.5);
	auton.pidTurn(-42, 1.0);
	auton.pidMove(85, 0.45);
	intake(0.0);
	auton.pidTurn(92, 1.0);
	emptyMag(340, false);

	// ~ 6 secs
	auton.pidTurn(81.5, 1.0);// 1.5
	auton.pidMove(175, 1.0);// 2.5
	auton.pidTurn(15, 1.0);// 2.0
	expand(true);
}

void autonomous() {
	// leftFieldRed();
	// leftFieldBlue(); 
	// rightFieldRed();
	// rightFieldBlue();
	autonSkills();

	print(6, "DONE");
}

void opcontrol() {
	const double FAST_RPM = 390, SLOW_RPM = 375;
	double shooterRPM = SLOW_RPM;
	tmpSensor.setOptLED(0.7);

	// bool tmpF = 0;
	bool rollT = false;
	int targetRoll = 1;// 1 red, 0 blue
	while (true) {
		clear();
		print(1, "%d", tmpSensor.getMagDepth());
		// printf("%d\n", sens.get_value());

		// if (Ct1.getA()) tmpF = 1;
		// else if (Ct1.getB()) tmpF = 0;

		// if (tmpF) shoot(400);
		// else shoot(0);

		// Arcade Drive
		drive.arcadeDrive(Ct1.getJoyLY(), Ct1.getJoyRX(), 1.0);

		// Robot Controls
		if (Ct1.getL1()) {
			intake(1.0);
			rollT = false;
		} else if (Ct1.getL2()) {
			intake(-1.0);
			rollT = false;
		} else intake(0);

		if (Ct1.getR2()) index(0.8);
		else index(0.0);

		if (Ct1.getX()) rollT = true;
		else if (Ct1.getY()) rollT = false;
		if (rollT && !(tmpSensor.getHueL() == targetRoll || tmpSensor.getHueR() == targetRoll)) {
			intake(1.0);
		} else if (rollT) {
			delay(100);
			intake(0.0);
			rollT = false;
		}

		if (Ct1.getA()) shooterRPM = SLOW_RPM;
		else if (Ct1.getB()) shooterRPM = FAST_RPM;

		if (Ct1.getR1()) {
			shoot(shooterRPM);
			if (tmpSensor.getMagDepth() == 1 || tmpSensor.getMagDepth() == 2) intake(0.45);
		} else if (Ct1.getUp()) {
			index(-0.4);
			shoot(-100);
		} else shoot(0);

		if (Ct1.getDown()) expand(true);
		else if (Ct1.getLeft()) expand(false);

		delay(10);
	}
}