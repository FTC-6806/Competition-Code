#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     Drive_R,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Drive_L,       tmotorTetrix, PIDControl, encoder)

#include "Header.h"

task main()
{
	waitForStart();
	while(true)
	{
		grabjoys();

		if(resetbtn){reset();}

		if(overidebtn){overide();}

		if(killbtn){kill();}

		if(boostbtn){boost();}

		if(turnbtn){turn();}

		if(togetherbtn){together();}

		execute();
	}
}
