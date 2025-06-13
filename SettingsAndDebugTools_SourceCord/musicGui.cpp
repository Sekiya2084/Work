#include "main.h"
#include "renderer.h"
#include "player.h"
#include "modelRenderer.h"
#include "input.h"
#include "manager.h"
#include "cylinder.h"
#include "result.h"
#include "animationModel.h"
#include "meshField.h"


#include "musicGui.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"



void MusicGui::Update()
{
	Scene* scene;
	scene = Manager::GetScene();

	Player* player;
	player = scene->GetGameObject<Player>();

	ImGui::Begin("Music");
	{
		//  テキストの表示
		ImGui::Text("MusicVolume");

		static float f1 = 0.123f;
		ImGui::SliderFloat("slider float", &f1, 0.0f, 1.0f, "%.3f");
	}
	ImGui::End();
}
