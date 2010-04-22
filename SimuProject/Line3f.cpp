#include "Line3f.h"

Line3f::Line3f(const Vector3f& point, const Vector3f& direction) :
	m_point(point), m_direction(direction)
{
}

Line3f::~Line3f()
{
}

Vector3f Line3f::ClosestPointOnLineToPoint(const Vector3f& point) const
{
	Vector3f op = point-m_point;
	float directionLength = m_direction.Length();
	float distToClosestPointOnLine = m_direction.Dot(op)/directionLength;

	return Vector3f(m_point.X() + m_direction.X()/directionLength * distToClosestPointOnLine,
					m_point.Y() + m_direction.Y()/directionLength * distToClosestPointOnLine,
					m_point.Z() + m_direction.Z()/directionLength * distToClosestPointOnLine);
}

float Line3f::PerpendicularDistanceToPoint(const Vector3f& point) const
{
	Vector3f op = point-m_point;
	float directionLength = m_direction.Length();
	float distToClosestPointOnLine = m_direction.Dot(op)/directionLength;
	//Vector3f disttopoint = point - (m_point + m_direction/directionLength * distToClosestPointOnLine);
	// more efficient way?
	Vector3f distToPoint( point.X() - (m_point.X() + m_direction.X()/directionLength * distToClosestPointOnLine),
						  point.Y() - (m_point.Y() + m_direction.Y()/directionLength * distToClosestPointOnLine),
						  point.Z() - (m_point.Z() + m_direction.Z()/directionLength * distToClosestPointOnLine));

	return distToPoint.Length();
}