#include "simulation.h"

#include "line2f.h"

#include <Gl/gl.h>

#include <iostream>

Simulation::Simulation() :
	m_rotation( 0.0 )
{

}

void Simulation::OnResize(int width, int height)
{
	Game::OnResize(width, height);

	double aspect = (double)width/(double)height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-aspect, aspect, -1, 1, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Simulation::Load()
{

}

void Simulation::Unload()
{

}

void Simulation::Update(double frameTime)
{
	m_rotation += frameTime*100.0;
	if (m_rotation > 360)
		m_rotation -= 360;
}

void Simulation::Draw()
{
	glPushMatrix();
	glTranslated(0, 0, -1);

	Line2f l(Vector2f(-1,-1), Vector2f(2,4));
	Vector2f point(0.5, -0.5);

	Vector2f closePoint = l.ClosestPointOnLineToPoint(point);

	Line2f closeLine(closePoint, point-closePoint);

	glBegin(GL_LINES);
		glColor3d(1.0, 1.0, 1.0);
		glVertex3f(l.Point().X(), l.Point().Y(), 0);
		glVertex3f(l.Point().X() + l.Direction().X(), l.Point().Y() + l.Direction().Y(), 0);
		
		glColor3d(1.0, 0.0, 0.0);
		glVertex3f(closeLine.Point().X(), closeLine.Point().Y(), 0);
		glVertex3f(closeLine.Point().X() + closeLine.Direction().X(), closeLine.Point().Y() + closeLine.Direction().Y(), 0);
	glEnd();


	glPointSize(5.0f);
	glBegin(GL_POINTS);
		glColor3d(0.0, 0.0, 1.0);
		glVertex3f(point.X(), point.Y(), 0);
		
		glColor3d(0.0, 1.0, 0.0);
		glVertex3f(closePoint.X(), closePoint.Y(), 0);
	glEnd();

	glPopMatrix();
}
