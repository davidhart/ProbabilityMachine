#ifndef _BALL_H
#define _BALL_H

#include "physicsobject.h"

class ResourceBank;
class Peg;
class Plane;

class Ball : public PhysicsObject
{
protected:
	float m_radius;

public:
	Ball(ResourceBank& resources, const Vector3f& position);

	bool CollisionTest(const Peg& peg, double& nextCollision);
	void CollisionResponse(const Peg& peg);

	bool CollisionTest(const Plane& plane, double& nextCollision);
	void CollisionResponse(const Plane& plane);
};

#endif