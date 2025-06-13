#pragma once

#include "gameobject.h"
#include "component.h"

class Enemy : public GameObject
{
	Component* m_Component{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};