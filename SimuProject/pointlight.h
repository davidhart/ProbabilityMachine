#ifndef _POINTLIGHT_H
#define _POINTLIGHT_H

#include "light.h"

#include "vector3f.h"

class PointLight : public Light
{
private:
	Vector3f m_position;
public:
	PointLight();
	~PointLight();

	void SetPosition(const Vector3f& position);
	void Apply(int channel);
};

#endif