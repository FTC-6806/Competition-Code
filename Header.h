////////////////////////////////////////////////////////////////////////////////////
//																																								//
//																																								//
//																																								//
//													 				Global		 																		//
//																																								//
//																																								//
//																																								//
////////////////////////////////////////////////////////////////////////////////////
#include "JoystickDriver.c"

#define resetbtn joy1Btn(3) || joy2Btn(3)
#define killbtn (joystick.joy1_TopHat == 4) || (joystick.joy2_TopHat == 4)
#define overidebtn joy1Btn(1) || joy2Btn(1)

#define boostbtn joy1Btn(6) || joy1Btn(8)
#define turnbtn joy1Btn(5) || joy1Btn(7)
#define togetherbtn joy1Btn(2)

#define joy1L joystick.joy1_y1
#define joy1R joystick.joy1_y2
#define joy2L joystick.joy2_y1
#define joy2R joystick.joy2_y2

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int one_turn = 1440;
int threesixty = 5500; //1325; 5300

#define PI 3.14159265358979323846

typedef struct{
  int full_power;
  int percision_power;
  int current_power;

  float left;
  float right;
} robot_drive_train;

robot_drive_train drive;

int deadband = 5;
bool kill = false;

void configure()
{
	drive.full_power = 100;
	drive.percision_power = 50;
}









////////////////////////////////////////////////////////////////////////////////////
//																																								//
//																																								//
//																																								//
//													 				Teleop		 																		//
//																																								//
//																																								//
//																																								//
////////////////////////////////////////////////////////////////////////////////////
void inverse_slave()
{
	if (abs(drive.left) >= abs(drive.right)) {drive.right = drive.left * -1;} //If left power value is greater or equal to right power value right power value is the inverse of the left power value
	else {drive.left = drive.right * -1;} //If right power value is greater than left power value left power value is the inverse of the right power value
}

void slave()
{
	drive.left = max(drive.left, drive.right); //Left power value is equal to the stronger of the two power values
	drive.right = drive.left; //Sets right power value to left power value
}

void excecute()
{
	motor[Drive_R] = drive.left;
	motor[Drive-L] = drive.right;
}









////////////////////////////////////////////////////////////////////////////////////
//																																								//
//																																								//
//																																								//
//													 				Autonymous 																		//
//																																								//
//																																								//
//																																								//
////////////////////////////////////////////////////////////////////////////////////
void turn(float t)
{
	t = (t / 360) * threesixty;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;

	if (t>0)
	{
		nMotorEncoderTarget[Drive_R] = -1 *t;
 		nMotorEncoderTarget[Drive_L] = t;

		motor[Drive_R] = -1 * drive_power;
		motor[Drive_L] = drive_power;
	}

	else
	{
			nMotorEncoderTarget[Drive_R] = t;
 			nMotorEncoderTarget[Drive_L] = -1*t;

			motor[Drive_R] = drive_power;
			motor[Drive_L] = -1 * drive_power;
	}

	while((nMotorRunState[Drive_L] != runStateIdle) && (nMotorRunState[Drive_R] != runStateIdle)){wait1Msec(1);}

	motor[Drive_R] = 0;
	motor[Drive_L] = 0;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;
}

void drive(float distance, bool dis = false)
{
	if (dis)
	{
		distance = distance / (4 * PI) * 1440;
	}

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;

	nMotorEncoderTarget[Drive_R] = distance;
 	nMotorEncoderTarget[Drive_L] = distance;

	motor[Drive_R] = drive_power;
	motor[Drive_L] = drive_power;

	while((nMotorRunState[Drive_L] != runStateIdle) && (nMotorRunState[Drive_R] != runStateIdle)){wait1Msec(1);}

	motor[Drive_R] = 0;
	motor[Drive_L] = 0;

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;
}
