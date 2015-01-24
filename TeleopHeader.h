#pragma systemFile

// define some buttons we use
#define driverstop joy1Btn(3)
#define gunnerstop joy2Btn(3)
#define revbut joy1Btn(1)
#define drivefast  joy1Btn(5)//||joy1Btn(6)
#define driveslow joy1Btn(7)//||joy1Btn(8)

/* ========< Drivetrain and mechanism >======== */
float drivepower;
// is the servo reversed
bool revmode;

// a position variable for the servo
float servoposition = 100;

// power values for drivetrain
#define lowpower 15.0
#define normpower 39.0
#define highpower 100.0

// joystick deadband
#define deadband 5.0

// defines to calculate left and right drive powers
float leftdrive()
{
	if(ABS(joystick.joy1_y1) < deadband){return 0;}
	else{return joystick.joy1_y1 / 127.0 * drivepower;}
}

float rightdrive()
{
	if(ABS(joystick.joy1_y2) < deadband){return 0;}
	else{return joystick.joy1_y2 / 127.0 * drivepower;}
}
