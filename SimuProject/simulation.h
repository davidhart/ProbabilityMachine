#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "game.h"
#include "model.h"
#include "object.h"
#include "texture.h"
#include "camera.h"
#include "pointlight.h"
#include <vector>
#include "ball.h"
#include "peg.h"
#include "plane.h"
#include "planesegment.h"

#include "resourcebank.h"

#include "font.h"

class Simulation : public Game
{
private:
	double m_rotationX,m_rotationY;
	Model* m_modelMachine;
	Model* m_modelPeg;
	Object m_objectMachine;
	std::vector<Peg*> m_pegVector;
	std::vector<Plane*> m_planeVector;
	std::vector<PlaneSegment*> m_planeSegVector;
	std::vector<Ball*> m_ballVector;
	Camera m_camera;
	PointLight m_light0;
	Font m_font;

	const double m_updateFrequency;
	double m_frameTimeAccumulator;

	ResourceBank m_resources;

public: 
	Simulation();
	~Simulation();

	void Load();
	void Unload();
	void Update(const Input& input, double frameTime);
	void OnResize(int width, int height);
	void Draw();
	void DoSimulation(double timeStep);

	void SpawnBall();
};

#endif