#include "MathsTests.h"
#include "Vector2fTests.h"
#include "Vector3fTests.h"
#include "Line2fTests.h"
#include "Line3fTests.h"
#include "Matrix3x3Tests.h"

using std::endl;

void MathsLibTests::DoAllTests(ostream& os)
{
	os<<"Maths Tests Start"<<endl;
	Vector2fTests::DoAllTests(os);
	Vector3fTests::DoAllTests(os);
	Line2fTests::DoAllTests(os);
	Line3fTests::DoAllTests(os);
	Matrix3x3Tests::DoAllTests(os);
	os<<"Maths Tests Complete"<<endl;
}
