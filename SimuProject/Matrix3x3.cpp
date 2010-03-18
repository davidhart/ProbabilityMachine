#include "Matrix3x3.h"

#include <cmath>

void Matrix3x3::Identity(Matrix3x3& matrix)
{
	matrix.m_1_1 = 1; matrix.m_2_1 = 0; matrix.m_3_2 = 0;
	matrix.m_1_2 = 0; matrix.m_2_2 = 1; matrix.m_3_3 = 0;
	matrix.m_1_3 = 0; matrix.m_2_3 = 0; matrix.m_3_3 = 1;
}

void Matrix3x3::RotationX(Matrix3x3& matrix, float angle)
{
	matrix.m_1_1 = 1; matrix.m_2_1 = 0;				matrix.m_3_1 = 0;
	matrix.m_1_2 = 0; matrix.m_2_2 = cos(angle);	matrix.m_3_2 = -sin(angle);
	matrix.m_1_3 = 0; matrix.m_2_3 = sin(angle);	matrix.m_3_3 = cos(angle);
}

void Matrix3x3::RotationY(Matrix3x3& matrix, float angle)
{
	matrix.m_1_1 = cos(angle);	matrix.m_2_1 = 0;	matrix.m_3_1 = sin(angle);
	matrix.m_1_2 = 0;			matrix.m_2_2 = 1;	matrix.m_2_3 = 0;
	matrix.m_1_3 = -sin(angle); matrix.m_2_3 = 0;	matrix.m_3_3 = cos(angle);
}

void Matrix3x3::RotationZ(Matrix3x3& matrix, float angle)
{
	matrix.m_1_1 = cos(angle);	matrix.m_2_1 = -sin(angle); matrix.m_3_1 = 0;
	matrix.m_1_2 = sin(angle);	matrix.m_2_2 = cos(angle);	matrix.m_3_2 = 0;
	matrix.m_1_3 = 0;			matrix.m_2_3 = 0;			matrix.m_3_3 = 1;
}

void Matrix3x3::RotationAxis(Matrix3x3& matrix, const Vector3f& axis, float angle)
{
	float sinTheta = sin(angle);
	float cosTheta = cos(angle);

	float oneMinusCosTheta = 1-cosTheta;

	float axisXSquared = axis.X()*axis.X();
	float axisYSquared = axis.Y()*axis.Y();
	float axisZSquared = axis.Z()*axis.Z();
	
	matrix.m_1_1 =	axisXSquared + (1-axisXSquared) * cosTheta;	
		matrix.m_2_1 = axis.X()*axis.Y() * oneMinusCosTheta - axis.Z() * sinTheta;
			matrix.m_3_1 = axis.X()*axis.Z() * oneMinusCosTheta + axis.Y() * sinTheta;

	matrix.m_1_2 = axis.X()*axis.Y() * oneMinusCosTheta + axis.Z() * sinTheta;
		matrix.m_2_2 = axisYSquared + (1-axisYSquared) * cosTheta;
			matrix.m_3_2 = axis.Y()*axis.Z() * oneMinusCosTheta - axis.X() * sinTheta;

	matrix.m_1_3 = axis.X()*axis.Y() * oneMinusCosTheta - axis.Y()*sinTheta;
		matrix.m_2_3 = axis.Y()*axis.Z() * oneMinusCosTheta + axis.X()*sinTheta;
			matrix.m_3_3 = axisZSquared + (1-axisZSquared)*cosTheta;
}

const Vector3f operator* (const Vector3f& lhs, const Matrix3x3& rhs)
{
	Vector3f v(rhs.m_1_1 * lhs.X() + rhs.m_1_2 * lhs.Y() + rhs.m_1_3 * lhs.Z(),
			   rhs.m_2_1 * lhs.X() + rhs.m_2_2 * lhs.Y() + rhs.m_2_3 * lhs.Z(),
			   rhs.m_3_1 * lhs.X() + rhs.m_3_2 * lhs.Y() + rhs.m_3_3 * lhs.Z());
	return v;
}

const Matrix3x3 operator* (const Matrix3x3& lhs, const Matrix3x3& rhs)
{
	Matrix3x3 m;

	m.m_1_1 = lhs.m_1_1 * rhs.m_1_1 + lhs.m_2_1 * rhs.m_1_2 + lhs.m_3_1 * rhs.m_1_3;
	m.m_2_1 = lhs.m_1_1 * rhs.m_2_1 + lhs.m_2_1 * rhs.m_2_2 + lhs.m_3_1 * rhs.m_2_3;
	m.m_3_1 = lhs.m_1_1 * rhs.m_3_1 + lhs.m_2_1 * rhs.m_3_2 + lhs.m_3_1 * rhs.m_3_3;

	m.m_1_2 = lhs.m_1_2 * rhs.m_1_1 + lhs.m_2_2 * rhs.m_1_2 + lhs.m_3_2 * rhs.m_1_3;
	m.m_2_2 = lhs.m_1_2 * rhs.m_2_1 + lhs.m_2_2 * rhs.m_2_2 + lhs.m_3_2 * rhs.m_2_3;
	m.m_3_2 = lhs.m_1_2 * rhs.m_3_1 + lhs.m_2_2 * rhs.m_3_2 + lhs.m_3_2 * rhs.m_3_3;

	m.m_1_3 = lhs.m_1_3 * rhs.m_1_1 + lhs.m_2_3 * rhs.m_1_2 + lhs.m_3_3 * rhs.m_1_3;
	m.m_2_3 = lhs.m_1_3 * rhs.m_2_1 + lhs.m_2_3 * rhs.m_2_2 + lhs.m_3_3 * rhs.m_2_3;
	m.m_3_3 = lhs.m_1_3 * rhs.m_3_1 + lhs.m_2_3 * rhs.m_3_2 + lhs.m_3_3 * rhs.m_3_3;

	return m;
}