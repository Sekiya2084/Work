#pragma once

#include "gameobject.h"
#include "component.h"

class Bullet : public GameObject
{
	Component* m_Component{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	
	XMFLOAT3 forward;
	std::chrono::system_clock::time_point m_StartTime;
	std::chrono::system_clock::time_point m_NowTime;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};