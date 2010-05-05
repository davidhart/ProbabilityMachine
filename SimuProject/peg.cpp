#include "peg.h"
#include "resourcebank.h"

#include "ball.h"
#include "Vector2f.h"

Peg::Peg(ResourceBank& resourcebank, const Vector3f& position) : 
	m_radius ( 0.1f )
{
	SetModel(resourcebank.RequestModel("Resources/peg.obj"));
	SetPosition(position);
}

bool Peg::CollisionTest(Ball& ball, double& nextCollision)
{	
	Vector3f p = ball.CalcTenativePosition(nextCollision);

	Vector2f p2D (p.X(), p.Y());

	Vector2f pegPosition2D(this->GetPosition().X(), this->GetPosition().Y());

	if ((pegPosition2D - p2D).Length() <= ball.GetRadius() + this->GetRadius())
	{
		double bottomTime = 0;
		double topTime = nextCollision;
		double midTime = bottomTime + (topTime-bottomTime)/2;

		for (int i = 0; i < 5; i++)
		{
			p = ball.CalcTenativePosition(midTime);
			p2D.SetX(p.X());
			p2D.SetY(p.Y());
			
			if ((pegPosition2D - p2D).Length() <= ball.GetRadius() + this->GetRadius())
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

void Peg::CollisionResponse(Ball& ball)
{
	Vector3f normal (ball.GetPosition().X()-this->GetPosition().X(), ball.GetPosition().Y()-this->GetPosition().Y(), 0.0f);
	normal.Unit();

	float impulse = -(1+0.7f)*ball.GetVelocity().Dot(normal);
	ball.SetVelocity(ball.GetVelocity() + normal*impulse);
	ball.ApplyForce(normal * - normal.Dot(ball.GetForce()));
	ball.ApplyForce(ball.GetVelocity()*-0.01f);	// some kindof friction/energy transfer
}