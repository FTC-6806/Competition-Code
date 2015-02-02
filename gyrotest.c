#pragma config(Hubs,  S1, HTMotor, HTServo, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Servo,  srvo_S1_C2_1,		GoalGrabber1, tServoStandard)

// Current heading of the robot
float currHeading = 0;
float prevHeading = 0;

float totalDrift = 0;

float drivedrift_timeslice = 0;

float dl = 0;
float dr = 0;

#include "Header.h"

float totaldr = 0;

task main() {
	initSensor(&gyroSensor, S2);
	startTask(getHeading);
	while (!gyroCalibrated) {}
	playSound(soundBeepBeep);
	drive_distance(12, 100);
	totaldr = totalDrift;
	dl = motor[Drive_L];
	dr = motor[Drive_R];
	while(!getXbuttonValue(xButtonEnter)) {}
	//playSound(soundFastUpwardTones);
}
