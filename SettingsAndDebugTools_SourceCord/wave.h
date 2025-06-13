#pragma once
#include "gameobject.h"


class Wave : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_EnvTexture{};

	ID3D11InputLayout* m_VertexLayout{};
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};

	VERTEX_3D m_Vertex[21][21];

	float m_Time{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	float GetHeight(XMFLOAT3 Position);
};