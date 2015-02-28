#pragma config(Hubs,  S1, HTMotor, HTMotor, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor, mtr_S1_C2_2,			Back_Arm,      tmotorTetrix, PIDControl, encoder, reversed);

#include "Header.h"

task Driver()
{
	while(true)
	{
		getJoystickSettings(joystick);
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

		// -- gunner
		motor[Back_Arm] = map(joystick.joy2_y1, -128, 128, -15, 15);
	}
}

task main()
{
	waitForStart();
	startTask(Driver);

	while(true)
	{
		if(driverstop || gunnerstop){
			stopTask(Driver);
			motor[Drive_R] = 0;
			motor[Drive_L] = 0;
			motor[Back_Arm] = 0;
			while(driverstop || gunnerstop){wait1Msec(1);}
			startTask(Driver);
		}
	}
}
