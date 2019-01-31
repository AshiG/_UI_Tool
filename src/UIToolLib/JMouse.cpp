#include "JMouse.h"
#include "Window.h"
#include "Input.h"
namespace UI
{
	void JMouse::Update(float fWidth, float fHeight)
	{
		POINT mouse;
		mouse.x = (LONG)(Input::GetCursor().x * ((float)fWidth / (float)Window::getClientRect().right));
		mouse.y = (LONG)(Input::GetCursor().y * ((float)fHeight / (float)Window::getClientRect().bottom));
		m_ptMouse.x = (LONG)(mouse.x - (fWidth / 2.0f));
		m_ptMouse.y = (LONG)((mouse.y - (fHeight / 2.0f)) * -1.0f);
	}
	POINT& JMouse::Getpt()
	{
		return m_ptMouse;
	}
}