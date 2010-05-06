#ifndef _VECTOR2F_H
#define _VECTOR2F_H

class Vector2f
{
private:
	float m_X, m_Y;

public:
	Vector2f();
	Vector2f(float pX, float pY);
	~Vector2f();

	inline float X()const { return m_X; }
	inline float Y()const { return m_Y; }

	inline void SetX(float pX) { m_X = pX; }
	inline void SetY(float pY) { m_Y = pY; }

	float Length()const;
	void Unit();

	Vector2f Add(const Vector2f& pV)const;
	inline Vector2f operator+(const Vector2f& pV) const { return Add(pV); }
	const Vector2f& operator+=(const Vector2f& pV);

	Vector2f Subtract(const Vector2f& pV)const;
	inline Vector2f operator-(const Vector2f& pV) const { return Subtract(pV); }
	const Vector2f& operator-=(const Vector2f& pV);

	Vector2f Multiply(float pScalar)const;
	inline Vector2f operator*(float pScalar) const { return Multiply(pScalar); }
	const Vector2f& operator*=(float pScalar);

	float Dot(const Vector2f& pV)const;
};

#endif
