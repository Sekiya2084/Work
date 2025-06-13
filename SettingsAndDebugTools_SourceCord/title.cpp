#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"


//imgui関連インクルード
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

//外部シーンインクルード
#include "game.h"

#include "input.h"
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
#include "particleEmitter.h"
#include "wave.h"
#include "meshField.h"
#include "tree.h"
#include "hunsui.h"
#include "titlepng.h"
#include "ken.h"


void Title::Init()
{
	AddGameObject<Camera>(0)->SetPosition(XMFLOAT3(0.0f,0.0f,0.0f));
	AddGameObject<MeshField>(1);
	AddGameObject<Skydome>(1);
	////正面
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(21.0f, 5.0f, 25.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(14.0f, 5.0f, 30.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-7.0f, 5.0f, 25.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(7.0f, 5.0f, 30.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(0.0f, 5.0f, 25.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(28.0f, 5.0f, 30.0f));
	////右
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-5.0f, 5.0f, 21.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-10.0f, 5.0f, 14.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-5.0f, 5.0f, -7.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-10.0f, 5.0f, 7.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-5.0f, 5.0f, 0.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-20.0f, 5.0f, 28.0f));
	////後
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(14.0f, 5.0f, -10.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(-7.0f, 5.0f, -5.0f));
	//AddGameObject<Ken>(1)->SetPosition(XMFLOAT3(-2.0f, 5.0f, 7.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(7.0f, 5.0f, -10.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(0.0f, 5.0f, -5.0f));
	////左
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(20.0f, 5.0f, 21.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(25.0f, 5.0f, 14.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(20.0f, 5.0f, -7.0f));
	//AddGameObject<Ken>(1)->SetPosition(XMFLOAT3(15.0f, 5.0f, -7.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(25.0f, 5.0f, 7.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(20.0f, 5.0f, 0.0f));
	//AddGameObject<Tree>(1)->SetPosition(XMFLOAT3(35.0f, 5.0f, 28.0f));

	AddGameObject<Hunsui>(1)->SetPosition(XMFLOAT3(10.0f, 1.0f, 20.0f));
	AddGameObject<particleEmitter>(1)->SetPosition(XMFLOAT3(10.0f, 5.0f, 20.2f));
	AddGameObject<Wave>(1)->SetPosition(XMFLOAT3(0.0f, 1.0f, 0.0f));
	AddGameObject<Titlepng>(2);
	AddGameObject<fadePoly>(2);

	//  ImGuiの初期化処理
	{
		//  バージョンの確認
		IMGUI_CHECKVERSION();

		//  コンテキストの作成
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // キーボードによるナビゲーションの有効化
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // コントローラーによるナビゲーションの有効化

		//  Win32用の初期化
		ImGui_ImplWin32_Init(GetWindow());
		//  DirectX11用の初期化
		ID3D11Device* device = Renderer::GetDevice();
		ID3D11DeviceContext* context = Renderer::GetDeviceContext();
		ImGui_ImplDX11_Init(device, context);
	}
}

void Title::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	Scene::Uninit();
}

void Title::Update()
{
	//  新フレームの開始（メインループの一番上に記述）
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Scene::Update();

	GetGameObject<fadePoly>()->FadeIn();
	if (Input::GetKeyTrigger(VK_RETURN)) {
		m_Fadebool = true;
	}
	if(m_Fadebool)
		if (GetGameObject<fadePoly>()->FadeOut()) {
			Manager::SetScene<Game>();
	}
}

void Title::Draw()
{
	Scene::Draw();

	//  ImGuiの描画処理
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}