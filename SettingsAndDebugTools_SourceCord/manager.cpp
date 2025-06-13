#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "camera.h"
#include "field.h"
#include "gameobject.h"
#include "player.h"
#include "input.h"
#include "scene.h"
#include "title.h"
#include "audio.h"
//#include "meshField.h"


Scene* Manager::m_Scene{};
Scene* Manager::m_NextScene{};

void Manager::Init()
{
	Input::Init();
	Renderer::Init();
	Audio::InitMaster();

	m_Scene = new Title();
	m_Scene->Init();
}


void Manager::Uninit()
{
	m_Scene->Uninit();
	Input::Uninit();
	Renderer::Uninit();
	Audio::UninitMaster();
}

void Manager::Update()
{
	m_Scene->Update();
	Input::Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();
	
	Renderer::End();

	if (m_NextScene != nullptr) {
		if (m_Scene) {
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = m_NextScene;
		m_Scene->Init();

		m_NextScene = nullptr;
	}
}
