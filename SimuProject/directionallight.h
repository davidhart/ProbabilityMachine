#ifndef _DIRECTIONALLIGHT_H
#define _DIRECTIONALLIGHT_H

#include "light.h"
#include "Vector3f.h"

class DirectionalLight : public Light
{
private:
	Vector3f m_direction;

public:
	DirectionalLight();
	~DirectionalLight();

	void SetDirection(const Vector3f& direction);
	void Apply(int channel);
};

#endif