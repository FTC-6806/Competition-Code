#pragma config(Hubs,  S1, HTMotor, HTServo, none,  none)
#pragma config(Motor,  mtr_S1_C1_1,     Drive_R,       tmotorTetrix, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Drive_L,       tmotorTetrix, PIDControl, driveLeft, encoder)
#pragma config(Servo,  srvo_S1_C2_1,		GoalGrabber1, tServoStandard)


#include "Header.h"

task main()
{

  nMotorEncoder[Drive_L] = 0;  //clear the TETRIX motor encoders
  nMotorEncoder[Drive_R] = 0;

  nMotorEncoderTarget[Drive_L] = 10; //set the target stoping position
  nMotorEncoderTarget[Drive_R] = 10;

  motor[Drive_L] = 20; //turn both motors on at 30 percent power
  motor[Drive_R] = 20;

  while (nMotorRunState[Drive_L] != runStateIdle || nMotorRunState[Drive_R] != runStateIdle) //while the encoder wheel turns one revolution
  {
    // This condition waits for motors D & E to come to an idle position. Both motors stop
    // and then jumps out of the loop
  }

  motor[Drive_L] = 0; //turn both motors off
  motor[Drive_R] = 0;

  wait1Msec(3000);  // wait 3 seconds to see feedback on the debugger screens
                    // open the "NXT Devices" window to see the distance the encoder spins.
                    // the robot will come to a stop at the nMotorEncoderTarget position.
}
