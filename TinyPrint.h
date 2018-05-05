/*
https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Print.cpp
https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Print.h
*/

// TODO make a library out of this!

/***************************************************************************
  This is a library for the SH1106 I2C OLED display
  These displays use I2C to communicate, 2 pins are required to  interface

  Written by https://github.com/notisrac
  MIT license, all text above must be included in any redistribution
 ***************************************************************************/


#pragma once

#ifndef _TINYPRINT_H
#define _TINYPRINT_H

#include <Arduino.h>

class TinyPrint
{
public:
	TinyPrint();
	virtual byte write(uint8_t) = 0;
	byte write(const char *str) {
		if (str == NULL) return 0;
		return write((const uint8_t *)str, strlen(str));
	}
	virtual byte write(const uint8_t *buffer, size_t size);
	byte write(const char *buffer, size_t size) {
		return write((const uint8_t *)buffer, size);
	}

	void print(const __FlashStringHelper *);
	void print(const char[]);
	void print(char);
	void print(unsigned char, int = DEC);
	void print(int, int = DEC);
	void print(unsigned int, int = DEC);
	void print(long, int = DEC);
	void print(unsigned long, int = DEC);
	void print(double, int = 2);

	void println(const __FlashStringHelper *);
	void println(const char[]);
	void println(char);
	void println(unsigned char, int = DEC);
	void println(int, int = DEC);
	void println(unsigned int, int = DEC);
	void println(long, int = DEC);
	void println(unsigned long, int = DEC);
	void println(double, int = 2);
	void println(void);

private:
	void printNumber(unsigned long, uint8_t);
	void printFloat(double, uint8_t);
};

#endif // _TINYPRINT_H
