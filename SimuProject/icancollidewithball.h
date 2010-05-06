#ifndef _ICANCOLLIDEWITHBALL_H
#define _ICANCOLLIDEWITHBALL_H

class Ball;

class ICanCollideWithBall
{
public:
	virtual bool CollisionTest(Ball& ball, double& nextCollision) = 0;
	virtual void CollisionResponse(Ball& ball) = 0;
	virtual ~ICanCollideWithBall() { };
};

#endif