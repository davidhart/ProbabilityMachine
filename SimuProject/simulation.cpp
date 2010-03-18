#include "simulation.h"
#include "line2f.h"
#include "model.h"

#include <Gl/gl.h>
#include <iostream>

#include "Math.h" // PI
#include <cmath>

Simulation::Simulation() :
	m_rotation( 0.0 ),
	m_model("Resources/plane.obj"),
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

void Simulation::Update(const Input& input, double frameTime)
{
	m_rotation += frameTime*100.0;
	if (m_rotation > 360)
		m_rotation -= 360;

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
			//std::cout << "X:" << mouseMoveDist.X() << std::endl;
		}

		if (mouseMoveDist.Y() != 0.0f)
		{
			m_camera.RotatePitch(mouseMoveDist.Y()/300.0f);
			//std::cout << "Y:" << mouseMoveDist.Y() << std::endl;
		}
	}

	//m_camera.MoveForward(-(float)frameTime*1.0f);
}

void Simulation::Draw()
{
	glPushMatrix();

	m_camera.SetViewMatrix();

	//glRotated(m_rotation, 1.0f, 1.0f, 0.0f);

	m_model.Draw();

	glPopMatrix();
}
