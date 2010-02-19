#include "Vector2fTests.h"
#include "Vector2f.h"

using std::endl;

const float EPSILON = 0.000001f;

void Vector2fTests::DoAllTests(ostream& os)
{
	os<<"Vector2f Tests Start"<<endl;
	TestEmptyConstructor(os);
	TestTwoFloatConstructor(os);
	TestX(os);
	TestY(os);
	TestLength(os);
	TestSetX(os);
	TestSetY(os);
	TestUnit(os);
	TestAdd(os);
	TestSubtract(os);
	TestMultiply(os);
	TestDot(os);
	os<<"Vector2f Tests Complete"<<endl;
}

void Vector2fTests::TestEmptyConstructor(ostream& os)
{	
	Vector2f v;
	if(v.X()>EPSILON||v.X()<-EPSILON){os<<"TestEmptyConstructor Failed - x value not set to zero"<<endl;}
	if(v.Y()>EPSILON||v.Y()<-EPSILON){os<<"TestEmptyConstructor Failed - y value not set to zero"<<endl;}
}

void Vector2fTests::TestTwoFloatConstructor(ostream& os)
{	
	Vector2f v(1, 2);
	if(v.X()> 1 + EPSILON||v.X()< 1 - EPSILON){os<<"TestTwoFloatConstructor Failed - x value not set or retreived correctly"<<endl;}
	if(v.Y()> 2 + EPSILON||v.Y()< 2 - EPSILON){os<<"TestTwoFloatConstructor Failed - y value not set or retreived correctly"<<endl;}
}

void Vector2fTests::TestX(ostream& os)
{
	Vector2f v(1, 0);
	if(v.X()> 1 + EPSILON||v.X()< 1 - EPSILON){os<<"TestX Failed - x value not set or retreived correctly"<<endl;}
}

void Vector2fTests::TestY(ostream& os)
{
	Vector2f v(0, 1);
	if(v.Y()> 1 + EPSILON||v.Y()< 1 - EPSILON){os<<"TestY Failed - y value not set or retreived correctly"<<endl;}
}

void Vector2fTests::TestLength(ostream& os)
{
	Vector2f v(3, 4);
	if(v.Length() > 5 + EPSILON||v.Length()< 5 - EPSILON){os<<"TestLength Failed - length value not calculated correctly"<<endl;}
}

void Vector2fTests::TestSetX(ostream& os)
{
	Vector2f v;
	v.SetX(1);
	if(v.X()> 1 + EPSILON||v.X()< 1 - EPSILON){os<<"TestSetX Failed - x value not set or retreived correctly"<<endl;}
}

void Vector2fTests::TestSetY(ostream& os)
{
	Vector2f v;
	v.SetY(1);
	if(v.Y()> 1 + EPSILON||v.Y()< 1 - EPSILON){os<<"TestSetY Failed - y value not set or retreived correctly"<<endl;}
}

void Vector2fTests::TestUnit(ostream& os)
{
	Vector2f v(3,4);
	v.Unit();
	if(v.X() > 3.0/5.0 + EPSILON||v.X() < 3.0/5.0 - EPSILON){os<<"TestUnit Failed - x value not calculated or retreived correctly"<<endl;}
	if(v.Y() > 4.0/5.0 + EPSILON||v.Y() < 4.0/5.0 - EPSILON){os<<"TestUnit Failed - y value not calculated or retreived correctly"<<endl;}
}

void Vector2fTests::TestAdd(ostream& os)
{
	Vector2f v1(1,2);
	Vector2f v2(3,4);
	Vector2f v3 = v1.Add(v2);
	if(v3.X() > 4.0 + EPSILON||v3.X() < 4.0 - EPSILON){os<<"TestAdd Failed - x value not calculated or retreived correctly"<<endl;}
	if(v3.Y() > 6.0 + EPSILON||v3.Y() < 6.0 - EPSILON){os<<"TestAdd Failed - y value not calculated or retreived correctly"<<endl;}	
}

void Vector2fTests::TestSubtract(ostream& os)
{
	Vector2f v1(1,2);
	Vector2f v2(3,4);
	Vector2f v3 = v1.Subtract(v2);
	if(v3.X() > -2.0 + EPSILON||v3.X() < -2.0 - EPSILON){os<<"TestSubtract Failed - x value not calculated or retreived correctly"<<endl;}
	if(v3.Y() > -2.0 + EPSILON||v3.Y() < -2.0 - EPSILON){os<<"TestSubtract Failed - y value not calculated or retreived correctly"<<endl;}	
}

void Vector2fTests::TestMultiply(ostream& os)
{
	Vector2f v1(1,2);
	Vector2f v2 = v1.Multiply(2);
	if(v2.X() > 2.0 + EPSILON||v2.X() < 2.0 - EPSILON){os<<"TestMultiply Failed - x value not calculated or retreived correctly"<<endl;}
	if(v2.Y() > 4.0 + EPSILON||v2.Y() < 4.0 - EPSILON){os<<"TestMultiply Failed - y value not calculated or retreived correctly"<<endl;}	
}

void Vector2fTests::TestDot(ostream& os)
{
	Vector2f v1(2, 0);
	Vector2f v2(0, 3);
	float dot = v1.Dot(v2);
	if(dot > EPSILON||dot < - EPSILON){os<<"TestDot Failed - value not calculated or retreived correctly (perpendicular)"<<endl;}

	dot = v1.Dot(v1);
	if(dot > 4.0 + EPSILON||dot < 4.0 - EPSILON){os<<"TestDot Failed - value not calculated or retreived correctly (parallel)"<<endl;}
}
