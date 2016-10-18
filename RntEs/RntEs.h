/*
  RntEs.h - Library for read data from RNT.ES Seonsors
  Created by Piotr Stania <piotrekstania@gmail.com>, 10.2016
  Released into the public domain.
*/
#ifndef RntEs_h
#define RntEs_h

#include "Arduino.h"

#define BUF_SIZE		16


class RntEs {

public:
	RntEs(int pin);
	int getData(unsigned long timeout);

	unsigned long getSerial();

	float getTemperature();
	float getPressure();
	float getRH();
	float getAH();
	float getDP();

private:
	int _pin;
	uint8_t bit;
	uint8_t byte;
	uint8_t buf[BUF_SIZE];

	uint32_t serial;
	float t;
	float rh;
	float ah;
	float p;
	float dp;

	static uint8_t crc8(uint8_t *buffer, uint8_t size);
};

#endif //RntEs_h
