#pragma config(Hubs,  S1, HTMotor, HTMotor, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, reversed, driveLeft, encoder)

#include "Header.h"

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
	//while (true) {
	//	if ((joystick.joy2_y1 < -30) && ( servoposition > (downoverride ? 0 : 54))) {
	//		servoposition -= 0.27;
	//	} else if ((joystick.joy2_y1 > 30) && (servoposition < 230)) {
	//		servoposition += 0.27;
	//	}
	//	servo[GoalGrabber1] = map(servoposition, 0, 360, 0, 255);
	//	//displayStringAt(0, 63, "%i sp", servoposition);
	//}
}

task main()
{
	waitForStart();
	startTask(Driver);
	startTask(Gunner);
	startTask(DriveReverse);

	while(true)
	{
		if(driverstop || gunnerstop){
			stopTask(Driver);
			stopTask(Gunner);
			motor[Drive_R] = 0;
			motor[Drive_L] = 0;
			while(driverstop || gunnerstop){wait1Msec(1);}
			startTask(Driver);
			startTask(Gunner);
		}
	}
}
