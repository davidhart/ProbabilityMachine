#ifndef _PEG_H
#define _PEG_H

#include "physicsobject.h"
#include "icancollidewithball.h"

class ResourceBank;

class Peg : public PhysicsObject, public ICanCollideWithBall
{
private:
	float m_radius;

public:
	Peg(ResourceBank& resourcebank, const Vector3f& position);
	inline float GetRadius() const { return m_radius; }

	bool CollisionTest(Ball& ball, double& nextCollision);
	void CollisionResponse(Ball& ball);
};

#endif