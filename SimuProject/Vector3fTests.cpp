#include "Vector3fTests.h"
#include "Vector3f.h"

using std::endl;

const float EPSILON = 0.000001f;

void Vector3fTests::DoAllTests(ostream& os)
{
	os<<"Vector3f Tests Start"<<endl;
	TestEmptyConstructor(os);
	TestThreeFloatsConstructor(os);
	TestX(os);
	TestY(os);
	TestZ(os);
	TestLength(os);
	TestSetX(os);
	TestSetY(os);
	TestSetZ(os);
	TestUnit(os);
	TestAdd(os);
	TestSubtract(os);
	TestMultiply(os);
	TestCross(os);
	TestDot(os);
	os<<"Vector3f Tests Complete"<<endl;
}

void Vector3fTests::TestEmptyConstructor(ostream& os)
{
	Vector3f v;
	if(v.X()>EPSILON||v.X()<-EPSILON){os<<"TestEmptyConstructor Failed - x value not set to zero"<<endl;}
	if(v.Y()>EPSILON||v.Y()<-EPSILON){os<<"TestEmptyConstructor Failed - y value not set to zero"<<endl;}
	if(v.Z()>EPSILON||v.Z()<-EPSILON){os<<"TestEmptyConstructor Failed - z value not set to zero"<<endl;}
}

void Vector3fTests::TestThreeFloatsConstructor(ostream& os)
{
	Vector3f v(1, 2, 3);
	if(v.X()> 1 + EPSILON||v.X()< 1 - EPSILON){os<<"TestTwoFloatConstructor Failed - x value not set or retreived correctly"<<endl;}
	if(v.Y()> 2 + EPSILON||v.Y()< 2 - EPSILON){os<<"TestTwoFloatConstructor Failed - y value not set or retreived correctly"<<endl;}
	if(v.Z()> 3 + EPSILON||v.Z()< 3 - EPSILON){os<<"TestTwoFloatConstructor Failed - y value not set or retreived correctly"<<endl;}
}

void Vector3fTests::TestX(ostream& os)
{
	Vector3f v(1, 0, 0);
	if(v.X()> 1 + EPSILON||v.X()< 1 - EPSILON){os<<"TestX Failed - x value not set or retreived correctly"<<endl;}
}

void Vector3fTests::TestY(ostream& os)
{
	Vector3f v(0, 1, 0);
	if(v.Y()> 1 + EPSILON||v.Y()< 1 - EPSILON){os<<"TestY Failed - y value not set or retreived correctly"<<endl;}
}

void Vector3fTests::TestZ(ostream& os)
{
	Vector3f v(0, 0, 1);
	if(v.Z()> 1 + EPSILON||v.Z()< 1 - EPSILON){os<<"TestZ Failed - z value not set or retreived correctly"<<endl;}
}

void Vector3fTests::TestLength(ostream& os)
{
	Vector3f v(3, 4, 5);
	if(v.Length() > 7.0710678f + EPSILON||v.Length()< 7.0710678f - EPSILON){os<<"TestLength Failed - length value not calculated correctly"<<endl;}
}

void Vector3fTests::TestSetX(ostream& os)
{
	Vector3f v;
	v.SetX(1);
	if(v.X()> 1 + EPSILON||v.X()< 1 - EPSILON){os<<"TestSetX Failed - x value not set or retreived correctly"<<endl;}
}

void Vector3fTests::TestSetY(ostream& os)
{	
	Vector3f v;
	v.SetY(1);
	if(v.Y()> 1 + EPSILON||v.Y()< 1 - EPSILON){os<<"TestSetY Failed - y value not set or retreived correctly"<<endl;}
}

void Vector3fTests::TestSetZ(ostream& os)
{
	Vector3f v;
	v.SetZ(1);
	if(v.Z()> 1 + EPSILON||v.Z()< 1 - EPSILON){os<<"TestSetZ Failed - z value not set or retreived correctly"<<endl;}
}

void Vector3fTests::TestUnit(ostream& os)
{
	Vector3f v(3, 4, 5);
	v.Unit();
	
	if(v.X() > 3.0/7.0710678f + EPSILON||v.X() < 3.0/7.0710678f - EPSILON){os<<"TestUnit Failed - x value not calculated or retreived correctly"<<endl;}
	if(v.Y() > 4.0/7.0710678f + EPSILON||v.Y() < 4.0/7.0710678f - EPSILON){os<<"TestUnit Failed - y value not calculated or retreived correctly"<<endl;}
	if(v.Z() > 5.0/7.0710678f + EPSILON||v.Z() < 5.0/7.0710678f - EPSILON){os<<"TestUnit Failed - z value not calculated or retreived correctly"<<endl;}
}

void Vector3fTests::TestAdd(ostream& os)
{
	
	Vector3f v1(1,2,10);
	Vector3f v2(3,4,999);
	Vector3f v3 = v1.Add(v2);
	if(v3.X() > 4.0 + EPSILON||v3.X() < 4.0 - EPSILON){os<<"TestAdd Failed - x value not calculated or retreived correctly"<<endl;}
	if(v3.Y() > 6.0 + EPSILON||v3.Y() < 6.0 - EPSILON){os<<"TestAdd Failed - y value not calculated or retreived correctly"<<endl;}	
	if(v3.Z() > 1009 + EPSILON||v3.Z() < 1009 - EPSILON){os<<"TestAdd Failed - z value not calculated or retreived correctly"<<endl;}	
}

void Vector3fTests::TestSubtract(ostream& os)
{
	Vector3f v1(1,2,60);
	Vector3f v2(3,4,90);
	Vector3f v3 = v1.Subtract(v2);
	if(v3.X() > -2.0 + EPSILON||v3.X() < -2.0 - EPSILON){os<<"TestSubtract Failed - x value not calculated or retreived correctly"<<endl;}
	if(v3.Y() > -2.0 + EPSILON||v3.Y() < -2.0 - EPSILON){os<<"TestSubtract Failed - y value not calculated or retreived correctly"<<endl;}	
	if(v3.Z() > -30.0 + EPSILON||v3.Z() < -30.0 - EPSILON){os<<"TestSubtract Failed - z value not calculated or retreived correctly"<<endl;}	
}

void Vector3fTests::TestMultiply(ostream& os)
{
	Vector3f v1(1,2,3);
	Vector3f v2 = v1.Multiply(2);
	if(v2.X() > 2.0 + EPSILON||v2.X() < 2.0 - EPSILON){os<<"TestMultiply Failed - x value not calculated or retreived correctly"<<endl;}
	if(v2.Y() > 4.0 + EPSILON||v2.Y() < 4.0 - EPSILON){os<<"TestMultiply Failed - y value not calculated or retreived correctly"<<endl;}
	if(v2.Z() > 6.0 + EPSILON||v2.Z() < 6.0 - EPSILON){os<<"TestMultiply Failed - z value not calculated or retreived correctly"<<endl;}	
}

void Vector3fTests::TestCross(ostream& os)
{
	Vector3f v1(1,0,0);
	Vector3f v2(0,1,0);
	Vector3f v3 = v1.Cross(v2);
	if(v3.X() > 0.0 + EPSILON||v3.X() < 0.0 - EPSILON){os<<"TestCross Failed - x value not calculated or retreived correctly"<<endl;}
	if(v3.Y() > 0.0 + EPSILON||v3.Y() < 0.0 - EPSILON){os<<"TestCross Failed - y value not calculated or retreived correctly"<<endl;}
	if(v3.Z() > 1.0 + EPSILON||v3.Z() < 1.0 - EPSILON){os<<"TestCross Failed - z value not calculated or retreived correctly"<<endl;}
}

void Vector3fTests::TestDot(ostream& os)
{
	Vector3f v1(1,0,0);
	Vector3f v2(0,1,0);
	float dot = v1.Dot(v1);
	if(dot > 1.0 + EPSILON||dot < 1.0 - EPSILON){os<<"TestDot Failed - value not calculated or retreived correctly (parallel)"<<endl;}

	dot = v1.Dot(v2);
	if(dot > EPSILON||dot < - EPSILON){os<<"TestDot Failed - value not calculated or retreived correctly (perpendicular)"<<endl;}
}
