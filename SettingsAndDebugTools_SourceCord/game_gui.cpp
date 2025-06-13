#include "game_gui.h"
#include "main.h"
#include "renderer.h"
//imgui関連インクルード
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


void GameGui::Init()
{
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

void GameGui::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void GameGui::Update()
{
	//  新フレームの開始（メインループの一番上に記述）
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//ウィンドウサイズ変更（解像度の修正がうまくいかないので後回し
	//ImGui::Begin("Window");
	//{
	//	const char* items[] = { "1280*720(default)", "1920*1080", "640*480" };

	//	ImGui::Combo("solusion", &item_current, items, IM_ARRAYSIZE(items));
	//	//テキスト表示
	//	ImGui::Text("%d", item_current);

	//	switch (item_current) {
	//	case 0:
	//		sw = 1280;
	//		sh = 720;

	//		break;

	//	case 1:
	//		sw = 1920;
	//		sh = 1080;
	//		break;

	//	case 2:
	//		sw = 640;
	//		sh = 480;
	//		break;

	//	default:
	//		sw = 1280;
	//		sh = 720;
	//		break;
	//	}

	//	RECT rc = { 0, 0, (LONG)sw, (LONG)sh };
	//	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	//	ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);

	//	if (ImGui::Button("Basic", sz)) {
	//		ImGui_ImplWin32_Shutdown();

	//		SetWindowPos(GetWindow(), NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, (SWP_NOMOVE));

	//		ImGui_ImplWin32_Init(GetWindow());
	//		//ImGui_ImplWin32_NewFrame();
	//	}

	//	
	//}
	//ImGui::End();

	//デモウィンドウの描画
	ImGui::ShowDemoWindow();
}

void GameGui::Draw()
{
	//  ImGuiの描画処理
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
