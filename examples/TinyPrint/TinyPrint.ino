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
    testMe.print(123);
    testMe.println(456);
    testMe.print(F("asdf!"));
    testMe.println(F("qwer?"));
    testMe.print("hjk");
    testMe.println("zui");
    
    delay(1000);
}

/*
If compiling this for an Arduino UNO, it will consume this much resources:
  Sketch uses 1246 bytes (3%) of program storage space. Maximum is 32256 bytes.
  Global variables use 27 bytes (1%) of dynamic memory, leaving 2021 bytes for local variables. Maximum is 2048 bytes.
*/
