#pragma config(Hubs,  S1, HTMotor, HTMotor, none,  none)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_R,       tmotorTetrix, PIDControl, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_L,       tmotorTetrix, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor, mtr_S1_C2_1,			Back_Arm,      tmotorTetrix, PIDControl, encoder, reversed);
#pragma config(Motor, mtr_S1_C2_2,			Front_Arm,      tmotorTetrix, PIDControl, encoder);


task main()
{
	nMotorEncoder[Back_Arm] = 0;
	nMotorEncoder[Front_Arm] = 0;
	int lastback = 100;
	int lastfront = 100;
	int a = 0;
	int b = 0;
	motor[Back_Arm] = -10;
	motor[Front_Arm] = -10;
	while(a != 1 && b != 1)
	{
		lastback = nMotorEncoder(Back_Arm);
		lastfront = nMotorEncoder(Front_Arm);
		wait1Msec(100);
		if(nMotorEncoder[Back_Arm] == lastback){motor[Back_Arm] = 0; a = 1;}
		if(nMotorEncoder[Front_Arm] == lastfront) {motor[Front_Arm] = 0; b = 1;}
	}
	nMotorEncoder[Back_Arm] = 0;
	nMotorEncoder[Front_Arm] = 0;
}
