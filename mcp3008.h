#define adcclockoutbit() setPinValue(SPI_MOSI, (commandout & 0x80)); \
	commandout <<= 1; \
	setPinValue(SPI_CLK, true); \
	setPinValue(SPI_CLK, false);

#define adcgrabbit() setPinValue(SPI_CLK, true); \
	setPinValue(SPI_CLK, false); \
	adcout <<= 1; \
	if (getPinValue(SPI_MISO)) { \
		adcout |= 0x1; \
	}


int readmcp3008adc(byte adcnum)
{
	setPinValue(SPI_CS, true);

	setPinValue(SPI_CLK, false);
	setPinValue(SPI_CS, false);

	byte commandout = adcnum;
	commandout |= 0x18;
	commandout <<= 3;

	adcclockoutbit();
	adcclockoutbit();
	adcclockoutbit();
	adcclockoutbit();
	adcclockoutbit();

	int adcout = 0;
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();
	adcgrabbit();

	setPinValue(SPI_CS, true);

	adcout >>= 1;
	return adcout;
}
