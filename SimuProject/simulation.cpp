#include "simulation.h"
#include "line2f.h"
#include "model.h"

#include <Gl/gl.h>
#include <iostream>

#include "Math.h" // PI
#include <cmath>

#include <cstdlib>

#include "icondrawer3d.h"

#include "spritebatch.h"

Simulation::Simulation() :
	m_rotationX( 0.0 ),
	m_rotationY( 0.0 ),
	m_camera(Vector3f(0, 2, 20), 0, 0, 0),
	m_updateFrequency( 1/120.0 ),
	m_frameTimeAccumulator( 0.0 ),
	m_font("Tahoma", 12, false, false),
	m_ball( NULL )
{
	m_window.SetTitle("Simulation");

	srand(0);
}

Simulation::~Simulation()
{
	for (unsigned int i = 0; i < m_pegVector.size(); i++)
	{
		delete m_pegVector[i];
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
	m_font.Load();
	m_modelMachine = m_resources.RequestModel("Resources/machine2.obj");
	m_modelPeg = m_resources.RequestModel("Resources/peg.obj");
	m_resources.RequestModel("lighticon.png");

	m_objectMachine.SetModel(m_modelMachine);

	m_pegVector.reserve(68);

	SpawnBall();	

	for (int i = 0; i < 4; i++)
	{
		Vector3f pegPosition(-3.5f, 2.5f + (float)i, 0.0f);

		for(int j = 0; j < 8; j++)
		{
			m_pegVector.push_back(new Peg(m_resources, pegPosition));
			pegPosition += Vector3f(1.0f, 0.0f, 0.0f);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		Vector3f pegPosition(-4.0f, 3.0f + (float)i, 0.0f);

		for (int j = 0; j < 9; j++)
		{
			m_pegVector.push_back(new Peg(m_resources, pegPosition));
			pegPosition += Vector3f(1.0f, 0.0f, 0.0f);
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

	Lighting::Enable();
	Light::Enable(0);

	m_light0.SetPosition(Vector3f(-4.0f , 4.0f , 4.0f));
	m_light0.SetAmbientColour(0.4f, 0.4f, 0.4f, 1.0f);
	m_light0.SetDiffuseColour(0.6f, 0.6f, 0.6f, 1.0f);
	m_light0.SetSpecularColour(0.5f, 0.5f, 0.5f, 1.0f);
}

void Simulation::Unload()
{
	m_font.Unload();

}

void Simulation::Update(const Input& input, double frameTime)
{
	float frameTimeFloat = (float)frameTime;

	Vector2f mouseMoveDist = input.GetDistanceMouseMoved();

	m_frameTimeAccumulator += frameTime;

	while(m_frameTimeAccumulator >= m_updateFrequency)
	{
		DoSimulation(m_updateFrequency);
		m_frameTimeAccumulator -= m_updateFrequency;
	}

	if (input.IsKeyJustPressed(Input::KEY_ENTER))
	{
		SpawnBall();
	}

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

	if (input.IsKeyDown(Input::KEY_A))
		m_camera.MoveStrafe(-frameTimeFloat*15.0f);

	if (input.IsKeyDown(Input::KEY_D))
		m_camera.MoveStrafe(frameTimeFloat*15.0f);

	if (input.IsKeyDown(Input::KEY_W))
		m_camera.MoveForward(-frameTimeFloat*15.0f);

	if (input.IsKeyDown(Input::KEY_S))
		m_camera.MoveForward(frameTimeFloat*15.0f);

	if (input.IsKeyDown(Input::KEY_RIGHT))
		m_camera.RotateYaw(frameTimeFloat);

	if (input.IsKeyDown(Input::KEY_LEFT))
		m_camera.RotateYaw(frameTimeFloat);

	if (input.IsKeyDown(Input::KEY_UP))
		m_camera.RotatePitch(frameTimeFloat);

	if (input.IsKeyDown(Input::KEY_DOWN))
		m_camera.RotatePitch(frameTimeFloat);

	if (input.IsKeyJustPressed(Input::KEY_F1))
		Lighting::Disable();

	if (input.IsKeyJustPressed(Input::KEY_F2))
		Lighting::Enable();

	if (input.IsKeyJustPressed(Input::KEY_F3))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	if (input.IsKeyJustPressed(Input::KEY_F4))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Simulation::DoSimulation(double timeStep)
{
	Peg* collisionPeg = NULL;

	do
	{
		m_ball->ApplyForce(Vector3f(0, -98.1f*m_ball->GetMass(), 0));	// Gravity
		m_ball->ApplyForce(m_ball->GetVelocity()*-0.02f);				// Air resistance

		if (collisionPeg != NULL)
		{
			m_ball->CollisionResponse(*collisionPeg);
			collisionPeg = NULL;
		}

		double nextCollision = timeStep;

		// test for collisions
		for (unsigned int i = 0; i < m_pegVector.size(); i++)
		{
			if (m_ball->CollisionTest(*m_pegVector[i], nextCollision))
			{
				collisionPeg = m_pegVector[i];
			}
		}

		m_ball->Update(nextCollision);

		timeStep -= nextCollision;

	} while (timeStep > 0);
}

void Simulation::Draw()
{
	glPushMatrix();

	m_camera.SetViewMatrix();

	m_light0.Apply(0);

	glPushMatrix();
	glRotated(m_rotationX*180/MATH_PI, 0, 1, 0);
	glRotated(m_rotationY*180/MATH_PI, 1, 0, 0);

	
	m_objectMachine.Draw();

	for (unsigned int i = 0; i < m_pegVector.size(); i++)
		m_pegVector[i]->Draw();

	m_ball->Draw();

	glPopMatrix();	

	IconDrawer3D icons(m_camera);
	icons.Begin();
	icons.Draw(m_light0, m_resources.RequestTexture("lighticon.png"));
	icons.End();

	SpriteBatch s(m_window);
	s.Begin();
	m_font.DrawText(s, "David Hart", Vector2f(0, 0));
	s.Draw(m_resources.RequestTexture("lighticon.png"), Vector2f(0, 64));
	//s.Draw(m_resources.RequestTexture("lighticon.png"), Vector2f(1, 0));
	s.End();

	glPopMatrix();
}

void Simulation::SpawnBall()
{
	if (m_ball != NULL) delete m_ball;

	int random = rand() % 9999;
	//int random = 499;

	m_ball = new Ball(m_resources, Vector3f((float)(random-4999.5f)/9999.0f*0.75f, 10.0f, 0.125f));
}
