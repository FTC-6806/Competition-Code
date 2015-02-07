#pragma config(Hubs,  S1, HTMotor, HTMotor, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor, mtr_S1_C2_1,			Back_Arm,      tmotorTetrix, PIDControl, encoder);
#pragma config(Motor, mtr_S1_C2_2,			Front_Arm,      tmotorTetrix, PIDControl, encoder);

#include "Header.h"

task main() {
	waitForStart();

	motor[Drive_R] = -100;
	motor[Drive_L] = -100;

 	wait1Msec(3500);
 	motor[Drive_L]=0;
 	motor[Drive_R]=0;
 	return;

/*
	turn_degrees(30, 50);
	drive_distance(6,50);
	turn_degrees(30, 50);
	drive_distance(6,50);
	turn_degrees(30, 50);
	drive_distance(2*12, 50);
	turn_degrees(-90, 50);
	drive_distance(4*12, 50);
	turn_degrees(90,50);
	drive_distance(3*12,50);
	initSensor(&gyroSensor, S2);
	startTask(getHeading);
	*/
}
