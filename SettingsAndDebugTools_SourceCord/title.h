#pragma once
#include "scene.h"

class Title : public Scene
{
private:
	bool m_Fadebool = false;
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};