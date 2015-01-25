#pragma config(Hubs,  S1, HTMotor, HTServo, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Servo,  srvo_S1_C2_1,		GoalGrabber1, tServoStandard)

#include "Header.h"

task main() {
	int delayms = 1000 * get_delay_prompt();
	waitForStart();
	wait1Msec(delayms);
	drive_distance(12, 39); // Drive 1 foot at 1/2 power
	// (which is actually 39% percent because neverest encoders)
}
