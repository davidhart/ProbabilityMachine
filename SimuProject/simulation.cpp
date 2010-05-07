#include "simulation.h"
#include "line2f.h"
#include "model.h"

#include <Gl/gl.h>
#include <iostream>

#include "Math.h"	// PI
#include <cmath>	// tan, floor
#include <cstdlib>	// rand, srand
#include <ctime>	// time
#include <sstream>

Simulation::Simulation() :
	m_updateFrequency ( 1/80.0 ),
	m_maxBalls ( 20 ),
	m_frameTimeAccumulator ( 0.0 ),
	m_font ("Tahoma", 12, false, false),
	m_cameraMode ( CAMERA_MODE_FIXED ),
	m_userCamera ( Vector3f(0, 3.5f, 16), 0, 0, 0 ),
	m_userCamSimRotation ( Vector2f(0, 0) ),
	m_fixedCamera ( Vector3f(0, 3.5f, 16), 0, 0, 0 ),
	m_trackingCamera ( Vector3f(0, 3.5f, 6), 0, 0, 0 ),
	m_trackedBall ( NULL ),
	m_spriteBatch ( m_window ),
	m_simSpeed ( 1.0f )
{
	m_window.SetTitle("08241 Simulation and Rendering ACW - David Hart (#200879078)");

	m_timeBetweenRenders.Start();

	Reset();

	srand((unsigned int)time(NULL));
}

Simulation::~Simulation()
{
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		delete m_obstacles[i];

	for (unsigned int i = 0; i < m_ballVector.size(); i++)
		delete m_ballVector[i];
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

	// Get models for machine
	m_modelMachine = m_resources.RequestModel("Resources/machine2.obj");
	m_modelGlass = m_resources.RequestModel("Resources/machineglass.obj");

	m_obstacles.reserve(92); // 92 obstacles will be created

	m_floor = new Plane(Vector3f(0,1,0), Vector3f(0, 0.5f, 0)); // bottom
	m_obstacles.push_back(m_floor);  
	m_obstacles.push_back(new Plane(Vector3f(1,0,0), Vector3f(-4.5f, 0, 0))); // left
	m_obstacles.push_back(new Plane(Vector3f(-1,0,0), Vector3f(4.5f, 0, 0))); // right
	m_obstacles.push_back(new Plane(Vector3f(0,-1,0), Vector3f(0, 6.5f, 0))); // top
	m_obstacles.push_back(new Plane(Vector3f(0,0,1), Vector3f(0,0,0))); // back
	m_obstacles.push_back(new Plane(Vector3f(0,0,-1), Vector3f(0,0,1))); // front

	// Shute walls
	m_obstacles.push_back(new PlaneSegment(Vector3f(1,0,0), Vector3f(-0.5f, 7.0f, 0), 
		Vector3f(-0.5f, 6+7.0f, 0), Vector3f(-0.5f, 7.0f, 1)));
	m_obstacles.push_back(new PlaneSegment(Vector3f(-1,0,0), Vector3f(0.5f, 7.0f, 0), 
		Vector3f(0.5f, 6+7.0f, 0), Vector3f(0.5f, 7.0f, 1)));

	// Bucket dividers
	const float dividerHeight = 2.4f, dividerWidth = 1.0f;
	for (float dividerPos = -3.5f; dividerPos <= 3.5f; dividerPos += 1.0f)
	{
		m_obstacles.push_back(new PlaneSegment(Vector3f(1,0,0), Vector3f(dividerPos+0.05f, 0, 0), 
			Vector3f(dividerPos+0.05f, dividerHeight, 0), Vector3f(dividerPos+0.05f, 0, dividerWidth)));
		m_obstacles.push_back(new PlaneSegment(Vector3f(-1,0,0), Vector3f(dividerPos-0.05f, 0, 0), 
			Vector3f(dividerPos-0.05f, dividerHeight, 0), Vector3f(dividerPos-0.05f, 0, dividerWidth)));
	}

	// Pegs
	for (int i = 0; i < 4; i++)
	{
		Vector3f pegPosition(-3.5f, 2.5f + (float)i, 0.0f);

		for(int j = 0; j < 8; j++)
		{
			Peg* p = new Peg(m_resources, pegPosition);
			m_obstacles.push_back(p);
			m_pegVector.push_back(p);
			pegPosition += Vector3f(1.0f, 0.0f, 0.0f);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		Vector3f pegPosition(-4.0f, 3.0f + (float)i, 0.0f);

		for (int j = 0; j < 9; j++)
		{
			Peg* p = new Peg(m_resources, pegPosition);
			m_obstacles.push_back(p);
			m_pegVector.push_back(p);
			pegPosition += Vector3f(1.0f, 0.0f, 0.0f);
		}
	}

	m_resources.Load();

	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);

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

	// Handle input
	if (input.IsKeyJustPressed(Input::KEY_1))
	{
		SpawnBall();
	}
	
	if (input.IsKeyDown(Input::KEY_2))
	{
		SpawnBall();
	}

	if (input.IsKeyJustPressed(Input::KEY_F1))
		m_cameraMode = CAMERA_MODE_FIXED;

	if (input.IsKeyJustPressed(Input::KEY_F2))
		m_cameraMode = CAMERA_MODE_USER;

	if (input.IsKeyJustPressed(Input::KEY_F3))
		m_cameraMode = CAMERA_MODE_BALL;

	if (input.IsKeyJustPressed(Input::KEY_R))
	{
		Reset();
	}

	if (input.IsKeyJustPressed(Input::KEY_NUM_MINUS))
	{
		m_simSpeed -= 0.1f;
		if (m_simSpeed < 0.0f)
			m_simSpeed = 0.0f;
	}
	if (input.IsKeyJustPressed(Input::KEY_NUM_PLUS))
	{
		m_simSpeed += 0.1f;
		if (m_simSpeed > 1.0f)
			m_simSpeed = 1.0f;
	}

	if (m_cameraMode == CAMERA_MODE_USER)
	{
		Vector2f mouseMoveDist = input.GetDistanceMouseMoved();

		if (input.IsButtonDown(Input::MBUTTON_RIGHT))
		{
			if (mouseMoveDist.X() != 0.0f) m_userCamera.RotateYaw(mouseMoveDist.X()/300.0f);
			if (mouseMoveDist.Y() != 0.0f) m_userCamera.RotatePitch(mouseMoveDist.Y()/300.0f);
		}

		if (input.IsButtonDown(Input::MBUTTON_LEFT))
		{
			m_userCamSimRotation += Vector2f(mouseMoveDist.X()/300.0f, mouseMoveDist.Y()/300.0f);
		}

		if (input.IsKeyDown(Input::KEY_W))
			m_userCamera.MoveForward(-frameTimeFloat*15.0f);

		if (input.IsKeyDown(Input::KEY_S))
			m_userCamera.MoveForward(frameTimeFloat*15.0f);
		
		if (input.IsKeyDown(Input::KEY_A))
			m_userCamera.MoveStrafe(-frameTimeFloat*15.0f);

		if (input.IsKeyDown(Input::KEY_D))
			m_userCamera.MoveStrafe(frameTimeFloat*15.0f);

		if (input.IsKeyDown(Input::KEY_RIGHT))
			m_userCamera.RotateYaw(frameTimeFloat);

		if (input.IsKeyDown(Input::KEY_LEFT))
			m_userCamera.RotateYaw(-frameTimeFloat);

		if (input.IsKeyDown(Input::KEY_UP))
			m_userCamera.RotatePitch(-frameTimeFloat);

		if (input.IsKeyDown(Input::KEY_DOWN))
			m_userCamera.RotatePitch(frameTimeFloat);
	}

	if (input.IsKeyJustPressed(Input::KEY_F5))
		Lighting::Disable();

	if (input.IsKeyJustPressed(Input::KEY_F6))
		Lighting::Enable();

	if (input.IsKeyJustPressed(Input::KEY_F7))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	if (input.IsKeyJustPressed(Input::KEY_F8))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Update simulation
	if (m_simSpeed > 0)
	{
		m_frameTimeAccumulator += frameTime*m_simSpeed;

		while(m_frameTimeAccumulator >= m_updateFrequency*m_simSpeed)
		{
			DoSimulation(m_updateFrequency*m_simSpeed);
			m_frameTimeAccumulator -= m_updateFrequency*m_simSpeed;
		}
	}
}

void Simulation::DoSimulation(double timeStep)
{
	// Balls that must be erased at the end of the timestep, as they have
	// collided with the floor plane
	std::vector<Ball*> ballsToErase;

	// Struct to hold details about collisions
	struct Collision
	{
		Collision (ICanCollideWithBall* collisionTarget, Ball* collisionBall, double time) : 
			collisionTarget(collisionTarget),
			collisionBall( collisionBall),
			time(time)
			{}
		ICanCollideWithBall* collisionTarget;
		Ball* collisionBall;
		double time;
	};

	// Vector of collisions that happen in the next timeslice
	std::vector<Collision> collisions;

	do
	{
		double nextCollision = timeStep;

		// Check for collisions happening to each ball in the current timeslice
		for (unsigned int b = 0; b < m_ballVector.size(); b++)
		{
			m_ballVector[b]->ApplyForce(Vector3f(0, -98.1f*m_ballVector[b]->GetMass(), 0));	// Gravity
			m_ballVector[b]->ApplyForce(m_ballVector[b]->GetVelocity()*-0.02f);				// Air resistance

			// Check for collisions with other balls
			for (unsigned int i = b+1; i < m_ballVector.size(); i++)
			{
				double nextCollisionTemp = nextCollision;

				if (m_ballVector[i]->CollisionTest(*m_ballVector[b], nextCollisionTemp))
				{
					// Apply collision response to any collisions happening now, 
					// otherwise record the time the collision happens
					if (nextCollisionTemp == 0.0f)
					{
						m_ballVector[i]->CollisionResponse(*m_ballVector[b]);
					}
					else
					{
						collisions.push_back(Collision(m_ballVector[i],m_ballVector[b],nextCollisionTemp));
					}
				}
			}

			// Check for collisions with obstacles
			for (unsigned int i = 0; i < m_obstacles.size(); i++)
			{
				double nextCollisionTemp = nextCollision;

				if (m_obstacles[i]->CollisionTest(*m_ballVector[b], nextCollisionTemp))
				{
					// Apply collision response to any collisions happening now,
					// otherwise record the time the collision happens
					if (nextCollisionTemp == 0.0f)
					{
						m_obstacles[i]->CollisionResponse(*m_ballVector[b]);
						if (m_obstacles[i] == m_floor)
							ballsToErase.push_back(m_ballVector[b]);
					}
					else
					{
						collisions.push_back(Collision(m_obstacles[i],m_ballVector[b],nextCollisionTemp));
					}
				}
			}
		}

		// if there are collisions, update all objects to the earliest collision
		if (!collisions.empty())
			nextCollision = collisions[collisions.size()-1].time;

		for (unsigned int b = 0; b < m_ballVector.size(); b++)
			m_ballVector[b]->Update(nextCollision);

		// for each simultaneous collsion happening at the current instant of time
		// reslove it
		for (int c = collisions.size() - 1; c > 0; c--)
		{
			if (collisions[c].time < nextCollision)
				break;

			collisions[c].collisionTarget->CollisionResponse(*collisions[c].collisionBall);

			// if the collision is with the floor, add the ball to be deleted
			if (collisions[c].collisionTarget == m_floor)
				ballsToErase.push_back(collisions[c].collisionBall);
		}
		// discard all collisions, including ones that have not had response applied, as
		// they need to be re-checked
		collisions.clear();

		// delete all the balls that need to be deleted
		for (unsigned int i = 0; i < ballsToErase.size(); i++)
		{
			// loop through ball vector to find it
			for (unsigned int b = 0; b < m_ballVector.size(); b++)
			{
				if (ballsToErase[i] == m_ballVector[b])
				{
					// when we've found it, remove from ball vector
					m_ballVector.erase(std::vector<Ball*>::iterator(&m_ballVector[b], &m_ballVector));

					// work out what divider it's in so we can increase that stat
					int dividerPos = 0;
					for (; dividerPos < 8; dividerPos++)
					{
						if (ballsToErase[i]->GetPosition().X() < (-3.5f+(float)dividerPos))
						{
							m_ballsCollected[dividerPos]++;
							break;
						}
					}
					if (dividerPos >= 8)
					{
						m_ballsCollected[8]++;
					}

					// if the deleted ball is being tracked by the camera, stop tracking it
					if (m_trackedBall == ballsToErase[i])
						m_trackedBall = NULL;

					delete ballsToErase[i];
					break;
				}
			}
		}
		ballsToErase.clear();

		// we have updated to the next collision, so shrink the timestep
		timeStep -= nextCollision;

	} while (timeStep > 0);
}

void Simulation::Draw()
{
	m_timeBetweenRenders.Stop();
	m_timeBetweenRenders.Start();
	glPushMatrix();

	if (m_cameraMode == CAMERA_MODE_USER)
		m_userCamera.SetViewMatrix();
	else if (m_cameraMode == CAMERA_MODE_FIXED)
		m_fixedCamera.SetViewMatrix();
	else
	{
		if (m_trackedBall != NULL)
			m_trackingCamera.Position(Vector3f(m_trackedBall->GetPosition().X(), 
				m_trackedBall->GetPosition().Y(), m_trackingCamera.Position().Z()));

		m_trackingCamera.SetViewMatrix();
	}

	m_light0.Apply(0);

	glPushMatrix();

	if (m_cameraMode == CAMERA_MODE_USER)
	{
		glRotated(m_userCamSimRotation.X()*180/MATH_PI, 0, 1, 0);
		glRotated(m_userCamSimRotation.Y()*180/MATH_PI, 1, 0, 0);
	}
	
	m_modelMachine->Draw();

	for (unsigned int i = 0; i < m_pegVector.size(); i++)
		m_pegVector[i]->Draw();

	for (unsigned int i = 0; i < m_ballVector.size(); i++)
		m_ballVector[i]->Draw();

	DrawGraph3D();

	m_modelGlass->Draw();


	glPopMatrix();	

	std::stringstream ss;
	ss.setf(std::ios_base::floatfield, std::ios_base::fixed);
	ss.precision(2);
	ss << "David Hart (#200879078)\n08241 Simulation and Rendering";

	m_spriteBatch.Begin();

	int windoww, windowh;
	m_window.GetSize(windoww, windowh);

	m_font.DrawText(m_spriteBatch, ss.str(), Vector2f(1, 0));

	ss.str(std::string());
	ss << "fps: " << 1/m_timeBetweenRenders.GetTime() << "\n" <<
		"Dropped: " << m_ballsDropped << "\n" <<
		"Active: " << m_ballVector.size() << "/" << m_maxBalls << "\n" <<
		"Sim Speed: " << m_simSpeed << "x";
	
	m_font.DrawText(m_spriteBatch, ss.str(), Vector2f((float)windoww-3,0), Font::ALIGNMENT_RIGHT); 

	ss.str(std::string());
	if (m_cameraMode == CAMERA_MODE_FIXED)
		ss << "FIXED CAMERA";
	else if (m_cameraMode == CAMERA_MODE_BALL)
		ss << "BALL-TRACKING CAMERA";
	else 
		ss << "USER CAMERA";

	m_font.DrawText(m_spriteBatch, ss.str(), Vector2f(floor((float)windoww/2), 0), Font::ALIGNMENT_CENTER);

	DrawGraph2D();

	m_spriteBatch.End();

	glPopMatrix();
}

void Simulation::DrawGraph2D()
{
	int totalCollected = m_ballsDropped - m_ballVector.size();

	if (totalCollected > 0)
	{
		std::stringstream ss;
		for (int i = 0; i < 9; i++)
		{
			ss << m_ballsCollected[i] << "(" << (int)((float)m_ballsCollected[i]/totalCollected*100.0f) << "%)   ";
		}

		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

		int windoww, windowh;
		m_window.GetSize(windoww, windowh);

		float graphLineWidth = (float)windoww/9;
		float graphLineMaxHeight = (float)windowh/5;

		glColor4f(0.85f, 0.227f, 0.227f, 0.5f);

		for (int i = 0; i < 9; i++)
		{
			float height = (float)m_ballsCollected[i]/totalCollected * graphLineMaxHeight;
			glVertex2f(i*graphLineWidth, (float)windowh-height);
			glVertex2f(i*graphLineWidth, (float)windowh);
			glVertex2f(i*graphLineWidth+graphLineWidth, (float)windowh);
			glVertex2f(i*graphLineWidth+graphLineWidth, (float)windowh-height);
		}

		glEnd();
		glEnable(GL_TEXTURE_2D);

		glColor3f(1.0f, 1.0f, 1.0f);

		for (int i = 0; i < 9; i++)
		{
			ss.str(std::string());
			ss << m_ballsCollected[i] << "\n(" << (int)((float)m_ballsCollected[i]/totalCollected*100.0f) << "%)";
			Vector2f size = m_font.MeasureString(ss.str());
			m_font.DrawText(m_spriteBatch, ss.str(), Vector2f(floor(i*graphLineWidth+graphLineWidth/2), 
				floor(windowh-size.Y()-3)), Font::ALIGNMENT_CENTER);
		}
	}
}

void Simulation::DrawGraph3D()
{
	int totalCollected = m_ballsDropped - m_ballVector.size();

	if (totalCollected > 0)
	{
		glPushAttrib(GL_LIGHTING_BIT | GL_TEXTURE_BIT);
		Lighting::Disable();
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glColor4f(0.85f, 0.227f, 0.227f, 0.5f);
		for (int i = 0; i < 9; i++)
		{
			float height = (float)m_ballsCollected[i]/totalCollected * 2.0f;
			glVertex3f(i*1.0f-4.45f, height+0.5f, 1.125f);
			glVertex3f(i*1.0f-4.45f, 0.5f, 1.125f);
			glVertex3f(i*1.0f-3.55f, 0.5f, 1.125f);
			glVertex3f(i*1.0f-3.55f, height+0.5f, 1.125f);
		}
		glEnd();

		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
		for (int i = 0; i < 9; i++)
		{
			float height = (float)m_ballsCollected[i]/totalCollected * 2.0f;
			glBegin(GL_LINE_LOOP);
			glVertex3f(i*1.0f-4.44f, height+0.5f, 1.12501f);
			glVertex3f(i*1.0f-4.44f, 0.5f, 1.12501f);
			glVertex3f(i*1.0f-3.55f, 0.5f, 1.12501f);
			glVertex3f(i*1.0f-3.55f, height+0.5f, 1.12501f);
			glEnd();
		}

		glColor3f(1.0f, 1.0f, 1.0f);

		glPopAttrib();
	}
}

void Simulation::SpawnBall()
{
	if (m_ballVector.size() < m_maxBalls)
	{
		int randomX = rand() % 9999;
		int randomY = rand() % 9999;
		int randomZ = rand() % 9999;
		Ball * b = new Ball(m_resources, 
			Vector3f((float)(randomX-4999.5f)/9999.0f*0.75f, 
			8.0f+(float)(randomY-4999.5f)/9999.0f*0.75f, 
			0.126f+(float)(randomZ)/9999.0f*0.75f));
		m_ballVector.push_back(b);
		m_trackedBall = b;

		m_ballsDropped++;
	}
}

void Simulation::Reset()
{
	m_trackedBall = NULL;
	for (unsigned int i = 0; i < m_ballVector.size(); i++)
		delete m_ballVector[i];
	m_ballVector.clear();
	m_ballsDropped = 0;
	for (int i = 0; i < 9; i++) m_ballsCollected[i] = 0;
}