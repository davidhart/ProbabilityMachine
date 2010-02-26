#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "game.h"

class Simulation : public Game
{
public: 
	Simulation();

	void Load();
	void Unload();
	void Update(double frameTime);
	void Draw();
};

#endif