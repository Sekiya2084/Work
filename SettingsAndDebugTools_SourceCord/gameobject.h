#pragma once
#define MAX_GAMEOBJECT 5
#include <chrono>

class GameObject
{
protected:
	XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	float m_Volume = 1.0f;
	//std::string m_State = "none";

	bool m_Destroy = false;

public:
	virtual ~GameObject() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	XMFLOAT3 GetPosition() { return m_Position; }
	XMFLOAT3 GetRotation() { return m_Rotation; }
	XMFLOAT3 GetScale() { return m_Scale; }
	float GetVolume() { return m_Volume; }
	//std::string GetState() { return m_State; }

	void SetPosition(XMFLOAT3 Position) { m_Position = Position; }
	void SetRotation(XMFLOAT3 Rotation) { m_Rotation = Rotation; }
	void SetScale(XMFLOAT3 Scale) { m_Scale = Scale; }
	void SetVolume(float Volume) { m_Volume = Volume; }
	//void SetState(std::string State) { m_State = State; }

	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	XMFLOAT3 GetForward()//前方向ベクトル取得
	{
		//オイラー角から回転行列を生成
		XMMATRIX rotationMatrix; //floatが16個入ったマトリクス
		rotationMatrix = XMMatrixRotationRollPitchYaw
		(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		XMFLOAT3 forward;
		XMStoreFloat3(&forward, rotationMatrix.r[2]);
		return forward;
	}

	XMFLOAT3 GetRight()
	{
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw
		(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		XMFLOAT3 right;
		XMStoreFloat3(&right, rotationMatrix.r[0]);
		return right;
	}

};