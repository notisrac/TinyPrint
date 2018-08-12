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
    testMe.println('b');
    testMe.print(1234);
    testMe.println(4567);
    testMe.print(12.34);
    testMe.println(45.67);
    testMe.print(F("asdf!"));
    testMe.println(F("qwer?"));
    testMe.print("hjk");
    testMe.println("zui");
    
    delay(1000);
}

/*
If compiling this for an Arduino UNO, with Arduino IDE 1.8.5, it will consume this much resources:
  Sketch uses 1250 bytes (3%) of program storage space. Maximum is 32256 bytes.
  Global variables use 37 bytes (1%) of dynamic memory, leaving 2011 bytes for local variables. Maximum is 2048 bytes.
*/
