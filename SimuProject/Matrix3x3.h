#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_

#include "Vector3f.h"

class Matrix3x3
{
private:
	float m_1_1, m_2_1, m_3_1;
	float m_1_2, m_2_2, m_3_2;
	float m_1_3, m_2_3, m_3_3;

public:
	static void Identity(Matrix3x3& matrix);
	static void RotationX(Matrix3x3& matrix, float angle);
	static void RotationY(Matrix3x3& matrix, float angle);
	static void RotationZ(Matrix3x3& matrix, float angle);
	static void RotationAxis(Matrix3x3& matrix, const Vector3f& axis, float angle);

	friend const Vector3f operator* (const Vector3f& lhs, const Matrix3x3& rhs);
	friend const Matrix3x3 operator* (const Matrix3x3& lhs, const Matrix3x3& rhs);
};

#endif