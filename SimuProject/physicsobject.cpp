#include "physicsobject.h"

PhysicsObject::PhysicsObject() :
	m_mass ( 1.0f )
{
}

void PhysicsObject::Update(double elapsedTime)
{
	m_velocity += m_acceleration * (float)elapsedTime;
	m_position += m_velocity * (float)elapsedTime;
	m_acceleration = Vector3f(0,0,0);
}