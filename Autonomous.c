#pragma config(Hubs,  S1, HTMotor, HTServo, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, driveLeft, encoder)
#pragma config(Servo,  srvo_S1_C2_1,		GoalGrabber1, tServoStandard)
#pragma config(Sensor, S2, touch, sensorTouch)

#include "Header.h"

task main()
{


	nMotorEncoder[Drive_R] = 0;
	nMotorEncoder[Drive_L] = 0;

	motor[Drive_R] = 50;
	motor[Drive_L] = 50;

	while((nMotorEncoder[Drive_L] < 100) && (nMotorEncoder[Drive_R] < 100)) {
		wait1Msec(1);
	}

	motor[Drive_R] = 0;
	motor[Drive_L] = 0;


	//servoposition = 120;
	//waitForStart();
	//servo[GoalGrabber1] = map(servoposition, 0, 360, 0, 255);

 //nMotorEncoder[Drive_L] = 0;//reset the value of encoder B to zero
 //nMotorEncoder[Drive_R] = 0;//reset the value of encoder C to zero

	//motor[Drive_R] = 50;
 //while(SensorValue(touch) == 0)
	//{
	//motor[Drive_L] = 50;
	//}

	//servoposition = 20;
	//servo[GoalGrabber1] = map(servoposition, 0, 360, 0, 255);

	//while(nMotorEncoder[Drive_L] > 0)
	//{
	//motor[Drive_R] = -50;
	//motor[Drive_L] = -50;
	//}
	//wait1Msec(500);
}
