#include "ball.h"

#include "resourcebank.h"

Ball::Ball(ResourceBank *resources, const Vector3f &position) :
	PhysicsObject ( ),
	m_radius ( 0.125f )
{
	SetModel(resources->RequestModel("Resources/ball.obj"));
	SetPosition(position);
	SetMass( 0.004f );
}

void Ball::Update(double elapsedTime)
{
	ApplyForce(Vector3f(0, -98.1f*m_mass, 0));	// Gravity
	ApplyForce(m_velocity*-0.02f);				// Air resistance

	PhysicsObject::Update(elapsedTime);
}

