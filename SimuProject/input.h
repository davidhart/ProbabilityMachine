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
		KEY_NUM_PLUS = VK_ADD,
		KEY_ENTER = VK_RETURN,

		KEY_F1 = VK_F1,
		KEY_F2 = VK_F2,
		KEY_F3 = VK_F3,
		KEY_F4 = VK_F4,
		KEY_F5 = VK_F5,
		KEY_F6 = VK_F6,
		KEY_F7 = VK_F7,
		KEY_F8 = VK_F8,
		KEY_F9 = VK_F9,
		KEY_F10 = VK_F10,
		KEY_F11 = VK_F11,
		KEY_F12 = VK_F12,

		KEY_W = 0x57,
		KEY_A = 0x41,
		KEY_S = 0x53,
		KEY_D = 0x44,

		KEY_0 = 0x30,
		KEY_1 = 0x31,
		KEY_2 = 0x32,
		KEY_3 = 0x33,
		KEY_4 = 0x34,
		KEY_5 = 0x35,
		KEY_6 = 0x36,
		KEY_7 = 0x37,
		KEY_8 = 0x38,
		KEY_9 = 0x39,
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