#ifndef _BALL_H
#define _BALL_H

#include "physicsobject.h"
#include "icancollidewithball.h"

class ResourceBank;
class Peg;
class Plane;
class PlaneSegment;

class Ball : public PhysicsObject, public ICanCollideWithBall
{
protected:
	float m_radius;

public:
	Ball(ResourceBank& resources, const Vector3f& position);
	inline float GetRadius() { return m_radius; }

	bool CollisionTest(Ball& ball, double& nextCollision);
	void CollisionResponse(Ball& ball);
};

#endif