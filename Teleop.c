#pragma config(Hubs,  S1, HTMotor, HTServo, none,  none)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_R,       tmotorTetrix, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_L,       tmotorTetrix, PIDControl, driveLeft, encoder)
#pragma config(Servo,  srvo_S1_C2_1,		GoalGrabber1, tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    GoalGrabber2, tServoStandard)
#pragma systemFile            // eliminates warning for "unreferenced" functions

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
			motor[Drive_L] = leftdrive;
			motor[Drive_R] = rightdrive;
		}
		else
		{
			motor[Drive_L] = -1*rightdrive;
			motor[Drive_R] = -1*leftdrive;
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
		if ((joystick.joy2_y1 < -30) && (servoposition > 0)) {
			servoposition -= 0.2;
		} else if ((joystick.joy2_y1 > 30) && (servoposition < 255)) {
			servoposition += 0.2;
		}
		servo[GoalGrabber1] = map(servoposition, 0, 360, 0, 255);
		servo[GoalGrabber2] = map((servoposition) - 90, 0, 360, 0, 255);
	}
}

task main()
{
	waitForStart();
	startTask(Driver);
	startTask(Gunner);
	startTask(DriveReverse);
	while(true)
	{
		if(driverstop){
			stopTask(Driver);
			motor[Drive_R] = 0;
			motor[Drive_L] = 0;
			while(!driverstop){wait1Msec(1);}
			startTask(Driver);
		}

		if(gunnerstop){
			stopTask(Gunner);
			while(!gunnerstop){wait1Msec(1);}
			startTask(Gunner);
		}
	}
}
