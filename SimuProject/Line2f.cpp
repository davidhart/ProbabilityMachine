#include "Line2f.h"

#include <cassert>

Line2f::Line2f(const Vector2f& point, const Vector2f& direction) : 
	m_point(point), m_direction(direction)
{
	assert(direction.Length() != 0);
}

Line2f::~Line2f()
{
}

float Line2f::PerpendicularDistanceToPoint(const Vector2f& point) const
{
	Vector2f op = point-m_point;
	float directionLength = m_direction.Length();
	float distToClosestPointOnLine = m_direction.Dot(op)/directionLength;
	//Vector2f distToPoint = point - (m_point + m_direction/directionLength * distToClosestPointOnLine);
	// more efficient way?
	Vector2f distToPoint( point.X() - (m_point.X() + m_direction.X()/directionLength * distToClosestPointOnLine),
						  point.Y() - (m_point.Y() + m_direction.Y()/directionLength * distToClosestPointOnLine));

	return distToPoint.Length();
}