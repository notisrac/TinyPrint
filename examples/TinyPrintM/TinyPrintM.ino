#define TP_PRINTLINES 0
#define TP_FLASHSTRINGHELPER 0
#define TP_NUMBERS 0
#define TP_FLOAT 0
#define TP_WINDOWSLINEENDS 0

#include "testClass.h"

testClass testMe;

void setup()
{
    // do nothing
}

void loop()
{
    // do nothing
    testMe.doNothing();

    // print something

    testMe.print('a');
#if TP_PRINTLINES
    testMe.println('b');
#endif

#if TP_NUMBERS
    testMe.print(1234);
#if TP_PRINTLINES
    testMe.println(4567);
#endif
#endif

#if TP_FLOAT
    testMe.print(12.34);
#if TP_PRINTLINES
    testMe.println(45.67);
#endif
#endif


#if TP_FLASHSTRINGHELPER
    testMe.print(F("asdf!"));
#if TP_PRINTLINES
    testMe.println(F("qwer?"));
#endif
#endif
    
    testMe.print("hjk");
#if TP_PRINTLINES
    testMe.println("zui");
#endif
    
    delay(1000);
}

/*
If compiling this for an Arduino UNO, with Arduino IDE 1.8.5, it will consume this much resources:
Text only:
  Sketch uses 822 bytes (2%) of program storage space. Maximum is 32256 bytes.
  Global variables use 23 bytes (1%) of dynamic memory, leaving 2025 bytes for local variables. Maximum is 2048 bytes.

Text + flash string helpers
  Sketch uses 876 bytes (2%) of program storage space. Maximum is 32256 bytes.
  Global variables use 23 bytes (1%) of dynamic memory, leaving 2025 bytes for local variables. Maximum is 2048 bytes.

Text + flash string helpers + print lines
  Sketch uses 974 bytes (3%) of program storage space. Maximum is 32256 bytes.
  Global variables use 27 bytes (1%) of dynamic memory, leaving 2021 bytes for local variables. Maximum is 2048 bytes.

Text + numbers
  Sketch uses 846 bytes (2%) of program storage space. Maximum is 32256 bytes.
  Global variables use 23 bytes (1%) of dynamic memory, leaving 2025 bytes for local variables. Maximum is 2048 bytes.

Text + numbers + print lines
  Sketch uses 934 bytes (2%) of program storage space. Maximum is 32256 bytes.
  Global variables use 27 bytes (1%) of dynamic memory, leaving 2021 bytes for local variables. Maximum is 2048 bytes.

Text + numbers + float
  Sketch uses 840 bytes (2%) of program storage space. Maximum is 32256 bytes.
  Global variables use 23 bytes (1%) of dynamic memory, leaving 2025 bytes for local variables. Maximum is 2048 bytes.

Text + numbers + float + print lines
  Sketch uses 936 bytes (2%) of program storage space. Maximum is 32256 bytes.
  Global variables use 27 bytes (1%) of dynamic memory, leaving 2021 bytes for local variables. Maximum is 2048 bytes.

Everything:
  Sketch uses 1016 bytes (3%) of program storage space. Maximum is 32256 bytes.
  Global variables use 31 bytes (1%) of dynamic memory, leaving 2017 bytes for local variables. Maximum is 2048 bytes.
*/
