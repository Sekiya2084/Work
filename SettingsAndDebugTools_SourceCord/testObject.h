#pragma once


#include "gameObject.h"
#include "component.h"

class TestObject : public GameObject
{
private:

	Component* m_Component{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	ID3D11ShaderResourceView* m_EnvTexture{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};