#include <Arduino.h>

class testClass : public Print
{
public:
	testClass();
  void doNothing();

private:

	// Inherited via Print
	virtual size_t write(uint8_t) override;
};

testClass::testClass()
{
}

size_t testClass::write(uint8_t)
{
	// do the actual write

	// return the number of characters written
	return size_t();
}

void testClass::doNothing()
{
  // do nothing :)
}
