#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "result.h"

//imgui関連インクルード
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

//外部シーンインクルード
#include "title.h"

#include "input.h"
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


void Result::Init()
{
	AddGameObject<Camera>(0);
	AddGameObject<Skydome>(1);
	AddGameObject<fadePoly>(2);
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

void Result::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Result::Update()
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
	if (m_Fadebool)
		if (GetGameObject<fadePoly>()->FadeOut()) {
			Manager::SetScene<Title>();
		}
}

void Result::Draw()
{
	//  ImGuiの描画処理
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
