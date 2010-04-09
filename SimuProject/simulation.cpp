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
	m_camera(Vector3f(0, 2, 20), 0, 0, 0)
{
	m_window.SetTitle("Simulation");
}

Simulation::~Simulation()
{
	for (unsigned int i = 0; i < m_objectPegs.size(); i++)
	{
		delete m_objectPegs[i];
	}

	delete m_ball;
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
	
}

void Simulation::Load()
{
	m_modelMachine = m_resources.RequestModel("Resources/machine2.obj");
	m_modelPeg = m_resources.RequestModel("Resources/peg.obj");

	m_objectMachine.SetModel(m_modelMachine);

	m_objectPegs.reserve(68);

	m_ball = new Ball(&m_resources, Vector3f(0.0f, 10.0f, 0.0f));

	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			Object * o = new Object();
			o->SetModel(m_modelPeg);
			o->SetPosition(Vector3f(-3.5f + j * 1.0f, i*1.0f + 2.5f, 0.0f));
			m_objectPegs.push_back(o);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Object * o = new Object();
			o->SetModel(m_modelPeg);
			o->SetPosition(Vector3f(-4.0f + j * 1.0f, i*1.0f + 3.0f, 0.0f));
			m_objectPegs.push_back(o);
		}
	}

	m_resources.Load();

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_CULL_FACE);

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
		if (mouseMoveDist.X() != 0.0f) m_camera.RotateYaw(mouseMoveDist.X()/300.0f);
		if (mouseMoveDist.Y() != 0.0f) m_camera.RotatePitch(mouseMoveDist.Y()/300.0f);
	}

	if (input.IsButtonDown(Input::MBUTTON_LEFT))
	{
		m_rotationX += mouseMoveDist.X()/300.0f;
		m_rotationY += mouseMoveDist.Y()/300.0f;
	}

	m_ball->Update(frameTime);

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

	m_objectMachine.Draw();

	for (unsigned int i = 0; i < m_objectPegs.size(); i++)
	{
		m_objectPegs[i]->Draw();
	}

	m_ball->Draw();

	glPopMatrix();
}
