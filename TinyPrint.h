/***************************************************************************
  This is a slimmed down version of the original Print.h Arduino library.
  The intent is to have a smaller prog mem a ram footprint. To achieve this
  String and Printable were removed, along with the error methods.

  Written by https://github.com/notisrac, 2018
  MIT license, all text above must be included in any redistribution
 ***************************************************************************/

/*
	Originals:
	https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Print.cpp
	https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Print.h
*/


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
