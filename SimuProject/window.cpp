#include "window.h"
#include "game.h"

#include <Gl/gl.h>

Window::Window() : 
	m_game( NULL ),
	m_open ( false ),
	m_window ( NULL ),
	m_width ( 800 ),
	m_height ( 600 ),
	m_title ( "Form1" )
{

}
	
Window::~Window()
{
	if (m_open)
		Destroy();
}

bool Window::Create()
{
	if (!InitWindow())
	{
		CleanupWindow();
		return false;
	}


	if(!InitGl())
	{
		CleanupGl();
		CleanupWindow();
		return false;
	}

	m_open = true;

	m_game->OnResize(m_width, m_height);

	return true;
}

void Window::Destroy()
{
	DestroyWindow(m_window);
}

void Window::DoEvents()
{	
	MSG msg;
	while(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

bool Window::IsOpen()
{
	return m_open;
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Present()
{
	SwapBuffers(m_dc);
}

void Window::SetSize(int width, int height)
{
	if(m_open)
	{
		if (width != m_width || height != m_height)
		{
			RECT r;
			r.left = 0;
			r.top = 0;
			r.bottom = height;
			r.right = width;
			
			AdjustWindowRectEx(&r, m_winStyle, FALSE, m_winStyleEx);

			SetWindowPos(m_window, 0, 0, 0, r.right-r.left, r.bottom - r.top, SWP_NOZORDER | SWP_NOMOVE);
		}
	}
	else
	{
		m_width = width;
		m_height = height;
	}
}

void Window::GetSize(int& width, int& height) const
{
	width = m_width;
	height = m_height;
}

void Window::SetTitle(const std::string& title)
{
	m_title = title;

	if (m_open)
	{
		SetWindowTextA(m_window, m_title.c_str());
	}
}

const std::string& Window::GetTitle() const
{
	return m_title;
}

void Window::SetGame(Game* game)
{
	m_game = game;
}

LRESULT CALLBACK Window::StaticWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCCREATE)
	{
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)((LPCREATESTRUCT)lParam)->lpCreateParams);
	}
	else
	{
		Window* wnd = (Window*)GetWindowLongPtr(hWnd, GWL_USERDATA);
		if (wnd != NULL)
		{
			return wnd->WindowProc(hWnd, message, wParam, lParam);
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		Cleanup();
		return 0;

	case WM_SIZE:
		if (m_open)
		{
			RECT r;
			GetClientRect(hWnd, &r);
			m_width = r.right - r.left;
			m_height = r.bottom - r.top;
			m_game->OnResize(m_width, m_height);
			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
	
bool Window::InitWindow()
{
	ZeroMemory(&m_wc, sizeof(WNDCLASSEX));
	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.style = CS_HREDRAW | CS_VREDRAW;
	m_wc.lpfnWndProc = StaticWindowProc;
	m_wc.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND+1);
	m_wc.lpszClassName = TEXT(WINDOW_CLASS_NAME);

	if (!RegisterClassEx(&m_wc))
		return false;

	m_winStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	m_winStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = m_width;
	r.bottom = m_height;
	
	AdjustWindowRectEx(&r, m_winStyle, FALSE, m_winStyleEx);

	m_window = CreateWindowExA(m_winStyleEx,
								WINDOW_CLASS_NAME,
								m_title.c_str(),
								m_winStyle,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								r.right - r.left,
								r.bottom - r.top,
								NULL,
								NULL,
								(HINSTANCE)GetModuleHandle(NULL),
								(void*)this);

	if (m_window == NULL)
		return false;

	return true;
}

bool Window::InitGl()
{
	m_dc = GetDC(m_window);

	if (m_dc == NULL) return false;

	
	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	int pf = ChoosePixelFormat(m_dc, &pfd);

	if (pf == 0)
		return false;

	
	if (!SetPixelFormat(m_dc, pf, &pfd))
		return false;
	
	m_glrc = wglCreateContext(m_dc);
	
	if (m_glrc == NULL)
		return false;
	
	if (!wglMakeCurrent(m_dc, m_glrc))
		return false;

	return true;
}

void Window::Cleanup()
{
	CleanupGl();
	CleanupWindow();

	m_open = false;
}

void Window::CleanupWindow()
{
	m_window = NULL;

	UnregisterClass(TEXT(WINDOW_CLASS_NAME), (HINSTANCE)GetModuleHandle(NULL));
}
void Window::CleanupGl()
{
	wglDeleteContext(m_glrc);
}
