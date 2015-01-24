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

#define WHEEL_DIAMETER 3.5 // in
#define WHEEL_CIRCUMFRENCE PI * WHEEL_DIAMETER

#define tickscale 1140.0

void drive_r(float rotations, float power) {
	// reset motor encoders
	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;

	wait1Msec(75);

	nMotorEncoderTarget[Drive_R] = tickscale * rotations;
	nMotorEncoderTarget[Drive_L] = tickscale * rotations;

	// turn motors on
	motor[Drive_R] = power;
	motor[Drive_L] = power;

	while(nMotorRunState[Drive_L] != runStateIdle || nMotorRunState[Drive_R] != runStateIdle) {
		// wait for the motors to come to an idle state
	}

	// turn motors off
	motor[Drive_R] = 0;
	motor[Drive_L] = 0;
}