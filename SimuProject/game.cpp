#include "game.h"
#include "timer.h"

#include <GL/gl.h>

Game::Game() : 
	window(*this)
{
	window.SetSize(800, 600);
	window.SetTitle("GameWindow");
}

int Game::Run()
{
	if (!window.Create())
		return 1;

	Load();

	Timer t;

	while (window.IsOpen())
	{
		t.Start();

		window.Clear();

		Draw();

		window.Present();

		window.DoEvents();

		Update(t.GetTime());

		t.Stop();
	}

	Unload();

	return 0;
}

void Game::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
}
