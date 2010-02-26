#include "simulation.h"

#include "line2f.h"

#include <Gl/gl.h>

Simulation::Simulation()
{

}

void Simulation::Load()
{

}

void Simulation::Unload()
{

}

void Simulation::Update(double frameTime)
{

}

void Simulation::Draw()
{
	Line2f l(Vector2f(0,0), Vector2f(1,1));

	glBegin(GL_LINES);

	glVertex2f(l.Point().X(), l.Point().Y());

	glVertex2f(l.Point().X() + l.Direction().X(), l.Point().Y() + l.Direction().Y());

	glEnd();
}
