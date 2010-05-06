#include "Vector2f.h"

#include <cmath>

Vector2f::Vector2f() :
	m_X(0), m_Y(0)
{ }

Vector2f::Vector2f(float pX, float pY) :
	m_X(pX), m_Y(pY)
{ }

Vector2f::~Vector2f()
{ }

float Vector2f::Length() const
{
	return sqrt(m_X*m_X + m_Y*m_Y);
}

void Vector2f::Unit()
{
	float len = Length();
	m_X /= len;
	m_Y /= len;
}

Vector2f Vector2f::Add(const Vector2f& pV) const
{
	return Vector2f(m_X + pV.m_X, m_Y + pV.m_Y);
}
const Vector2f& Vector2f::operator+=(const Vector2f& pV)
{
	m_X += pV.m_X;
	m_Y += pV.m_Y;

	return *this;
}


Vector2f Vector2f::Subtract(const Vector2f& pV) const
{
	return Vector2f(m_X - pV.m_X, m_Y - pV.m_Y);
}

Vector2f Vector2f::Multiply(float pScalar) const
{
	return Vector2f(m_X*pScalar, m_Y*pScalar);
}

float Vector2f::Dot(const Vector2f& pV) const
{
	return m_X * pV.m_X + m_Y * pV.m_Y;
}
