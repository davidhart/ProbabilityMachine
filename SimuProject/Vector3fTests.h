#ifndef _VECTOR3FTESTS_H
#define _VECTOR3FTESTS_H

#include <iostream>

using std::ostream;

class Vector3fTests
{
public:
	static void DoAllTests(ostream& os);
	static void TestEmptyConstructor(ostream& os);
	static void TestThreeFloatsConstructor(ostream& os);
	static void TestX(ostream& os);
	static void TestY(ostream& os);
	static void TestZ(ostream& os);
	static void TestLength(ostream& os);
	static void TestSetX(ostream& os);
	static void TestSetY(ostream& os);
	static void TestSetZ(ostream& os);
	static void TestUnit(ostream& os);
	static void TestAdd(ostream& os);
	static void TestSubtract(ostream& os);
	static void TestMultiply(ostream& os);
	static void TestCross(ostream& os);
	static void TestDot(ostream& os);
};

#endif
