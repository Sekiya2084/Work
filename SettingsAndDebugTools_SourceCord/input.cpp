
#include "main.h"
#include "input.h"
#include "winuser.h"


BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];

POINT Input::m_MouseStart;
POINT Input::m_MouseNow; 


void Input::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
	GetCursorPos(&m_MouseStart);

}

void Input::Uninit()
{


}

void Input::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );

	GetCursorPos(&m_MouseNow);
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

float Input::GetMousePointX()
{
	return (m_MouseNow.x - m_MouseStart.x);
}
float Input::GetMousePointY()
{
	return (m_MouseNow.y - m_MouseStart.y);
}