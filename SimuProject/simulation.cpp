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
	glTranslated(0, 0, -10);
	glRotated(m_rotation, 1,0,0);
	Line2f l(Vector2f(0,0), Vector2f(1,1));

	glBegin(GL_LINES);

	glVertex3f(l.Point().X(), l.Point().Y(), 0);

	glVertex3f(l.Point().X() + l.Direction().X(), l.Point().Y() + l.Direction().Y(), 0);

	glEnd();

	glBegin(GL_QUADS);

	glVertex3f(-1, -1, 0);
	glVertex3f(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3d(0, -1, 0);
	glEnd();

	glPopMatrix();
}
