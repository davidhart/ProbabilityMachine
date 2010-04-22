#ifndef _LINE3F_H
#define _LINE3F_H

#include "Vector3f.h"

class Line3f
{
private:
	Vector3f m_point, m_direction;

public:
	Line3f(const Vector3f& point, const Vector3f& direction);
	~Line3f();

	inline const Vector3f& Point() const { return m_point; }
	inline const Vector3f& Direction() const { return m_direction; }

	inline void SetPoint(const Vector3f& point) { m_point = point; }
	inline void SetDirection(const Vector3f& direction) { m_direction = direction; }

	Vector3f ClosestPointOnLineToPoint(const Vector3f& point) const;
	float PerpendicularDistanceToPoint(const Vector3f& point) const;
};

#endif
