#ifndef _LINE2FTESTS_H
#define _LINE2FTESTS_H

#include <ostream>

using std::ostream;

class Line2fTests
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
