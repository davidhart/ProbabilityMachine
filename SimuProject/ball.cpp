#include "ball.h"

#include "resourcebank.h"
#include "peg.h"

#include "line3f.h"

#include <cmath>
#include <iostream>

#include "vector2f.h"

Ball::Ball(ResourceBank& resources, const Vector3f &position) :
	PhysicsObject ( ),
	m_radius ( 0.125f )
{
	SetModel(resources.RequestModel("Resources/ball.obj"));
	SetPosition(position);
	SetMass( 0.003f );
}

bool Ball::CollisionTest(const Peg& peg, double& nextCollision)
{
	Vector3f p = CalcTenativePosition(nextCollision);

	Vector2f p2D (p.X(), p.Y());

	Vector2f pegPosition2D(peg.GetPosition().X(), peg.GetPosition().Y());

	if ((pegPosition2D - p2D).Length() <= m_radius + peg.GetRadius())
	{
		double bottomTime = 0;
		double topTime = nextCollision;
		double midTime = bottomTime + (topTime-bottomTime)/2;

		for (int i = 0; i < 5; i++)
		{
			p = CalcTenativePosition(midTime);
			p2D.SetX(p.X());
			p2D.SetY(p.Y());
			
			if ((pegPosition2D - p2D).Length() <= m_radius + peg.GetRadius())
			{
				topTime = midTime;
			}
			else
			{
				bottomTime = midTime;
			}
		}

		nextCollision = bottomTime+0.0001f;
		
		return true;
	}

	return false;
}

void Ball::CollisionResponse(const Peg& peg)
{
	Vector3f normal (m_position.X()-peg.GetPosition().X(), m_position.Y()-peg.GetPosition().Y(), 0.0f);
	normal.Unit();

	float impulse = -(1+0.8)*m_velocity.Dot(normal)*m_mass;
	m_velocity += normal*impulse/m_mass;
	ApplyForce(m_velocity*-0.03f);	// some kindof friction/energy transfer
}

