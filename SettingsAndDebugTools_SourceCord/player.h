#pragma once

#include "gameobject.h"
#include "component.h"
#include "bullet.h"
#include "audio.h"
#include "string"

#define MAXSPEED (0.3)
#define MINSPEED (0.1)

class Player : public GameObject
{
	Component* m_Component{};
	Component* m_ChildModel{};

	bool m_JampTrigger;
	float m_JampPower;
	float m_Velocity;
	float m_Speed;
	float m_MaxSpeed;
	float m_MinSpeed;

	float i_Speed;
	float i_MaxSpeed;
	float i_MinSpeed;
	float i_Jamp;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_AnimationFrame;
	std::string m_AnimationName1;
	std::string m_AnimationName2;
	float m_AnimationBlendRatio;
	class Audio* m_SE;

	bool m_Fadebool = false;

	XMFLOAT4 m_Quaternion;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};