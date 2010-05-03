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
	/*
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
	*/

	/*
	Vector3f direction = (CalcTenativePosition(nextCollision) - m_position)/nextCollision;

	Vector3f pegPos = peg.GetPosition();

	float a = direction.Dot(direction);
	float b = 2* direction.Dot(m_position) - 2* direction.Dot(pegPos);
	float c = m_position.Dot(m_position) + pegPos.Dot(pegPos) - (m_radius + peg.GetRadius())*(m_radius + peg.GetRadius());
	float disc = b*b - 4*a*c;

	if (disc < 0)		// disc is negative no solutions
		return false;

	if (disc < 0.00001f) // disc is 0, 1 solution
	{
		float t = -b/2*a;
		nextCollision = t;
		return true;
	}

	float root = sqrt(disc);
	float t0 = (-b + root)/2*a;
	float t1 = (-b - root)/2*a;

	if (t0 >= 0 && t1 >= 0)
	{
		float t = t0 < t1 ? t0 : t1;
		if (t <= nextCollision)
		{
			nextCollision = t;
			return true;
		}
	}
	else
	{
		if (t0 >= 0 && t0 <= nextCollisio/)
		{
			nextCollision = t0;
			return true;
		}
		else if (t1 >= 0 && t1 <= nextCollision)
		{
			nextCollision = t1;
			return true;
		}

	}

	return false;
	*/


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

