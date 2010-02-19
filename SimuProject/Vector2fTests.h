#ifndef _VECTOR2FTESTS_H
#define _VECTOR2FTESTS_H

#include <ostream>

using std::ostream;

class Vector2fTests
{
public:
	static void DoAllTests(ostream& os);
	static void TestEmptyConstructor(ostream& os);
	static void TestTwoFloatConstructor(ostream& os);
	static void TestX(ostream& os);
	static void TestY(ostream& os);
	static void TestLength(ostream& os);
	static void TestSetX(ostream& os);
	static void TestSetY(ostream& os);
	static void TestUnit(ostream& os);
	static void TestAdd(ostream& os);
	static void TestSubtract(ostream& os);
	static void TestMultiply(ostream& os);
	static void TestDot(ostream& os);
};

#endif
