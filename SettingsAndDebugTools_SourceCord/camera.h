#pragma once
#include "gameobject.h"

class Camera : public GameObject
{
private:
	XMFLOAT3 m_Target;
	XMFLOAT3 LookAt;
	XMFLOAT4X4 m_ViewMatrix;
	float oldposx;
	float m_RotXMax = 1.0f;
	float m_RotXMin = -1.0f;
	float m_DeadZone = 3.0f;
	float m_Sensi = 0.005;

	float i_Sensi = 0;

	bool m_CursorTrigger = false;
	int CursorInfo = 0;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	XMMATRIX GetViewMatrix()
	{
		return XMLoadFloat4x4(&m_ViewMatrix);
	}

	bool CheckView(XMFLOAT3 Position);
	bool GetCursorEnable();
};
