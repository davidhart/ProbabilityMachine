#include "input.h"

Input::MouseInputState::MouseInputState() :
	m_position(0,0)
{
	for (int i = 0; i < MOUSE_BUTTON_ARRAY_SIZE; i++)
	{
		m_buttons[i] = false;
	}
}

Input::Input()
{
	for (int i = 0; i < KEY_ARRAY_SIZE; i++)
	{
		m_currentInputState[i] = false;
		m_prevInputState[i] = false;
	}
	m_mouseInputRecieved = false;
}

bool Input::Callback(HWND, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_KEYDOWN:
		if (wParam > 0 && wParam < KEY_ARRAY_SIZE)
		{
			m_currentInputState[wParam] = true;
			m_changedKeys.push_back((eKey)wParam);
		}
		break;

	case WM_KEYUP:
		if (wParam > 0 && wParam < KEY_ARRAY_SIZE)
		{
			m_currentInputState[wParam] = false;
			m_changedKeys.push_back((eKey)wParam);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINTS p = MAKEPOINTS(lParam);
			m_currentMouseInputState.m_position.SetX((float)p.x);
			m_currentMouseInputState.m_position.SetY((float)p.y);
			m_mouseInputRecieved = true;
		}
		break;

	case WM_LBUTTONDOWN:
		m_currentMouseInputState.m_buttons[MBUTTON_LEFT] = true;
		m_mouseInputRecieved = true;
		break;
	case WM_LBUTTONUP:
		m_currentMouseInputState.m_buttons[MBUTTON_LEFT] = false;
		m_mouseInputRecieved = true;
		break;
	case WM_RBUTTONDOWN:
		m_currentMouseInputState.m_buttons[MBUTTON_RIGHT] = true;
		m_mouseInputRecieved = true;
		break;
	case WM_RBUTTONUP:
		m_currentMouseInputState.m_buttons[MBUTTON_RIGHT] = false;
		m_mouseInputRecieved = true;
		break;
	case WM_MBUTTONDOWN:
		m_currentMouseInputState.m_buttons[MBUTTON_MIDDLE] = true;
		m_mouseInputRecieved = true;
		break;
	case WM_MBUTTONUP:
		m_currentMouseInputState.m_buttons[MBUTTON_MIDDLE] = false;
		m_mouseInputRecieved = true;
		break;
	}
	return false;
}

void Input::UpdateTick()
{
	std::vector<eKey>::iterator i = m_changedKeys.begin();

	while (i != m_changedKeys.end())
	{
		m_prevInputState[*i] = m_currentInputState[*i];
		i++;
	}

	m_changedKeys.clear();

	if (m_mouseInputRecieved)
	{
		m_prevMouseInputState = m_currentMouseInputState;
		m_mouseInputRecieved = false;
	}
}

const bool Input::IsKeyJustPressed(eKey key) const
{
	if (key < 0 || key > KEY_ARRAY_SIZE)
		return false;

	return !m_prevInputState[key] && m_currentInputState[key];
}

const bool Input::IsKeyJustReleased(eKey key) const
{
	if (key < 0 || key > KEY_ARRAY_SIZE)
		return false;

	return m_prevInputState[key] && !m_currentInputState[key];
}

const bool Input::IsKeyDown(eKey key) const
{
	if (key < 0 || key > KEY_ARRAY_SIZE)
		return false;

	return m_currentInputState[key];
}

const bool Input::IsKeyUp(eKey key) const
{
	if (key < 0 || key > KEY_ARRAY_SIZE)
		return false;

	return !m_currentInputState[key];
}

const bool Input::IsButtonJustPressed(eButton button) const
{
	return m_currentMouseInputState.m_buttons[button] && !m_prevMouseInputState.m_buttons[button];
}

const bool Input::IsButtonJustReleased(eButton button) const
{
	return !m_currentMouseInputState.m_buttons[button] && m_prevMouseInputState.m_buttons[button];
}

const bool Input::IsButtonDown(eButton button) const
{
	return m_currentMouseInputState.m_buttons[button];
}

const bool Input::IsButtonUp(eButton button) const
{
	return !m_currentMouseInputState.m_buttons[button];
}

const Vector2f& Input::GetMousePosition() const
{
	return m_currentMouseInputState.m_position;
}

const Vector2f Input::GetDistanceMouseMoved() const
{
	Vector2f temp (m_currentMouseInputState.m_position - m_prevMouseInputState.m_position);
	return temp;
}
