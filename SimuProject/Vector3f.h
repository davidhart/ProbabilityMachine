#ifndef _VECTOR3F_H
#define _VECTOR3F_H

#include <istream>

class Vector3f
{
public:
	float m_X, m_Y, m_Z;
public:
	Vector3f();
	Vector3f(float pX, float pY, float pZ);
	~Vector3f();

	inline float X() const { return m_X; }
	inline float Y() const { return m_Y; }
	inline float Z() const { return m_Z; }

	inline void SetX(float pX) { m_X = pX; }
	inline void SetY(float pY) { m_Y = pY; }
	inline void SetZ(float pZ) { m_Z = pZ; }

	float Length()const;
	void Unit();

	Vector3f Add(const Vector3f& pV)const;
	inline Vector3f operator+(const Vector3f& pV)const { return Add(pV); }

	Vector3f Subtract(const Vector3f& pV)const;
	inline Vector3f operator-(const Vector3f& pV)const { return Subtract(pV); }

	Vector3f Multiply(float pScalar)const;
	inline Vector3f operator*(float pScalar)const { return Multiply(pScalar); }

	Vector3f Cross(const Vector3f& pV)const;
	float Dot(const Vector3f& pV)const;
};

std::istream& operator>>(std::istream& in, Vector3f& v);

#endif
