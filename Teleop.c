#pragma config(Hubs,  S1, HTMotor, HTMotor, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor, mtr_S1_C2_2,			Back_Arm,      tmotorTetrix, PIDControl, encoder, reversed);

#include "Header.h"

int bTarget = 40;
//int fTarget = 40;

void zeroArms() {
	nMotorEncoder[Back_Arm] = 0;
	//nMotorEncoder[Front_Arm] = 0;
	int lastback = 100;
	//int lastfront = 100;
	int a = 0;
	//int b = 0;
	motor[Back_Arm] = -10;
	//motor[Front_Arm] = -10;
	while(a != 1 /*&& b != 1*/)
	{
		lastback = nMotorEncoder(Back_Arm);
		//lastfront = nMotorEncoder(Front_Arm);
		wait1Msec(100);
		if(nMotorEncoder[Back_Arm] == lastback){motor[Back_Arm] = 0; a = 1;}
	}
	nMotorEncoder[Back_Arm] = 0;
}

task Driver()
{
	while(true)
	{
		if(drivefast) {
			drivepower = highpower;
		} else if (driveslow) {
			drivepower = lowpower;
		} else {
			drivepower = normpower;
		}

		if(!revmode)
		{
			motor[Drive_L] = leftdrive();
			motor[Drive_R] = rightdrive();
		}
		else
		{
			motor[Drive_L] = -1*rightdrive();
			motor[Drive_R] = -1*leftdrive();
		}
	}
}

task DriveReverse()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(revbut && revmode)
		{
			revmode = false;
			while(revbut){wait1Msec(1);}
		}
		if(revbut && !revmode)
		{
			revmode = true;
			while(revbut){wait1Msec(1);}
		}
	}
}

task Gunner() {
	while (true) {
		wait1Msec(10);
		if ((joystick.joy2_y1 < -30)) {
			bTarget -= 1;
		} else if ((joystick.joy2_y1 > 30)) {
			bTarget += 1;
		}
		if (resettozero) {
			zeroArms();
		}
	}
}

task Arms() {
	const int Kp = 1;
	int bError = bTarget - nMotorEncoder[Back_Arm];
	while (true) {
		bError = bTarget - nMotorEncoder[Back_Arm];
		int bPower = (int)(Kp*bError);
		if (bPower > 100) { bPower = 100; } else if (bPower < -100) { bPower = -100; }
		motor[Back_Arm] = bPower;
	}
}

task main()
{
	waitForStart();
	zeroArms();
	startTask(Driver);
	startTask(DriveReverse);
	startTask(Arms);
	startTask(Gunner);

	while(true)
	{
		displayTextLine(0, "%f", bTarget);
		if(driverstop || gunnerstop){
			stopTask(Driver);
			stopTask(Gunner);
			stopTask(Arms);
			motor[Drive_R] = 0;
			motor[Drive_L] = 0;
			motor[Back_Arm] = 0;
			while(driverstop || gunnerstop){wait1Msec(1);}
			startTask(Driver);
			startTask(Gunner);
			startTask(Arms);
		}
	}
}
