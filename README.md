# TinyPrint
Base class that provides print() and println().
This is a slimmed down version of the original Print.h Arduino library.
The intent is to have a smaller flash and memory footprint. To achieve this, the String and Printable were removed, along with the error methods. Also the different parts (flashstring, number, float, print lines) can be enabled/disabled individually with conditional compilation.

## Features
 - Adds `print()` and `println()` functionality to your class
 - Same code as Arduino's own Print
 - Small (memory: 14 - 22 bytes, flash: 378 - 572 bytes)
 - Individual fetures can be enabled/disabled using preprocessor directives


## Using
This is a base class, so you need to inherit it in your own class:
```c
#include <TinyPrint.h>

class testClass : public TinyPrint
{
public:
	testClass();

private:
	// Inherited via Print
	virtual byte write(uint8_t) override;
};

testClass::testClass()
{}

byte testClass::write(uint8_t)
{
	// do the actual write

	// return the number of characters written
	return size_t();
}
```
Inheriting from TinyPrint will give you print() and println() functions:
```c
#include "testClass.h"

testClass testMe;

void setup()
{
  testMe.print("asdf");
  testMe.println("qwer");
}
```

## Configuration
These preprocessor directives are used to modify the behavior and the feature set of the library.

Remember to use them, before including the header file:
```c
// BEFORE including your class!
#define TP_PRINTLINES 1
...

#include "testClass.h"
...
```

### TP_PRINTLINES
Enables or disables the support for `println()`. You can still do print lines, but you will need to manually add a '\n' or a "\r\n" to the end of your string.
```c
  testMe.print('a');
  testMe.println('b'); // this will throw an error if TP_PRINTLINES is 0
```

### TP_FLASHSTRINGHELPER
Enables or disables the support for the FlashStringHelper - this is the class that enables you to store string literals in the flash memory. (keywords: PROGMEM, PGM, F())
```c
  testMe.print(F("asdf!")); // if TP_FLASHSTRINGHELPER is 0 then it should give you a warning: invalid conversion from 'const __FlashStringHelper*' to 'char' [-fpermissive]
```

### TP_NUMBERS
Enables or disables the support for numbers. You can pass in numbers as arguments, but it will try to print out a single character. So if you want to print out the value of the number, enable this.
```c
  testMe.print(64); // with TP_NUMBERS enabled, this prints '64', with TP_NUMBERS disabled this prints 'A'
```

### TP_FLOAT
Enables or disables the support for floating point numbers.
_Note: `TP_NUMBERS` must be enabled as well for this to work!_
```c
  testMe.print(12.34);
```

### TP_WINDOWSLINEENDS
Switches between having a `\n` and a `\r\n` at the end of the printed text when using `println(...)`
```c
  testMe.print("asdf"); // outputs either "asdf\n" or "asdf\r\n"
```


## Measurements
Here are a few measurements so we can compare TinyPrint with Arduino's Print.
Code used for measurements can be found in the Examples folder, with the name "*M" (ArduinoPrintM, TinyPrintM).

### Setup
 - Arduino UNO
 - Arduino IDE 1.8.5

### Test code
```c
    testMe.print('a');
    testMe.println('b');
    testMe.print(1234);
    testMe.println(4567);
    //testMe.print(12.34);
    //testMe.println(45.67);
    testMe.print(F("asdf!"));
    testMe.println(F("qwer?"));
    testMe.print("hjk");
    testMe.println("zui");
```
_The full test code can be found in the Examples folder._

### Base
| File              | Mode | Memory(b) | Flash(b)   | Comment                                                                                      |
| ----------------- |:----:| ---------:| ----------:| -------------------------------------------------------------------------------------------- |
| BareMinimum.ino   |      | 9         | 444        | This is the "BareMinimum" example sketch                                                     |
| ArduinoPrintM.ino |      | 28(37)    | 806(1250)  | This is a test class implementing Print, with the test code                                  |
| ArduinoPrintM.ino | FP   | 28(37)    | 2238(2682) | Test class implementing Print, with the test code, with the floating point operation enabled |
_All values have the BareMinimum subtracted from them. Original values are in parenthesis._

### TinyPrint
| Mode                                      | Memory(b) | Flash(b)  |
| ----------------------------------------- | ---------:| ---------:|
| Text only                                 | 14(23)    | 378(822)  |
| Text + Flash string helpers               | 14(23)    | 432(876)  |
| Text + Flash string helpers + print lines | 18(27)    | 530(974)  |
| Text + numbers                            | 14(23)    | 402(846)  |
| Text + numbers + print lines              | 18(27)    | 490(934)  |
| Text + numbers + float                    | 14(23)    | 396(840)  |
| Text + numbers + float + print lines      | 18(27)    | 492(936)  |
| Everything enabled                        | 22(31)    | 572(1016) |
_All values have the BareMinimum subtracted from them. Original values are in parenthesis._

_Note: your milage may vary! (Ex.: Newer versions of the IDE have better optimization features. Also if you already have floating point operations in your code, enabling it here will not have as much effect. Etc.)_


## Find the original Print library files here:
 * https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Print.cpp
 * https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Print.h


[![Analytics](https://ga-beacon.appspot.com/UA-122950438-1/TinyPrint)](https://github.com/igrigorik/ga-beacon)
