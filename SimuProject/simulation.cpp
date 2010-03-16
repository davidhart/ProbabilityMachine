#include "simulation.h"
#include "line2f.h"
#include "model.h"

#include <Gl/gl.h>
#include <iostream>

Simulation::Simulation() :
	m_rotation( 0.0 ),
	m_model("Resources/box.obj"),
	m_texture("boxtex.png"),
	m_camera(Vector3f(0, 0, -5), 0,0,0)
{
	window.SetTitle("Simulation");
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

	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float lightpos [ ] = {0 , 0 , 0 ,1};
	glLightfv( GL_LIGHT0 , GL_POSITION, lightpos );
}

void Simulation::Load()
{
	m_texture.Load();
	m_model.Load();
	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
}

void Simulation::Unload()
{

}

void Simulation::Update(double frameTime)
{
	m_rotation += frameTime*100.0;
	if (m_rotation > 360)
		m_rotation -= 360;

	//m_camera.RotateYaw((float)frameTime*100.0f);
	//m_camera.MoveForward(-(float)frameTime*10.0f);
}

void Simulation::Draw()
{
	glPushMatrix();

	m_camera.SetViewMatrix();

	glRotated(m_rotation, 1.0f, 1.0f, 0.0f);

	m_model.Draw();

	glPopMatrix();
}
