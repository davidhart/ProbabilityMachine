#ifndef _LINE3FTESTS_H
#define _LINE3FTESTS_H

#include <ostream>

using std::ostream;

class Line3fTests
{
public:
	static void DoAllTests(ostream& os);
	static void TestConstructor(ostream& os);
	static void TestGetPoint(ostream& os);
	static void TestGetDirection(ostream& os);
	static void TestSetPoint(ostream& os);
	static void TestSetDirection(ostream& os);
	static void TestPerpendicularDistanceToPoint(ostream& os);
};

#endif
