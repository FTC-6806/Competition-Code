#include "Joystickdriver.c"
#define driverstop joy1Btn(3)
#define gunnerstop joy2Btn(3)
#define revbut joy1Btn(1)
#define drivefast  joy1Btn(5)||joy1Btn(6)
#define driveslow joy1Btn(7)||joy1Btn(8)

#define ABS(x)      	    ( (x)>=0?(x):-(x) )
#define MAX(x,y)          ( (x)>(y)?(x):(y) )
#define MIN(x,y)          ( (x)<(y)?(y):(x) )

#define leftdrive (ABS(joystick.joy1_y1)>deadband?(joystick.joy1_y1 / 127 * drivepower):0)
#define rightdrive (ABS(joystick.joy1_y2)>deadband?(joystick.joy1_y2 / 127 * drivepower):0)

float drivepower;
bool revmode;


//////////////////////////////////////////////////////////////////////////////////
//																																							//
//															Settings																				//
//																																							//
//////////////////////////////////////////////////////////////////////////////////

int deadband = 5;
float lowpower = 25;
float normpower = 50;
float highpower = 100;


///////////////////////////////////////////////////////////////////
//
//                 Driving functions
//
//////////////////////////////////////////////////////////////////

#define PI 3.14159265358979323846
#define WHEEL_DIAMETER 3.5 // in
#define WHEEL_CIRCUMFRENCE pi * WHEEL_DIAMETER


void turn(float t) {
	t = (t / 360) * full_turn;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;

	if (t>0) {
		nMotorEncoderTarget[Drive_R] = -1 *t;
		nMotorEncoderTarget[Drive_L] = t;

		motor[Drive_R] = -1 * drive_power;
		motor[Drive_L] = drive_power;
	} else {
		nMotorEncoderTarget[Drive_R] = t;
		nMotorEncoderTarget[Drive_L] = -1*t;

		motor[Drive_R] = drive_power;
		motor[Drive_L] = -1 * drive_power;
	}

	while((nMotorRunState[Drive_L] != runStateIdle) && (nMotorRunState[Drive_R] != runStateIdle)) {
		wait1Msec(1);
	}

	motor[Drive_R] = 0;
	motor[Drive_L] = 0;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;
}

void drive(float distance, bool dis = false) {
	if (dis) {
		distance = distance / WHEEL_CIRCUMFRENCE;
	}

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;

	nMotorEncoderTarget[Drive_R] = distance;
 	nMotorEncoderTarget[Drive_L] = distance;

	motor[Drive_R] = drive_power;
	motor[Drive_L] = drive_power;

	while((nMotorRunState[Drive_L] != runStateIdle) && (nMotorRunState[Drive_R] != runStateIdle)) {
		wait1Msec(1);
	}

	motor[Drive_R] = 0;
	motor[Drive_L] = 0;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;
}