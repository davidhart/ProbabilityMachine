#include "Matrix3x3Tests.h"
#include "Matrix3x3.h"
#include "Vector3f.h"
#include "Math.h"

using std::endl;

void Matrix3x3Tests::DoAllTests(ostream& os)
{
	Vector3f v(0, 0, 1);
	Matrix3x3 m;

	Matrix3x3::RotationX(m, MATH_PI/2);
	Vector3f v2 = v*m;

	Matrix3x3::RotationZ(m, MATH_PI/2);
	Vector3f v3 = v2*m;
	os << "Matrix3x3 Tests Complete" << endl;
}