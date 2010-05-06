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

bool Ball::CollisionTest(Ball& ball, double& nextCollision)
{
	Vector3f p2 = ball.CalcTenativePosition(nextCollision);
	Vector3f p1 = this->CalcTenativePosition(nextCollision);

	if ((p2 - p1).Length() <= ball.GetRadius() + this->GetRadius())
	{
		double bottomTime = 0;
		double topTime = nextCollision;
		double midTime = bottomTime + (topTime-bottomTime)/2;

		for (int i = 0; i < 5; i++)
		{
			p1 = ball.CalcTenativePosition(midTime);
			p2 = this->CalcTenativePosition(midTime);
			
			if ((p2 - p1).Length() <= ball.GetRadius() + this->GetRadius())
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

void Ball::CollisionResponse(Ball& ball)
{
	Vector3f normal = ball.GetPosition()- this->GetPosition();
	normal.Unit();

	float impulse = -(0.8f+0.8f)*ball.GetVelocity().Dot(normal);
	ball.SetVelocity(ball.GetVelocity() + normal*impulse);
	ball.ApplyForce(normal * - normal.Dot(ball.GetForce()));
	ball.ApplyForce(ball.GetVelocity()*-0.01f);	// some kindof friction/energy transfer

	this->SetVelocity(this->GetVelocity() + normal*-impulse);
	this->ApplyForce(normal * normal.Dot(this->GetForce()));
	this->ApplyForce(ball.GetVelocity()*-0.01f);
}