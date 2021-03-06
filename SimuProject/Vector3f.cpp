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

const Vector3f Vector3f::Add(const Vector3f& pV) const
{
	return Vector3f(m_X + pV.m_X, m_Y + pV.m_Y, m_Z + pV.m_Z);
}

const Vector3f& Vector3f::operator+=(const Vector3f& pV)
{
	m_X += pV.m_X;
	m_Y += pV.m_Y;
	m_Z += pV.m_Z;
	return *this;
}

const Vector3f Vector3f::Subtract(const Vector3f& pV) const
{
	return Vector3f(m_X - pV.m_X, m_Y - pV.m_Y, m_Z - pV.m_Z);
}

const Vector3f& Vector3f::operator-=(const Vector3f& pV)
{
	m_X -= pV.m_X;
	m_Y -= pV.m_Y;
	m_Z -= pV.m_Z;
	return *this;
}

const Vector3f Vector3f::Multiply(float pScalar) const
{
	return Vector3f(m_X * pScalar, m_Y * pScalar, m_Z * pScalar);
}

const Vector3f& Vector3f::operator*=(float pScalar)
{
	m_X *= pScalar;
	m_Y *= pScalar;
	m_Z *= pScalar;
	return *this;
}

const Vector3f Vector3f::Divide(float pScalar) const
{
	return Vector3f(m_X / pScalar, m_Y / pScalar, m_Z / pScalar);
}

const Vector3f& Vector3f::operator/=(float pScalar)
{
	m_X /= pScalar;
	m_Y /= pScalar;
	m_Z /= pScalar;
	return *this;
}

const Vector3f Vector3f::Cross(const Vector3f& pV) const
{
	return Vector3f(m_Y*pV.m_Z - m_Z*pV.m_Y,
					m_Z*pV.m_X - m_X*pV.m_Z,
					m_X*pV.m_Y - m_Y*pV.m_X);
}

float Vector3f::Dot(const Vector3f& pV) const
{
	return m_X * pV.m_X + m_Y * pV.m_Y + m_Z * pV.m_Z;
}

std::istream& operator>>(std::istream& in, Vector3f& v)
{
	float x,y,z;
	std::istream::pos_type p =  in.tellg();

	in >> x >> y >> z;

	if (in.fail())
		in.seekg(p);
	else
	{
		v.SetX(x);
		v.SetY(y);
		v.SetZ(z);
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, Vector3f& v)
{
	out << "v(" << v.X() << "," << v.Y() << "," << v.Z() << ")";
	return out;
}