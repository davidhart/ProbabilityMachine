#include "game.h"
#include "timer.h"

#include <GL/gl.h>

Game::Game() : 
	m_window()
{
	m_window.SetGame(this);
	m_window.SetSize(600, 600);
	m_window.SetTitle("GameWindow");
}

int Game::Run()
{
	if (!m_window.Create())
		return 1;

	Load();

	Timer t;

	double accumulator = 0.0;
	double tickFrequency = 1/120.0;		// 120hz simulation

	while (m_window.IsOpen())
	{
		t.Start();

		m_window.Clear();

		Draw();

		m_window.Present();

		
		accumulator += t.GetTime();

		while(accumulator >= tickFrequency)
		{
			m_window.DoEvents();
			Update(m_window.GetInput(), tickFrequency);
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
