#pragma once

class Component
{
protected:
	class GameObject* m_GameObject = nullptr;

public:
	Component() = delete;
	Component(GameObject* Object) { m_GameObject = Object; }
	virtual ~Component(){}


	virtual void Init() {};//純粋仮想関数ではなく仮想関数(実体が必要)
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};

};