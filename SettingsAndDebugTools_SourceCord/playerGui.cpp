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


#include "playerGui.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"



void PlayerGui::Update()
{
	Scene* scene;
	scene = Manager::GetScene();

	Player* player;
	player = scene->GetGameObject<Player>();

	ImGui::Begin("PlayerParameter");
	{
		//  テキストの表示
		ImGui::Text("PlayerSpeed");

		static float f1 = player->GetSpeed();
		ImGui::SliderFloat("Speed", &f1, 0.0f, 1.0f, "%.3f");


		ImGui::Text("Push P");
		if(Input::GetKeyTrigger('P'))
		player->SetSpeed(f1); 
	}
	ImGui::End();
}
