#include "Line2fTests.h"
#include "Line2f.h"

#include <cmath>

using std::endl;

const float EPSILON = 0.000001f;

void Line2fTests::DoAllTests(ostream& os)
{
	os<<"Line2f Tests Start"<<endl;
	TestConstructor(os);
	TestGetPoint(os);
	TestGetDirection(os);
	TestSetPoint(os);
	TestSetDirection(os);
	TestPerpendicularDistanceToPoint(os);
	os<<"Line2f Tests Complete"<<endl;
}

void Line2fTests::TestConstructor(ostream& os)
{
	Line2f l(Vector2f(1,2), Vector2f(3, 4));
	
	if (l.Point().X() < 1 - EPSILON || l.Point().X() > 1 + EPSILON) { os<<"TestConstructor Failed - point.X not set to 1"<<endl; }
	if (l.Point().Y() < 2 - EPSILON || l.Point().Y() > 2 + EPSILON) { os<<"TestConstructor Failed - point.Y not set to 2"<<endl; }
	if (l.Direction().X() < 3 - EPSILON || l.Direction().X() > 3 + EPSILON) { os<<"TestConstructor Failed - direction.X not set to 3"<<endl; }
	if (l.Direction().Y() < 4 - EPSILON || l.Direction().Y() > 4 + EPSILON) { os<<"TestConstructor Failed - direction.Y not set to 4"<<endl; }
}

void Line2fTests::TestGetPoint(ostream& os)
{
	Line2f l(Vector2f(1,1), Vector2f(1,1));
	if (l.Point().X() < 1 - EPSILON || l.Point().X() > 1 + EPSILON) { os<<"TestGetPoint Failed - point.X not equal to 1"<<endl; }
	if (l.Point().Y() < 1 - EPSILON || l.Point().Y() > 1 + EPSILON) { os<<"TestGetPoint Failed - point.Y not equal to 1"<<endl; }
}

void Line2fTests::TestGetDirection(ostream& os)
{	
	Line2f l(Vector2f(1,1), Vector2f(1,1));
	if (l.Direction().X() < 1 - EPSILON || l.Direction().X() > 1 + EPSILON) { os<<"TestGetDirection Failed - direction.X not equal to 1"<<endl; }
	if (l.Direction().Y() < 1 - EPSILON || l.Direction().Y() > 1 + EPSILON) { os<<"TestGetDirection Failed - direction.Y not equal to 1"<<endl; }
}

void Line2fTests::TestSetPoint(ostream& os)
{
	Line2f l(Vector2f(1,1), Vector2f(1,1));
	l.SetPoint(Vector2f(2,2));	
	if (l.Point().X() < 2 - EPSILON || l.Point().X() > 2 + EPSILON) { os<<"TestSetPoint Failed - point.X not equal to 2"<<endl; }
	if (l.Point().Y() < 2 - EPSILON || l.Point().Y() > 2 + EPSILON) { os<<"TestSetPoint Failed - point.Y not equal to 2"<<endl; }
}

void Line2fTests::TestSetDirection(ostream& os)
{
	Line2f l(Vector2f(1,1), Vector2f(1,1));
	l.SetDirection(Vector2f(2,2));	
	if (l.Direction().X() < 2 - EPSILON || l.Direction().X() > 2 + EPSILON) { os<<"TestSetDirection Failed - point.X not equal to 2"<<endl; }
	if (l.Direction().Y() < 2 - EPSILON || l.Direction().Y() > 2 + EPSILON) { os<<"TestSetDirection Failed - point.Y not equal to 2"<<endl; }
}

void Line2fTests::TestPerpendicularDistanceToPoint(ostream& os)
{
	Line2f l(Vector2f(-10,0), Vector2f(0,1));
	float f = l.PerpendicularDistanceToPoint(Vector2f(20,-15));

	if (f < 30 - EPSILON || f > 30 + EPSILON) 
		{ os<<"TestPerpendicularDistanceToPoint Failed - perpendicular distance not equal to 30"<<endl; }

	l = Line2f(Vector2f(0,0), Vector2f(1,1));
	f = l.PerpendicularDistanceToPoint(Vector2f(1,0));

	if (f < sqrt(0.5)-EPSILON || f > sqrt(0.5)+EPSILON)
		{ os<<"TestPerpendicularDistanceToPoint Failed - perpendicular distance not equal to sqrt(1/2)"<<endl; }
}
