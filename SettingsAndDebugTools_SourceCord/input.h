#pragma once


class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static POINT m_MouseStart;
	static POINT m_MouseNow;

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	static float GetMousePointX();
	static float GetMousePointY();

	static void SetStartPoint(POINT stac);
	static void SetNowPoint();

};
