#ifndef _PHYSICSOBJECT_H
#define _PHYSICSOBJECT_H

#include "object.h"

class PhysicsObject : public Object
{
protected:
	Vector3f m_velocity;
	Vector3f m_acceleration;
	float m_mass;

public:
	PhysicsObject();
	virtual void Update(double elapsedTime);

	inline void SetVelocity(const Vector3f& velocity) { m_velocity = velocity; }
	inline void SetAcceleration(const Vector3f& acceleration) { m_acceleration = acceleration; }
	inline void ApplyForce(const Vector3f& force) { m_acceleration += force/m_mass; }
	inline void SetMass(float mass) { m_mass = mass; }
};

#endif