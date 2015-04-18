#include "FOXFIRE_Si70xx.h"

FOXFIRE_Si70xx::FOXFIRE_Si70xx()
{
	_addr = ID_SI7020;
}

boolean FOXFIRE_Si70xx::begin(void)
{
	Wire.begin();

	return true;
}

float FOXFIRE_Si70xx::readTemperature(void)
{
	float temp;
	int32_t rawTemp;
	write8(CMD_MEASURE_TEMPERATURE_HOLD);
	
	rawTemp = read16(CMD_MEASURE_TEMPERATURE_HOLD);
	//temp = (rawTemp*175.72/65536) - 46.85; // Original
	temp = (rawTemp*175.72/65536) - 50.85; // Marcus' edit based on ODROID forum post, see notes directory in repo

	return temp;
}

float FOXFIRE_Si70xx::readHumidity(void)
{
	float humi;
	int32_t rawHumi;
	write8(CMD_MEASURE_HUMIDITY_HOLD);
	delay(10);
	rawHumi = read16(CMD_MEASURE_HUMIDITY_HOLD);
	delay(10);
	humi = (rawHumi*125.0/65536) - 6;

	return humi;
}

uint16_t FOXFIRE_Si70xx::read16(uint8_t addr)
{
	uint16_t ret;
	Wire.beginTransmission(_addr);
	Wire.write(addr);
	Wire.endTransmission();

	Wire.beginTransmission(_addr);
	Wire.requestFrom(_addr, 2);
	ret = Wire.read();
	ret <<= 8;
	ret |= Wire.read();
	Wire.endTransmission();

	return ret;
}

void FOXFIRE_Si70xx::write8(uint8_t addr)
{
	Wire.beginTransmission(_addr);
	Wire.write(addr);
	Wire.endTransmission();
}
