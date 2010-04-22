#include "physicsobject.h"

#include <iostream>

PhysicsObject::PhysicsObject() :
	m_mass ( 1.0f ),
	m_force( 0, 0, 0 )
{
}

Vector3f PhysicsObject::CalcTenativePosition(double timeStep)
{
	Vector3f tenativePosition(m_position);

	Vector3f acceleration = m_force/m_mass;

	Vector3f vel = m_velocity + acceleration * (float)timeStep;
	tenativePosition += vel * (float)timeStep;

	return tenativePosition;
}

void PhysicsObject::Update(double timeStep)
{
	Vector3f newPos = CalcTenativePosition(timeStep);

	m_position = newPos;							// jump to new pos
	m_velocity += (m_force/m_mass)* (float)timeStep;// update velocity
	m_force = Vector3f(0, 0, 0);					// reset forces
}