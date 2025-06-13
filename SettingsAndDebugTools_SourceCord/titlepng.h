#pragma once
#include "gameobject.h"
#include "audio.h"

class Titlepng : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_alpha;
	bool m_test;
	bool m_Firstloop = true;
	bool m_fadeIn = true;

	class Audio* m_BGM{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};