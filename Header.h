#pragma systemFile

// the joystick driver
#include "Joystickdriver.c"

// define some buttons we use
#define driverstop joy1Btn(3)
#define gunnerstop joy2Btn(3)
#define revbut joy1Btn(1)
#define drivefast  joy1Btn(5)//||joy1Btn(6)
#define driveslow joy1Btn(7)//||joy1Btn(8)

// some useful functions
#define ABS(x)      	    ( (x)>=0?(x):-(x) )
#define MAX(x,y)          ( (x)>(y)?(x):(y) )
#define MIN(x,y)          ( (x)<(y)?(y):(x) )

/* ========< Drivetrain and mechanism >======== */
float drivepower;
// is the servo reversed
bool revmode;

// a position variable for the servo
float servoposition = 100;

// joystick deadband
#define deadband 5
// power values for drivetrain
#define lowpower 15
#define normpower 39
#define highpower 78

// routines to calculate left and right drive powers
float leftdrive()
{
	if(ABS(joystick.joy1_y1) < deadband){return 0;}
	else{return joystick.joy1_y1 / 127 * drivepower;}
}

float rightdrive()
{
	if(ABS(joystick.joy1_y2) < deadband){return 0;}
	else{return joystick.joy1_y2 / 127 * drivepower;}
}


/* ========< Maths >========= */
#define PI 3.14159265358979323846

double map(double x, double in_min, double in_max, double out_min, double out_max)
{
	double slope = 1.0 * (out_max - out_min) / (in_max - in_min);
  return out_min + floor((slope * (x - in_min)) + 0.5);
}

/* ========< Driving functions for autonomous >======== */

#define WHEEL_DIAMETER 3.5 // in
#define WHEEL_CIRCUMFRENCE PI * WHEEL_DIAMETER

// old stuff which shouldn't be depended on
int one_turn = 1440;
int full_turn = 5500; //1325; 5300

// turn: turn the robot
// @param float t : degrees to turn
void turn(float t) {
	t = (t / 360) * full_turn;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;

	if (t>0) {
		nMotorEncoderTarget[Drive_R] = -1 *t;
		nMotorEncoderTarget[Drive_L] = t;

		motor[Drive_R] = -1 * drivepower;
		motor[Drive_L] = drivepower;
	} else {
		nMotorEncoderTarget[Drive_R] = t;
		nMotorEncoderTarget[Drive_L] = -1*t;

		motor[Drive_R] = drivepower;
		motor[Drive_L] = -1 * drivepower;
	}

	while((nMotorRunState[Drive_L] != runStateIdle) && (nMotorRunState[Drive_R] != runStateIdle)) {
		wait1Msec(1);
	}

	motor[Drive_R] = 0;
	motor[Drive_L] = 0;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;
}

// drive: drive the robot
// @param float rotations : rotations to move
void drive_r(float rotations) {
	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;

	nMotorEncoderTarget[Drive_R] = rotations;
 	nMotorEncoderTarget[Drive_L] = rotations;

	motor[Drive_R] = drivepower;
	motor[Drive_L] = drivepower;

	while((nMotorRunState[Drive_L] != runStateIdle) && (nMotorRunState[Drive_R] != runStateIdle)) {
		wait1Msec(1);
	}

	motor[Drive_R] = 0;
	motor[Drive_L] = 0;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;
}

// drive: drive the robot
// @param float distance : distance to move in inches
void drive_d(float distance) {
	float rotations = distance / WHEEL_CIRCUMFRENCE;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;

	nMotorEncoderTarget[Drive_R] = rotations;
 	nMotorEncoderTarget[Drive_L] = rotations;

	motor[Drive_R] = drivepower;
	motor[Drive_L] = drivepower;

	while((nMotorRunState[Drive_L] != runStateIdle) && (nMotorRunState[Drive_R] != runStateIdle)) {
		wait1Msec(1);
	}

	motor[Drive_R] = 0;
	motor[Drive_L] = 0;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;
}
