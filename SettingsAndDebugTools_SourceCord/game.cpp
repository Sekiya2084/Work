//システムインクルード
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "input.h"

//ゲーム内オブジェクト/シーンインクルード
#include "result.h"
#include "score.h"
#include "polygon2D.h"
#include "field.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "skydome.h"
#include "explosion.h"
#include "cylinder.h"
#include "meshField.h"
#include "fadePoly.h"
#include "tree.h"
#include "box.h"
#include "wave.h"
#include "menu.h"
#include "testObject.h"
#include "particleEmitter.h"
#include "game_gui.h"


void Game::Init()
{
	AddGameObject<Camera>(0)->SetPosition(XMFLOAT3(0.0f, 15.0f, -10.0f));
	AddGameObject<MeshField>(1);
	AddGameObject<Skydome>(1);
	AddGameObject<Player>(1);
	AddGameObject<Wave>(1)->SetPosition(XMFLOAT3(0.0f, 1.0f, 0.0f));
	/*AddGameObject<TestObject>(1)->SetPosition(XMFLOAT3(0.0f, 1.0f, 0.0f));*/
	AddGameObject<Polygon2D>(2);
	AddGameObject<Score>(2);

	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(10.0f, 0.0f, 0.0f));
	AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(10.0f, 6.0f, 9.0f));
	AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(5.0f, 6.0f, 2.0f));
	AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(0.0f, 6.0f, 9.0f));
	AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-5.0f, 6.0f, 4.0f));
	AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-10.0f, 6.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(10.0f, 0.0f, 11.0f));
	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(10.0f, 0.0f, 13.0f));
	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(20.0f, 0.0f, 0.0f));
	AddGameObject<Enemy>(1)->SetPosition(XMFLOAT3(15.0f, 0.0f, 0.0f));

	AddGameObject<Cylinder>(1)->SetPosition(XMFLOAT3(10.0f, 0.0f, -10.0f));
	AddGameObject<Cylinder>(1)->SetPosition(XMFLOAT3(12.0f, 1.0f, -10.0f));
	AddGameObject<Cylinder>(1)->SetPosition(XMFLOAT3(14.0f, 2.0f, -10.0f));

	//{
	//	Box* box = AddGameObject<Box>(1);
	//	box->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	//	box->SetScale(XMFLOAT3(2.0f, 2.0f, 2.0f));
	//	box->SetRotation(XMFLOAT3(0.0f, 2.0f, 0.0f));
	//}
	//{
	//	Box* box = AddGameObject<Box>(1);
	//	box->SetPosition(XMFLOAT3(10.0f, 0.0f, 0.0f));
	//	box->SetScale(XMFLOAT3(2.0f, 2.0f, 2.0f));
	//}
	//{
	//	Box* box = AddGameObject<Box>(1);
	//	box->SetPosition(XMFLOAT3(-10.0f, 0.0f, 0.0f));
	//	box->SetScale(XMFLOAT3(2.0f, 2.0f, 2.0f));
	//}

	/*AddGameObject<particleEmitter>(1)->SetPosition(XMFLOAT3(4.0f, 4.0f, 0.0f));*/
	AddGameObject<fadePoly>(2);

	GameGui::Init();
	ShowCursor(false);
}

void Game::Uninit()
{
	GameGui::Uninit();

	Scene::Uninit();
}

void Game::Update()
{
	GameGui::Update();

	Scene::Update();

	GetGameObject<fadePoly>()->FadeIn();
	auto enemyList = GetGameObjects<Enemy>();
	if (enemyList.size() == 0){
		m_Fadebool = true;
	}
	if (m_Fadebool)
		if (GetGameObject<fadePoly>()->FadeOut()) {
			Manager::SetScene<Result>();
		}
}

void Game::Draw()
{
	Scene::Draw();

	GameGui::Draw();
}