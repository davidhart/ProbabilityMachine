#ifndef _PLANE_H
#define _PLANE_H

#include "Vector3f.h"

class Plane
{
private:
	Vector3f m_normal;
	Vector3f m_point;

public:
	Plane(const Vector3f& normal, const Vector3f& point);
	
	inline const Vector3f& GetNormal() const { return m_normal; }
	inline const Vector3f& GetPoint() const { return m_point; }
};

#endif