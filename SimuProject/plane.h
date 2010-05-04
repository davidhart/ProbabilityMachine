#ifndef _PLANE_H
#define _PLANE_H

#include "Vector3f.h"

class Plane
{
private:
	Vector3f m_normal;
	Vector3f m_origin;

public:
	Plane(const Vector3f& normal, const Vector3f& origin);
	
	inline const Vector3f& GetNormal() const { return m_normal; }
	inline const Vector3f& GetOrigin() const { return m_origin; }
};

#endif