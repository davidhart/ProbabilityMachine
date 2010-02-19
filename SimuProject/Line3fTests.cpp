#include "Line3fTests.h"
#include "Line3f.h"

#include <cmath>

using std::endl;

const float EPSILON = 0.000001f;

void Line3fTests::DoAllTests(ostream& os)
{
	os<<"Line3f Tests Start"<<endl;
	TestConstructor(os);
	TestGetPoint(os);
	TestGetDirection(os);
	TestSetPoint(os);
	TestSetDirection(os);
	TestPerpendicularDistanceToPoint(os);
	os<<"Line3f Tests Complete"<<endl;
}

void Line3fTests::TestConstructor(ostream& os)
{
	Line3f l(Vector3f(1,2,3), Vector3f(4, 5, 6));
	
	if (l.Point().X() < 1 - EPSILON || l.Point().X() > 1 + EPSILON) { os<<"TestConstructor Failed - point.X not set to 1"<<endl; }
	if (l.Point().Y() < 2 - EPSILON || l.Point().Y() > 2 + EPSILON) { os<<"TestConstructor Failed - point.Y not set to 2"<<endl; }
	if (l.Point().Z() < 3 - EPSILON || l.Point().Z() > 3 + EPSILON) { os<<"TestConstructor Failed - point.Z not set to 3"<<endl; }
	if (l.Direction().X() < 4 - EPSILON || l.Direction().X() > 4 + EPSILON) { os<<"TestConstructor Failed - direction.X not set to 4"<<endl; }
	if (l.Direction().Y() < 5 - EPSILON || l.Direction().Y() > 5 + EPSILON) { os<<"TestConstructor Failed - direction.Y not set to 5"<<endl; }
	if (l.Direction().Z() < 6 - EPSILON || l.Direction().Z() > 6 + EPSILON) { os<<"TestConstructor Failed - direction.Z not set to 6"<<endl; }
}

void Line3fTests::TestGetPoint(ostream& os)
{
	Line3f l(Vector3f(1,2,3), Vector3f(1, 1, 1));
	
	if (l.Point().X() < 1 - EPSILON || l.Point().X() > 1 + EPSILON) { os<<"TestGetPoint Failed - point.X not equal to 1"<<endl; }
	if (l.Point().Y() < 2 - EPSILON || l.Point().Y() > 2 + EPSILON) { os<<"TestGetPoint Failed - point.Y not equal to 2"<<endl; }
	if (l.Point().Z() < 3 - EPSILON || l.Point().Z() > 3 + EPSILON) { os<<"TestGetPoint Failed - point.Z not equal to 3"<<endl; }
}

void Line3fTests::TestGetDirection(ostream& os)
{
	Line3f l(Vector3f(1,1,1), Vector3f(1, 2, 3));
	
	if (l.Direction().X() < 1 - EPSILON || l.Direction().X() > 1 + EPSILON) { os<<"TestGetDirection Failed - direction.X not equal to 1"<<endl; }
	if (l.Direction().Y() < 2 - EPSILON || l.Direction().Y() > 2 + EPSILON) { os<<"TestGetDirection Failed - direction.Y not equal to 2"<<endl; }
	if (l.Direction().Z() < 3 - EPSILON || l.Direction().Z() > 3 + EPSILON) { os<<"TestGetDirection Failed - direction.Z not equal to 3"<<endl; }
}

void Line3fTests::TestSetPoint(ostream& os)
{
	Line3f l(Vector3f(1,1,1), Vector3f(1, 1, 1));
	l.SetPoint(Vector3f(1,2,3));

	if (l.Point().X() < 1 - EPSILON || l.Point().X() > 1 + EPSILON) { os<<"TestSetPoint Failed - point.X not equal to 1"<<endl; }
	if (l.Point().Y() < 2 - EPSILON || l.Point().Y() > 2 + EPSILON) { os<<"TestSetPoint Failed - point.Y not equal to 2"<<endl; }
	if (l.Point().Z() < 3 - EPSILON || l.Point().Z() > 3 + EPSILON) { os<<"TestSetPoint Failed - point.Z not equal to 3"<<endl; }
}

void Line3fTests::TestSetDirection(ostream& os)
{
	Line3f l(Vector3f(1,1,1), Vector3f(1, 1, 1));
	l.SetDirection(Vector3f(1,2,3));
	
	if (l.Direction().X() < 1 - EPSILON || l.Direction().X() > 1 + EPSILON) { os<<"TestSetDirection Failed - direction.X not equal to 1"<<endl; }
	if (l.Direction().Y() < 2 - EPSILON || l.Direction().Y() > 2 + EPSILON) { os<<"TestSetDirection Failed - direction.Y not equal to 2"<<endl; }
	if (l.Direction().Z() < 3 - EPSILON || l.Direction().Z() > 3 + EPSILON) { os<<"TestSetDirection Failed - direction.Z not equal to 3"<<endl; }
}

void Line3fTests::TestPerpendicularDistanceToPoint(ostream& os)
{
	Line3f l(Vector3f(0,-15,0), Vector3f(0,0,1));
	float f = l.PerpendicularDistanceToPoint(Vector3f(10,-15,0));

	if (f < 10 - EPSILON || f > 10 + EPSILON) 
		{ os<<"TestPerpendicularDistanceToPoint Failed - perpendicular distance not equal to 10"<<endl; }

	l = Line3f(Vector3f(0,0,0), Vector3f(1,0,1));
	f = l.PerpendicularDistanceToPoint(Vector3f(1,0,0));

	if (f < sqrt(0.5f) - EPSILON || f > sqrt(0.5f) + EPSILON)
		{ os<<"TestPerpendicularDistanceToPoint Failed - perpendicular distance not equal to sqrt(1/2)"<<endl; }
}
