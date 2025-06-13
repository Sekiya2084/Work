#pragma once
#include "scene.h"

class Game : public Scene
{
private:
	bool m_Fadebool;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};