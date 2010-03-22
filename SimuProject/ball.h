#ifndef _BALL_H
#define _BALL_H

#include "physicsobject.h"

class ResourceBank;

class Ball : public PhysicsObject
{
protected:
	float m_radius;

public:
	Ball(ResourceBank* resources, const Vector3f& position);
	void Update(double elapsedTime);
};

#endif