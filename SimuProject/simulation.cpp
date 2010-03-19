#include "simulation.h"
#include "line2f.h"
#include "model.h"

#include <Gl/gl.h>
#include <iostream>

#include "Math.h" // PI
#include <cmath>

Simulation::Simulation() :
	m_rotationX( 0.0 ),
	m_rotationY( 0.0 ),
	m_model("Resources/machine.obj"),
	m_texture("boxtex.png"),
	m_camera(Vector3f(0, 2, 20), 0, 0, 0)
{
	m_window.SetTitle("Simulation");
}

void Simulation::OnResize(int width, int height)
{
	Game::OnResize(width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	double aspect = (double)width/(double)height;

	double nearPlane = 1;
	double farPlane = 1000;
	double fov = 45.0*MATH_PI/180.0f;
	double top = tan(fov*0.5) * nearPlane;
	glFrustum(-aspect*top, aspect*top, -top, top, nearPlane, farPlane);
	
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
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambient [] = { 0.4f, 0.4f, 0.4f, 0.4f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
}

void Simulation::Unload()
{

}

void Simulation::Update(const Input& input, double frameTime)
{
	if (input.IsKeyDown(Input::KEY_LEFT))
		m_camera.MoveStrafe(-(float)frameTime*10.0f);

	if (input.IsKeyDown(Input::KEY_RIGHT))
		m_camera.MoveStrafe((float)frameTime*10.0f);

	if (input.IsKeyDown(Input::KEY_UP))
		m_camera.MoveForward(-(float)frameTime*10.0f);

	if (input.IsKeyDown(Input::KEY_DOWN))
		m_camera.MoveForward((float)frameTime*10.0f);

	Vector2f mouseMoveDist = input.GetDistanceMouseMoved();

	if (input.IsButtonDown(Input::MBUTTON_RIGHT))
	{
		if (mouseMoveDist.X() != 0.0f)
		{
			m_camera.RotateYaw(mouseMoveDist.X()/300.0f);
		}

		if (mouseMoveDist.Y() != 0.0f)
		{
			m_camera.RotatePitch(mouseMoveDist.Y()/300.0f);
		}
	}
	if (input.IsButtonDown(Input::MBUTTON_LEFT))
	{
		m_rotationX += mouseMoveDist.X()/300.0f;
		m_rotationY += mouseMoveDist.Y()/300.0f;
	}

	//m_camera.MoveForward(-(float)frameTime*1.0f);
}

void Simulation::Draw()
{
	glPushMatrix();

	m_camera.SetViewMatrix();

	float lightpos [ ] = {-4 , 4 , 4,  1};
	glLightfv( GL_LIGHT0 , GL_POSITION, lightpos );

	glRotated(m_rotationX*180/MATH_PI, 0, 1, 0);
	glRotated(m_rotationY*180/MATH_PI, 1, 0, 0);

	m_model.Draw();

	glPopMatrix();
}
