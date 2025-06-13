#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "result.h"

//imgui�֘A�C���N���[�h
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

//�O���V�[���C���N���[�h
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
		//  �o�[�W�����̊m�F
		IMGUI_CHECKVERSION();

		//  �R���e�L�X�g�̍쐬
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // �L�[�{�[�h�ɂ��i�r�Q�[�V�����̗L����
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // �R���g���[���[�ɂ��i�r�Q�[�V�����̗L����

		//  Win32�p�̏�����
		ImGui_ImplWin32_Init(GetWindow());
		//  DirectX11�p�̏�����
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
	//  �V�t���[���̊J�n�i���C�����[�v�̈�ԏ�ɋL�q�j
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
	//  ImGui�̕`�揈��
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
