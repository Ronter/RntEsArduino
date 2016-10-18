#include "Arduino.h"
#include "RntEs.h"

RntEs::RntEs(int pin) {
	pinMode(pin, INPUT_PULLUP);
	_pin = pin;
}

unsigned long RntEs::getSerial(){return serial;}
float RntEs::getTemperature(){return t;}
float RntEs::getPressure(){return p;}
float RntEs::getRH(){return rh;}
float RntEs::getAH(){return ah;}
float RntEs::getDP(){return dp;}

int RntEs::getData(unsigned long timeout) {
	unsigned long time;
	uint16_t temp;
	bool edge = false;
	timeout += millis();
	while(millis() < timeout) {
		if(digitalRead(_pin)) {
			if(edge) {
				time = micros() - time;
				edge = false;
				if((time > 200) && (time < 400)) {
					buf[byte] &= ~(1<<bit++);
				} else if((time > 500) && (time < 700)) {
					buf[byte] |= (1<<bit++);
				} else if((time > 1900) && (time < 2200)) {
					bit = 0;
					byte = 0;
				} else if((time > 2900) && (time < 3200)) {
					if(!bit && (buf[byte-1] == crc8(buf, byte-1))) {
						serial = (uint16_t)(buf[0]<<8 | buf[1]);
						serial <<= 16;
						serial |= (uint16_t)(buf[2]<<8 | buf[3]);
						t  = ((float)(buf[4]<<8 | buf[5]))/10;
						rh = ((float)(buf[6]<<8 | buf[7]))/10;
						p  = ((float)(buf[8]<<8 | buf[9]))/10;
						ah = ((float)(buf[10]<<8 | buf[11]))/10;
						dp = ((float)(buf[12]<<8 | buf[13]))/10;
						return 1;
					}
				}
				if(bit == 8) {
					bit = 0;
					byte++;
					if(byte == BUF_SIZE) byte = 0;
				}
			}
		} else {
			if(!edge) {
				time = micros();
				edge = true;
			}
		}
	}
	return 0;
}


uint8_t RntEs::crc8(uint8_t *buffer, uint8_t size) {
	uint8_t crc = 0;
	uint8_t loop_count;
	uint8_t bit_counter;
	uint8_t data;
	uint8_t feedback_bit;
	for(loop_count = 0; loop_count != size; loop_count++) {
		data = buffer[loop_count];
		bit_counter = 8;
		do {
			feedback_bit = (crc^data) & 0x01;
			if(feedback_bit == 0x01) crc ^= 0x18;		//0X18 = X^8+X^5+X^4+X^0
			crc = (crc>>1) & 0x7F;
			if(feedback_bit == 0x01) crc |= 0x80;
			data >>= 1;
			bit_counter--;
		} while (bit_counter > 0);
	}
	return crc;
}
