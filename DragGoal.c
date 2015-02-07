#pragma config(Hubs,  S1, HTMotor, HTMotor, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor, mtr_S1_C2_1,			Back_Arm,      tmotorTetrix, PIDControl, encoder);
#pragma config(Motor, mtr_S1_C2_2,			Front_Arm,      tmotorTetrix, PIDControl, encoder);

#include "Header.h"

task main() {
	//int delayms = 1000 * get_delay_prompt();
	waitForStart();
	//wait1Msec(delayms);
	drive_distance(-6*12, 50); // Drive 1 foot at 1/2 power
	//turn_degrees(-5,35);

	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;


	servoposition = 120;

	servo[GoalGrabber1] = map(servoposition, 0, 360, 0, 255);

 nMotorEncoder[Drive_L] = 0;//reset the value of encoder B to zero
 nMotorEncoder[Drive_R] = 0;//reset the value of encoder C to zero


 while(SensorValue(touch) == 0)
	{
	motor[Drive_R] = -50;
	motor[Drive_L] = -50;
	}
	motor[Drive_R] = 0;
	motor[Drive_L] = 0;

	servoposition = 10;
	servo[GoalGrabber1] = map(servoposition, 0, 360, 0, 255);
	delay(1000);
	sleep(1000);
	while(nMotorEncoder[Drive_L] < 0 && nMotorEncoder[Drive_R] < 0)
	{
	motor[Drive_R] = 50;
	motor[Drive_L] = 50;
	}
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
}
