#define TP_PRINTLINES 1
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
    testMe.println('b');
    
    delay(1000);
}