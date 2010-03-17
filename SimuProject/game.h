#ifndef _GAME_H
#define _GAME_H

#include "window.h"

class Game
{
	friend class Window;

protected:
	Window m_window;

public:
	Game();
	int Run();

protected:
	virtual void Update(const Input& input, double frameTime) = 0;
	virtual void Draw() = 0;

	virtual void Load() = 0;
	virtual void Unload() = 0;

	virtual void OnResize(int width, int height);
};

#endif