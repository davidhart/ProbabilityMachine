#include "planesegment.h"

PlaneSegment::PlaneSegment(const Vector3f& normal, const Vector3f& origin, const Vector3f& topPoint, const Vector3f& farPoint) :
	Plane ( normal, origin ),
	m_topPoint ( topPoint ),
	m_farPoint ( farPoint )
{
}