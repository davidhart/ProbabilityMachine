#ifndef _LINE2F_H
#define _LINE2F_H

#include "Vector2f.h"

class Line2f
{
private:
	Vector2f m_point, m_direction;

public:
	Line2f(const Vector2f& point, const Vector2f& direction);
	~Line2f();

	inline const Vector2f& Point() const { return m_point; }
	inline const Vector2f& Direction() const { return m_direction; }

	inline void SetPoint(const Vector2f& point) { m_point = point; }
	inline void SetDirection(const Vector2f& direction) { m_direction = direction; }

	Vector2f ClosestPointOnLineToPoint(const Vector2f& point) const;
	float PerpendicularDistanceToPoint(const Vector2f& point) const;
};

#endif
