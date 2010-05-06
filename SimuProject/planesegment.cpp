#include "planesegment.h"

#include "ball.h"

PlaneSegment::PlaneSegment(const Vector3f& normal, const Vector3f& origin, const Vector3f& topPoint, const Vector3f& farPoint) :
	Plane ( normal, origin ),
	m_topPoint ( topPoint ),
	m_farPoint ( farPoint )
{
}

bool PlaneSegment::CollisionTest(Ball& ball, double& nextCollision)
{
	double nextCollisionTemp = nextCollision;

	if (Plane::CollisionTest(ball, nextCollisionTemp))
	{
		Vector3f p = ball.CalcTenativePosition(nextCollisionTemp);

		Vector3f bottomN = this->GetTopPoint()-this->GetOrigin();
		bottomN.Unit();

		Vector3f topN = this->GetOrigin()-this->GetTopPoint();
		topN.Unit();

		Vector3f frontN = this->GetFarPoint()-this->GetOrigin();
		frontN.Unit();
			
		Vector3f backN = this->GetOrigin()-this->GetFarPoint();
		backN.Unit();

		if ((bottomN.Dot(p-this->GetOrigin()-bottomN*ball.GetRadius()) >= -0.001f)		/*p above origin */
			&& (topN.Dot(p-this->GetTopPoint()-topN*ball.GetRadius()) >= -0.001f)		/* p below top */
			&& (frontN.Dot(p-this->GetOrigin()-frontN*ball.GetRadius()) >= -0.001f)		/* p behind front */
			&& (backN.Dot(p-this->GetFarPoint()-backN*ball.GetRadius()) >= -0.001f)	/* p infront of back */)
		{
			nextCollision = nextCollisionTemp;
			return true;
		}

		return false;
	}

	return false;

	/*
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



		}
	}*/
}

void PlaneSegment::CollisionResponse(Ball& ball)
{
	float impulse = -(1+1.0f)*ball.GetVelocity().Dot(this->GetNormal());

	ball.SetVelocity(ball.GetVelocity() + this->GetNormal()*impulse);

	ball.ApplyForce(this->GetNormal() * -this->GetNormal().Dot(ball.GetForce()));
	ball.ApplyForce(ball.GetVelocity()*-0.03f);	// some kindof friction/energy transfer
}