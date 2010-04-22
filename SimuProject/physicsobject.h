#ifndef _PHYSICSOBJECT_H
#define _PHYSICSOBJECT_H

#include "object.h"

class PhysicsObject : public Object
{
protected:
	Vector3f m_velocity;
	Vector3f m_force;
	float m_mass;

public:
	PhysicsObject();

	inline void SetVelocity(const Vector3f& velocity) { m_velocity = velocity; }
	inline const Vector3f& GetVelocity() const { return m_velocity; } 

	inline void ApplyForce(const Vector3f& force) { m_force += force; }

	inline void SetMass(float mass) { m_mass = mass; }
	inline float GetMass() const { return m_mass; }

	Vector3f CalcTenativePosition(double timeStep);
	void Update(double timeStep);
};

#endif