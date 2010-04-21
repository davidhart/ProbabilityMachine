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

	while (m_window.IsOpen())
	{
		t.Start();

		m_window.DoEvents();
		Update(m_window.GetInput(), t.GetTime());

		m_window.Clear();

		Draw();

		m_window.Present();

		t.Stop();
	}

	Unload();

	return 0;
}

void Game::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
}
