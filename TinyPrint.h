/***************************************************************************
  This is a slimmed down version of the original Print.h Arduino library.
  The intent is to have a smaller prog mem a ram footprint. To achieve this
  String and Printable were removed, along with the error methods. Also the
  different parts (flashstring, number, float, print lines) can be 
  enabled/disabled individually with conditional compilation.

  The implementation needed to go here instead of a .cpp file, because that
   way the configuration #defines would not work!
  See: https://github.com/arduino/Arduino/pull/1808#issuecomment-370210551

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

// default values
#ifndef TP_FLASHSTRINGHELPER
#define TP_FLASHSTRINGHELPER 0
#endif

#ifndef TP_NUMBERS
#define TP_NUMBERS 0
#endif

#ifndef TP_FLOAT
#define TP_FLOAT 0
#endif

#ifndef TP_PRINTLINES
#define TP_PRINTLINES 0
#endif

#ifndef TP_WINDOWSLINEENDS
#define TP_WINDOWSLINEENDS 0
#endif

// error check
#if TP_FLOAT && !TP_NUMBERS
#error "TP_NUMBERS must be set to 1, when using TP_FLOAT!"
#endif // TP_FLOAT && !TP_NUMBERS


#include <Arduino.h>

class TinyPrint
{
public:
	TinyPrint()
	{
	}

	virtual byte write(uint8_t) = 0;

	byte write(const char *str) {
		if (str == NULL) return 0;
		return write((const uint8_t *)str, strlen(str));
	}

	byte write(const char *buffer, size_t size) {
		return write((const uint8_t *)buffer, size);
	}

	/* default implementation: may be overridden */
	virtual byte write(const uint8_t *buffer, size_t size)
	{
		size_t n = 0;
		while (size--) {
			if (write(*buffer++)) {
				n++;
			}
			else {
				break;
			}
		}

		return n;
	}


	void print(const char str[])
	{
		write(str);
	}

	void print(char c)
	{
		write(c);
	}

#if TP_PRINTLINES
	void println(void)
	{
#if TP_WINDOWSLINEENDS
		write("\r\n"); // nope, this cannot be further optimized with the current setup
#else
		write('\n');
#endif // TP_WINDOWSLINEENDS
	}

	void println(const char c[])
	{
		print(c);
		println();
	}

	void println(char c)
	{
		print(c);
		println();
	}
#endif // TP_PRINTLINES


#if TP_FLASHSTRINGHELPER
	void print(const __FlashStringHelper *ifsh)
	{
		PGM_P p = reinterpret_cast<PGM_P>(ifsh);
		while (1) {
			unsigned char c = pgm_read_byte(p++);
			if (c == 0) {
				break;
			}
			if (write(c)) {
				// do nothing - the counter increment was here
			}
			else {
				break;
			}
		}
	}

#if TP_PRINTLINES
	void println(const __FlashStringHelper *ifsh)
	{
		print(ifsh);
		println();
	}
#endif // TP_PRINTLINES
#endif // TP_FLASHSTRINGHELPER

#if TP_NUMBERS
	void print(unsigned char b, int base)
	{
		print((unsigned long)b, base);
	}

	void print(int n, int base)
	{
		print((long)n, base);
	}

	void print(unsigned int n, int base)
	{
		print((unsigned long)n, base);
	}

	void print(long n, int base)
	{
		if (base == 0) {
			write(n);
		}
		else if (base == 10) {
			if (n < 0) {
				print('-');
				n = -n;
				printNumber(n, 10);
			}
			return printNumber(n, 10);
		}
		else {
			return printNumber(n, base);
		}
	}

	void print(unsigned long n, int base)
	{
		if (base == 0) {
			write(n);
		}
		else {
			printNumber(n, base);
		}
	}

#if TP_PRINTLINES
	void println(unsigned char b, int base)
	{
		print(b, base);
		println();
	}

	void println(int num, int base)
	{
		print(num, base);
		println();
	}

	void println(unsigned int num, int base)
	{
		print(num, base);
		println();
	}

	void println(long num, int base)
	{
		print(num, base);
		println();
	}

	void println(unsigned long num, int base)
	{
		print(num, base);
		println();
	}
#endif // TP_PRINTLINES
#endif // TP_NUMBERS


#if TP_FLOAT
	void print(double n, int digits)
	{
		printFloat(n, digits);
	}

#if TP_PRINTLINES
	void println(double num, int digits)
	{
		print(num, digits);
		println();
	}
#endif // TP_PRINTLINES
#endif // TP_FLOAT

	// Private Methods /////////////////////////////////////////////////////////////
private:
#if TP_NUMBERS
	void printNumber(unsigned long n, uint8_t base)
	{
		char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
		char *str = &buf[sizeof(buf) - 1];

		*str = '\0';

		// prevent crash if called with base == 1
		if (base < 2)
		{
			base = 10;
		}

		do {
			char c = n % base;
			n /= base;

			*--str = c < 10 ? c + '0' : c + 'A' - 10;
		} while (n);

		write(str);
	}
#endif // TP_NUMBERS

#if TP_FLOAT
	void printFloat(double number, uint8_t digits)
	{

		if (isnan(number))
		{
			return print('N'/*F("nan")*/);
		}
		if (isinf(number))
		{
			return print('I'/*F("inf")*/);
		}
		if (number > 4294967040.0)
		{
			return print('O'/*F("ovf")*/);  // constant determined empirically
		}
		if (number < -4294967040.0)
		{
			return print('O'/*F("ovf")*/);  // constant determined empirically
		}

		// Handle negative numbers
		if (number < 0.0)
		{
			print('-');
			number = -number;
		}

		// Round correctly so that print(1.999, 2) prints as "2.00"
		double rounding = 0.5;
		for (uint8_t i = 0; i < digits; ++i)
		{
			rounding /= 10.0;
		}

		number += rounding;

		// Extract the integer part of the number and print it
		unsigned long int_part = (unsigned long)number;
		double remainder = number - (double)int_part;
		print(int_part);

		// Print the decimal point, but only if there are digits beyond
		if (digits > 0) {
			print('.');
		}

		// Extract digits from the remainder one at a time
		while (digits-- > 0)
		{
			remainder *= 10.0;
			unsigned int toPrint = (unsigned int)(remainder);
			print(toPrint);
			remainder -= toPrint;
		}
	}
#endif // TP_FLOAT
};

#endif // _TINYPRINT_H
