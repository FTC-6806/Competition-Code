#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)

#define SPI_MOSI 0
#define SPI_MISO 1
#define SPI_CLK 2
#define SPI_CS 3

byte pinvalues = 0b00000000;
byte pinmodes = 0b00000000;

#include "pincontrol.h"
#include "mcp3008.h"

task main()
{
	setPinMode(SPI_MISO, false);
	setPinMode(SPI_MOSI, true);
	setPinMode(SPI_CLK, true);
	setPinMode(SPI_CS, true);
  while (true) {
		displayTextLine(0, "0::::%i::::", readadc(0));
		displayTextLine(1, "1::::%i::::", readadc(1));
		displayTextLine(2, "2::::%i::::", readadc(2));
		displayTextLine(3, "3::::%i::::", readadc(3));
	}
	//setPinMode(7, false);
	//setPinMode(6, true);
	//while (true) {
	//	setPinValue(6, getPinValue(7));
	//}
}
