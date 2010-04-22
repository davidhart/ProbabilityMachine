#include "ball.h"

#include "resourcebank.h"
#include "peg.h"

#include "line3f.h";

Ball::Ball(ResourceBank& resources, const Vector3f &position) :
	PhysicsObject ( ),
	m_radius ( 0.125f )
{
	SetModel(resources.RequestModel("Resources/ball.obj"));
	SetPosition(position);
	SetMass( 0.004f );
}

bool Ball::CollisionTest(const Peg& peg, double& nextCollision)
{
	Vector3f tenativePosition = CalcTenativePosition(nextCollision);

	Vector3f direction = tenativePosition - m_position;

	Line3f motionLine(m_position, direction);

	Vector3f closestPointOnLine = motionLine.ClosestPointOnLineToPoint(peg.GetPosition());

	float distanceFromPtToLine = (closestPointOnLine - peg.GetPosition()).Length();

	if (distanceFromPtToLine < m_radius + peg.GetRadius())
	{
		if ((closestPointOnLine - m_position).Length() < direction.Length())
		{
			nextCollision*=0.7f;		
			return true;
		}
	}
	else if ((tenativePosition - peg.GetPosition()).Length() < m_radius + peg.GetRadius())
	{
		nextCollision*=0.7f;	
		return true;		
	}

	return false;
}

void Ball::CollisionResponse(const Peg& peg)
{
	//m_force = Vector3f(0,0,0);

	
	float speed = m_velocity.Length()*m_mass;

	Vector3f normal = m_position-peg.GetPosition();
	normal.Unit();
	ApplyForce(normal*0.9f*speed/m_mass);

	//m_velocity += normal*0.9f*speed/m_mass;

}

