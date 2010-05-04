#ifndef _PLANESEGMENT_H
#define _PLANESEGMENT_H

#include "Vector3f.h"
#include "plane.h"

class PlaneSegment : public Plane
{
private:
	Vector3f m_topPoint;
	Vector3f m_farPoint;

public:
	PlaneSegment(const Vector3f& normal, const Vector3f& origin, const Vector3f& topPoint, const Vector3f& farPoint);

	inline const Vector3f& GetTopPoint() const { return m_topPoint; }
	inline const Vector3f& GetFarPoint() const { return m_farPoint; }
};

#endif