#include "ball.h"

#include "resourcebank.h"
#include "peg.h"
#include "plane.h"

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

		nextCollision = bottomTime;
		
		return true;
	}

	return false;
}

void Ball::CollisionResponse(const Peg& peg)
{
	Vector3f normal (m_position.X()-peg.GetPosition().X(), m_position.Y()-peg.GetPosition().Y(), 0.0f);
	normal.Unit();

	float impulse = -(1+0.8f)*m_velocity.Dot(normal);
	m_velocity += normal*impulse;
	ApplyForce(m_velocity*-0.03f);	// some kindof friction/energy transfer
}

bool Ball::CollisionTest(const Plane& plane, double& nextCollision)
{
	Vector3f p = CalcTenativePosition(nextCollision);

	if ( plane.GetNormal().Dot(m_position - (plane.GetPoint()+plane.GetNormal()*m_radius)) > -0.001f )
	{
		if ( plane.GetNormal().Dot(p - (plane.GetPoint()+plane.GetNormal()*m_radius)) <= 0)
		{
			double bottomTime = 0;
			double topTime = nextCollision;
			double midTime = bottomTime + (topTime-bottomTime)/2;

			for (int i = 0; i < 5; i++)
			{
				p = CalcTenativePosition(midTime);

				if (plane.GetNormal().Dot(p - (plane.GetPoint()+plane.GetNormal()*m_radius)) <= 0)
				{
					topTime = midTime;
				}
				else
				{
					bottomTime = midTime;
				}
			}

			nextCollision = bottomTime;

			return true;
		}
	}

	return false;
}

void Ball::CollisionResponse(const Plane& plane)
{	
	float impulse = -(1+0.8f)*m_velocity.Dot(plane.GetNormal());
	m_velocity += plane.GetNormal()*impulse;

	ApplyForce(plane.GetNormal() * -plane.GetNormal().Dot(m_force));
	ApplyForce(m_velocity*-0.03f);	// some kindof friction/energy transfer
}
