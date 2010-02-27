#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "game.h"

class Simulation : public Game
{
private:
	double m_rotation;

public: 
	Simulation();

	void Load();
	void Unload();
	void Update(double frameTime);
	void OnResize(int width, int height);
	void Draw();
};

#endif