#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "game.h"
#include "model.h"
#include "object.h"
#include "texture.h"
#include "camera.h"
#include <vector>

class Simulation : public Game
{
private:
	double m_rotationX,m_rotationY;
	Model m_modelMachine;
	Model m_modelPeg;
	Object m_objectMachine;
	std::vector<Object*> m_objectPegs;
	Camera m_camera;

public: 
	Simulation();
	~Simulation();

	void Load();
	void Unload();
	void Update(const Input& input, double frameTime);
	void OnResize(int width, int height);
	void Draw();
};

#endif