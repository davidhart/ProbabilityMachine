#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "game.h"
#include "model.h"
#include "texture.h"

class Simulation : public Game
{
private:
	double m_rotation;
	Model m_model;
	Texture m_texture;
public: 
	Simulation();

	void Load();
	void Unload();
	void Update(double frameTime);
	void OnResize(int width, int height);
	void Draw();
};

#endif