#ifndef _INPUT_H
#define _INPUT_H

#include <vector>
#include <windows.h>
#include "Vector2f.h"

class Input
{
public:
	enum eKey
	{
		KEY_ESCAPE = VK_ESCAPE,
		KEY_UP = VK_UP,
		KEY_DOWN = VK_DOWN,
		KEY_LEFT = VK_LEFT,
		KEY_RIGHT = VK_RIGHT,
	};

	enum eButton
	{
		MBUTTON_LEFT = 0,
		MBUTTON_MIDDLE = 1,
		MBUTTON_RIGHT = 2,
	};
private:
	static const int KEY_ARRAY_SIZE = 256;

	typedef bool KeyboardInputState[KEY_ARRAY_SIZE];
	
	KeyboardInputState m_prevInputState;
	KeyboardInputState m_currentInputState;
	std::vector<eKey> m_changedKeys;

	static const int MOUSE_BUTTON_ARRAY_SIZE = 3;
	class MouseInputState
	{
	public:
		MouseInputState();
		Vector2f m_position;
		bool m_buttons[MOUSE_BUTTON_ARRAY_SIZE];
	};

	MouseInputState m_prevMouseInputState;
	MouseInputState m_currentMouseInputState;
	bool m_mouseInputRecieved;

public:
	Input();
	bool Callback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void UpdateTick();

	const bool IsKeyJustPressed(eKey key) const;
	const bool IsKeyJustReleased(eKey key) const;
	const bool IsKeyDown(eKey key) const;
	const bool IsKeyUp(eKey key) const;

	const bool IsButtonJustPressed(eButton button) const;
	const bool IsButtonJustReleased(eButton button) const;
	const bool IsButtonDown(eButton button) const;
	const bool IsButtonUp(eButton button) const;

	const Vector2f& GetMousePosition() const;
	const Vector2f GetDistanceMouseMoved() const;
};

#endif