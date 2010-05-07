#ifndef _SIMULATION_H
#define _SIMULATION_H

#include <vector>
#include "game.h"
#include "model.h"
#include "object.h"
#include "texture.h"
#include "camera.h"
#include "pointlight.h"
#include "ball.h"
#include "peg.h"
#include "plane.h"
#include "planesegment.h"

#include "spritebatch.h"

#include "resourcebank.h"
#include "icancollidewithball.h"

#include "font.h"
#include "timer.h"

class Simulation : public Game
{
private:
	Model* m_modelMachine;
	Model* m_modelGlass;
	std::vector<Peg*> m_pegVector;
	std::vector<ICanCollideWithBall*> m_obstacles;
	Plane* m_floor;
	std::vector<Ball*> m_ballVector;

	enum eCameraMode
	{
		CAMERA_MODE_FIXED,
		CAMERA_MODE_USER,
		CAMERA_MODE_BALL,
	};
	eCameraMode m_cameraMode;

	Camera m_userCamera;
	Vector2f m_userCamSimRotation;

	Camera m_trackingCamera;
	Ball* m_trackedBall;

	Camera m_fixedCamera;

	PointLight m_light0;
	
	ResourceBank m_resources;
	SpriteBatch m_spriteBatch;
	Font m_font;

	Timer m_timeBetweenRenders;

	int m_ballsDropped;
	int m_ballsCollected[9];

	float m_simSpeed;

	const double m_updateFrequency;
	const unsigned int m_maxBalls;
	double m_frameTimeAccumulator;

public: 
	Simulation();
	~Simulation();

	void Load();
	void Unload();
	void Update(const Input& input, double frameTime);
	void OnResize(int width, int height);
	void DoSimulation(double timeStep);
	
	void Draw();
	void DrawGraph3D();
	void DrawGraph2D();

	void SpawnBall();
	void Reset();
};

#endif