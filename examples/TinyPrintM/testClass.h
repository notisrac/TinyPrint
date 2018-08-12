#include <TinyPrint.h>

class testClass : public TinyPrint
{
public:
	testClass();
  void doNothing();

private:

	// Inherited via Print
	virtual byte write(uint8_t) override;
};

testClass::testClass()
{
}

byte testClass::write(uint8_t)
{
	// do the actual write

	// return the number of characters written
	return size_t();
}

void testClass::doNothing()
{
  // do nothing :)
}
