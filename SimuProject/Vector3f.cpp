#include "Vector3f.h"

#include <cmath>

Vector3f::Vector3f() :
	m_X(0), m_Y(0), m_Z(0)
{ }

Vector3f::Vector3f(float pX, float pY, float pZ) :
	m_X(pX), m_Y(pY), m_Z(pZ)
{ }

Vector3f::~Vector3f()
{ }

float Vector3f::Length() const
{
	return sqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z);
}

void Vector3f::Unit()
{
	float len = Length();
	m_X /= len;
	m_Y /= len;
	m_Z /= len;
}

Vector3f Vector3f::Add(const Vector3f& pV) const
{
	return Vector3f(m_X + pV.m_X, m_Y + pV.m_Y, m_Z + pV.m_Z);
}

Vector3f Vector3f::Subtract(const Vector3f& pV) const
{
	return Vector3f(m_X - pV.m_X, m_Y - pV.m_Y, m_Z - pV.m_Z);
}

Vector3f Vector3f::Multiply(float pScalar) const
{
	return Vector3f(m_X * pScalar, m_Y * pScalar, m_Z * pScalar);
}

Vector3f Vector3f::Cross(const Vector3f& pV) const
{
	return Vector3f(m_Y*pV.m_Z - m_Z*pV.m_Y,
					m_Z*pV.m_X - m_X*pV.m_Z,
					m_X*pV.m_Y - m_Y*pV.m_X);
}

float Vector3f::Dot(const Vector3f& pV) const
{
	return m_X * pV.m_X + m_Y * pV.m_Y + m_Z * pV.m_Z;
}
