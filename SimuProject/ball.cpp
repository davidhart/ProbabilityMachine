#include "ball.h"

#include "resourcebank.h"
#include "peg.h"
#include "plane.h"
#include "planesegment.h"

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
	ApplyForce(normal * - normal.Dot(m_force));
	ApplyForce(m_velocity*-0.03f);	// some kindof friction/energy transfer
}

bool Ball::CollisionTest(const Plane& plane, double& nextCollision)
{
	Vector3f p = CalcTenativePosition(nextCollision);

	if ( plane.GetNormal().Dot(m_position - plane.GetOrigin()) > m_radius-0.001f )
	{
		if ( plane.GetNormal().Dot(p - plane.GetOrigin()) <= m_radius)
		{
			double bottomTime = 0;
			double topTime = nextCollision;
			double midTime = bottomTime + (topTime-bottomTime)/2;

			for (int i = 0; i < 5; i++)
			{
				p = CalcTenativePosition(midTime);

				if (plane.GetNormal().Dot(p - plane.GetOrigin()) <= m_radius)
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

bool Ball::CollisionTest(const PlaneSegment& planeSegment, double& nextCollision)
{
	Vector3f p = CalcTenativePosition(nextCollision);

	if ( planeSegment.GetNormal().Dot(m_position - planeSegment.GetOrigin()) > -m_radius+0.001f )
	{
		if ( planeSegment.GetNormal().Dot(p - planeSegment.GetOrigin()) <= m_radius)
		{
			double bottomTime = 0;
			double topTime = nextCollision;
			double midTime = bottomTime + (topTime-bottomTime)/2;

			for (int i = 0; i < 5; i++)
			{
				p = CalcTenativePosition(midTime);

				if (planeSegment.GetNormal().Dot(p - planeSegment.GetOrigin()) <= m_radius)
				{
					topTime = midTime;
				}
				else
				{
					bottomTime = midTime;
				}
			}

			p = CalcTenativePosition(bottomTime);

			Vector3f bottomN = planeSegment.GetTopPoint()-planeSegment.GetOrigin();
			bottomN.Unit();

			Vector3f topN = planeSegment.GetOrigin()-planeSegment.GetTopPoint();
			topN.Unit();

			Vector3f frontN = planeSegment.GetFarPoint()-planeSegment.GetOrigin();
			frontN.Unit();
			
			Vector3f backN = planeSegment.GetOrigin()-planeSegment.GetFarPoint();
			backN.Unit();

			if ((bottomN.Dot(p-planeSegment.GetOrigin()) > -m_radius)		/*p above origin */
				&& (topN.Dot(p-planeSegment.GetTopPoint()) > -m_radius)		/* p below top */
				&& (frontN.Dot(p-planeSegment.GetOrigin()) > -m_radius)		/* p behind front */
				&& (backN.Dot(p-planeSegment.GetFarPoint()) > -m_radius)	/* p infront of back */)
			{

				nextCollision = bottomTime;
				return true;
			}

		}
	}

	return false;
}

void Ball::CollisionResponse(const PlaneSegment& planeSegment)
{
	float impulse = -(1+1)*m_velocity.Dot(planeSegment.GetNormal());
	m_velocity += planeSegment.GetNormal()*impulse;

	ApplyForce(planeSegment.GetNormal() * -planeSegment.GetNormal().Dot(m_force));
	ApplyForce(m_velocity*-0.03f);	// some kindof friction/energy transfer

}
