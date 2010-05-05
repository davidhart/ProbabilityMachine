#include "plane.h"

#include "ball.h"

Plane::Plane(const Vector3f& normal, const Vector3f& origin) :
	m_normal ( normal ),
	m_origin ( origin )
{
}

bool Plane::CollisionTest(Ball& ball, double& nextCollision)
{
	Vector3f p = ball.CalcTenativePosition(nextCollision);

	if ( this->GetNormal().Dot(ball.GetPosition() - this->GetOrigin()) > ball.GetRadius())
	{
		if ( this->GetNormal().Dot(p - (this->GetOrigin()+this->GetNormal()*ball.GetRadius())) < 0)
		{
			double bottomTime = 0;
			double topTime = nextCollision;
			double midTime = bottomTime + (topTime-bottomTime)/2;

			for (int i = 0; i < 5; i++)
			{
				p = ball.CalcTenativePosition(midTime);

				if (this->GetNormal().Dot(p -(this->GetOrigin()+this->GetNormal()*ball.GetRadius())) < 0)
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

void Plane::CollisionResponse(Ball& ball)
{
	float impulse = -(1+0.8f)*ball.GetVelocity().Dot(this->GetNormal());

	ball.SetVelocity(ball.GetVelocity() + this->GetNormal()*impulse);

	ball.ApplyForce(this->GetNormal() * -this->GetNormal().Dot(ball.GetForce()));
	ball.ApplyForce(ball.GetVelocity()*-0.03f);	// some kindof friction/energy transfer
}