#pragma systemFile

#include "Joystickdriver.c"

// define some buttons we use
#define driverstop joy1Btn(3)
#define gunnerstop joy2Btn(3)
#define downoverride joy2Btn(4)
#define revbut joy1Btn(1)
#define drivefast  joy1Btn(5)||joy1Btn(6)
#define driveslow joy1Btn(7)||joy1Btn(8)

/* ========< Drivetrain and mechanism >======== */

// some useful functions
#define ABS(x)      	    ( (x)>=0?(x):-(x) )
#define MAX(x,y)          ( (x)>(y)?(x):(y) )
#define MIN(x,y)          ( (x)<(y)?(y):(x) )

float drivepower;
// is the servo reversed
bool revmode;

// a position variable for the servo
float servoposition = 100;

// power values for drivetrain
#define lowpower 15.0
#define normpower 39.0
#define highpower 100.0

// joystick deadband
#define deadband 5.0

// defines to calculate left and right drive powers
float leftdrive()
{
	if(ABS(joystick.joy1_y1) < deadband){return 0;}
	else{return joystick.joy1_y1 / 127.0 * drivepower;}
}

float rightdrive()
{
	if(ABS(joystick.joy1_y2) < deadband){return 0;}
	else{return joystick.joy1_y2 / 127.0 * drivepower;}
}

/* ========< Maths >========= */

#define PI 3.14159265358979323846

double map(double x, double in_min, double in_max, double out_min, double out_max)
{
	double slope = 1.0 * (out_max - out_min) / (in_max - in_min);
  return out_min + floor((slope * (x - in_min)) + 0.5);
}

/* ========< Driving functions for autonomous >======== */
#include "hitechnic-gyro.h"

// Current heading of the robot
float currHeading = 0;

tHTGYRO gyroSensor;

// Task to keep track of the current heading using the HT Gyro
task getHeading () {
	float delTime = 0;
	float prevHeading = 0;
	float curRate = 0;

	sensorCalibrate(&gyroSensor);
	playSound(soundBeepBeep);
	while (true) {
		time1[T1] = 0;
		readSensor(&gyroSensor);
		curRate = gyroSensor.rotation;
		if (abs(curRate) > 3) {
			prevHeading = currHeading;
			currHeading = prevHeading + curRate * delTime;
			if (currHeading > 360) currHeading -= 360;
			else if (currHeading < 0) currHeading += 360;
		}
		displayTextLine(0, "heading %f", currHeading);
		wait1Msec(5);
		delTime = ((float)time1[T1]) / 1000;
		//delTime /= 1000;
	}
}

// pid

#define PID_MAX_DRIVE       100
#define PID_MIN_DRIVE     (-100)

#define PID_MIN_ERROR 30

#define PID_INTEGRAL_LIMIT  50

float  pid_Kp = 2.0;
float  pid_Ki = 0.04;
float  pid_Kd = 0.0;

float lTarget;
float rTarget;
bool lAttained;
bool rAttained;
bool pidRunning = true;

task pidControl() {
	float rCurrentValue;
	float lCurrentValue;
	float lPidIntegral;
	float rPidIntegral;
	float lPidDerivative;
	float rPidDerivative;
	float lPidDrive;
	float rPidDrive;
	float lPidError;
	float rPidError;
	float lPidLastError;
	float rPidLastError;

	nMotorEncoder[Drive_L] = 0; nMotorEncoder[Drive_R] = 0;

	while (true) {
		if (pidRunning) {
			lCurrentValue = nMotorEncoder[Drive_L];
			rCurrentValue = nMotorEncoder[Drive_R];

			lPidError = lCurrentValue - lTarget; rPidError = rCurrentValue - rTarget;

			if (lPidError < PID_MIN_ERROR) {lPidError = 0; lAttained = true;} else {lAttained=false;}
			if (rPidError < PID_MIN_ERROR) {rPidError = 0; rAttained = true;} else {rAttained=false;}

			if (pid_Ki != 0) {
				if (abs(lPidError) < PID_INTEGRAL_LIMIT) {
					lPidIntegral += lPidError;
				} else {
					lPidIntegral = 0; rPidIntegral = 0;
				}

				if (abs(rPidError) < PID_INTEGRAL_LIMIT) {
					rPidIntegral += rPidError;
				} else {
					rPidIntegral = 0;
				}
			}

			lPidDerivative = lPidError - lPidLastError; rPidDerivative = rPidError - rPidLastError;
			lPidLastError = lPidError; rPidLastError = rPidError;

			lPidDrive = (pid_Kp * lPidError) + (pid_Ki * lPidIntegral) + (pid_Kd * lPidDerivative);
			rPidDrive = (pid_Kp * rPidError) + (pid_Ki * rPidIntegral) + (pid_Kd * rPidDerivative);

			lPidDrive = MAX(lPidDrive, PID_MAX_DRIVE); lPidDrive = MIN(lPidDrive, PID_MIN_DRIVE);
			rPidDrive = MAX(rPidDrive, PID_MAX_DRIVE); rPidDrive = MIN(rPidDrive, PID_MIN_DRIVE);

			motor[Drive_L] = lPidDrive; motor[Drive_R] = rPidDrive;
		}
	}

}

//#define WHEEL_DIAMETER 3.5 // in
#define WHEEL_CIRCUMFRENCE 12.25 //in

#define tickscale 1575.0
#define fullturn tickscale * 4.0

void drive_rotations(float rotations, float power) {
	nMotorEncoder[Drive_L] = 0;
	nMotorEncoder[Drive_R] = 0;

	delay(75);

	lTarget = rotations * tickscale;
	rTarget = rotations * tickscale;

	while (!lAttained || !rAttained) {}
}

void drive_distance(float distance, float power) {
	drive_rotations(distance / WHEEL_CIRCUMFRENCE, power);
}

void turn_degrees(float degrees, float power) {

	// reset motor encoders
	nMotorEncoder[Drive_L] = 0;
	nMotorEncoder[Drive_R] = 0;

	wait1Msec(75); // let encoders settle

	motor[Drive_R] = 0;
	motor[Drive_L] = 0;
}

/* =========< Interfacing >======== */
#define nxt_button_pressed() nNxtButtonPressed != kNoButton
#define is_nxt_button_pressed(btn) nNxtButtonPressed == btn

int get_delay_prompt() {
	int delay_time = 0;
	wait1Msec(1000);
	while (!(is_nxt_button_pressed(kEnterButton))) {
		if (is_nxt_button_pressed(kRightButton)) {
			delay_time += 1;

		} else if (is_nxt_button_pressed(kLeftButton) && delay_time > 0) {
			delay_time -= 1;
		}
		displayStringAt(0, 63, "delay: %i", delay_time);
		wait1Msec(500);
	}

	return delay_time;
}
