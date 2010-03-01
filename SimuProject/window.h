#ifndef _WINDOW_H
#define _WINDOW_H

#include <windows.h>
#include <string>

class Game;

class Window
{
private:
	HWND m_window;
	WNDCLASSEX m_wc;
	DWORD m_winStyle;
	DWORD m_winStyleEx;

	HDC m_dc;
	HGLRC m_glrc;

	bool m_open;
	int m_width,m_height;
	std::string m_title;

	Game* m_game;
	
#define WINDOW_CLASS_NAME "windowclass"

public:
	Window();
	~Window();

	bool Create();
	void Destroy();

	void DoEvents();
	bool IsOpen();

	void Clear();
	void Present();
	
	void SetSize(int width, int height);
	void GetSize(int& width, int& height) const;

	void SetTitle(const std::string& title);
	const std::string& GetTitle() const;
	void SetGame(Game* game);

private:
	static LRESULT CALLBACK StaticWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool InitWindow();
	bool InitGl();

	void Cleanup();
	void CleanupWindow();
	void CleanupGl();

	Window& operator=( const Window& );
};

#endif