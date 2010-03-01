#include "game.h"
#include "timer.h"

#include <GL/gl.h>

Game::Game() : 
	window()
{
	window.SetGame(this);
	window.SetSize(600, 600);
	window.SetTitle("GameWindow");
}

int Game::Run()
{
	if (!window.Create())
		return 1;

	Load();

	Timer t;

	double accumulator = 0.0;
	double tickFrequency = 1/120.0;		// 120hz simulation

	while (window.IsOpen())
	{
		t.Start();

		window.Clear();

		Draw();

		window.Present();

		window.DoEvents();

		accumulator += t.GetTime();

		while(accumulator >= tickFrequency)
		{
			Update(tickFrequency);
			accumulator -= tickFrequency;
		}

		t.Stop();
	}

	Unload();

	return 0;
}

void Game::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
}
