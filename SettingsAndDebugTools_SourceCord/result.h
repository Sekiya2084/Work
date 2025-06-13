#pragma once
#include "scene.h"

class Result : public Scene
{
private:
	bool m_Fadebool;
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};