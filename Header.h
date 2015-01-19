#include "Joystickdriver.c"
#define driverstop joy1Btn(3)
#define gunnerstop joy2Btn(3)
#define revbut joy1Btn(1)
#define drivefast  joy1Btn(5)||joy1Btn(6)
#define driveslow joy1Btn(7)||joy1Btn(8)

#define ABS(x)      	    ( (x)>=0?(x):-(x) )
#define MAX(x,y)          ( (x)>(y)?(x):(y) )
#define MIN(x,y)          ( (x)<(y)?(y):(x) )

#define leftdrive (ABS(joystick.joy1_y1)>deadband?(joystick.joy1_y1 / 127 * drivepower):0)
#define rightdrive (ABS(joystick.joy1_y2)>deadband?(joystick.joy1_y2 / 127 * drivepower):0)

float drivepower;
bool revmode;


//////////////////////////////////////////////////////////////////////////////////
//																																							//
//															Settings																				//
//																																							//
//////////////////////////////////////////////////////////////////////////////////

int deadband = 5;
float lowpower = 25;
float normpower = 50;
float highpower = 100;
