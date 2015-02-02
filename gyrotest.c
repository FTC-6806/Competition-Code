#pragma config(Hubs,  S1, HTMotor, HTServo, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Servo,  srvo_S1_C2_1,		GoalGrabber1, tServoStandard)

#include "Header.h"

task main() {
	initSensor(&gyroSensor, S2);
	startTask(getHeading);
	while (!gyroCalibrated) {}
	playSound(soundBeepBeep);
	drive_distance(12 * 5, 100);
	while(!getXbuttonValue(xButtonEnter)) {}
	//playSound(soundFastUpwardTones);
}
