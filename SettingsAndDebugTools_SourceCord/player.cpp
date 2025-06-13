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
#include "imgui.h"
#include "camera.h"

void Player::Init()
{
	//m_Component = new ModelRenderer(this);
	//((ModelRenderer*)m_Component)->Load("asset\\model\\player.obj");

	m_Component = new AnimationModel(this);
	((AnimationModel*)m_Component)->Load("asset\\model\\Akai.fbx");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_Idle.fbx","Idle");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_Run.fbx","Run");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_Back.fbx","Back");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_Jamp.fbx","Jamp");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_RWalk.fbx","RWalk");
	((AnimationModel*)m_Component)->LoadAnimation("asset\\model\\Akai_LWalk.fbx","LWalk");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
	
	m_Scale = XMFLOAT3(0.01f, 0.01f, 0.01f);
	m_Speed = MINSPEED;
	m_MaxSpeed = MAXSPEED;
	m_MinSpeed = MINSPEED;
	m_JampPower = 0.3;

	//imgui用
	i_Speed = m_Speed;
	i_MaxSpeed = MAXSPEED;
	i_MinSpeed = MINSPEED;
	i_Jamp = m_JampPower;

	m_Rotation.y = 3.15f;

	m_SE = new Audio(this);
	m_SE->Load("asset\\audio\\wan.wav");

	m_ChildModel = new ModelRenderer(this);
	((ModelRenderer*)m_ChildModel)->Load("asset\\model\\box.obj");
}

void Player::Uninit()
{
	m_SE->Uninit();
	delete m_SE;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Component->Uninit();
	delete m_Component;

	m_ChildModel->Uninit();
	delete m_ChildModel;
}

void Player::Update()
{
	XMFLOAT3 oldPosition = m_Position;

	Scene* scene;
	scene = Manager::GetScene();

	Camera* camera;
	camera = scene->GetGameObject<Camera>();

	m_AnimationName1 = "Idle";
	XMFLOAT3 forward = GetForward();
	XMFLOAT3 right = GetRight();
	//GetRightで同じようなものが必要
	
	if (!camera->GetCursorEnable()) {
		//基本操作部分
		if (Input::GetKeyPress('W')) {
			m_Position.x -= forward.x * m_Speed;
			m_Position.y -= forward.y * m_Speed;
			m_Position.z -= forward.z * m_Speed;


			if (m_AnimationName2 != "Run")
			{
				m_AnimationName1 = m_AnimationName2;
				m_AnimationName2 = "Run";
				m_AnimationBlendRatio = 0.0f;
			}
			//ダッシュ
			if (Input::GetKeyPress(VK_LSHIFT))
			{
				if (m_Speed < m_MaxSpeed)
					m_Speed += 0.01f;
			}
			else
				if (m_Speed > m_MinSpeed)
					m_Speed -= 0.01f;

		}

		if (Input::GetKeyPress('S')) {
			m_Position.x += forward.x * m_Speed * 0.45;
			m_Position.y += forward.y * m_Speed * 0.45;
			m_Position.z += forward.z * m_Speed * 0.45;

			if (m_AnimationName2 != "Back")
			{
				m_AnimationName1 = m_AnimationName2;
				m_AnimationName2 = "Back";
				m_AnimationBlendRatio = 0.0f;
			}
		}

		if (Input::GetKeyPress('A')) {
			m_Position.x += right.x * m_Speed * 0.5;
			m_Position.y += right.y * m_Speed * 0.5;
			m_Position.z += right.z * m_Speed * 0.5;
			if (m_AnimationName2 != "LWalk")
			{
				m_AnimationName1 = m_AnimationName2;
				m_AnimationName2 = "LWalk";
				m_AnimationBlendRatio = 0.0f;
			}
		}

		if (Input::GetKeyPress('D')) {
			m_Position.x -= right.x * m_Speed * 0.5;
			m_Position.y -= right.y * m_Speed * 0.5;
			m_Position.z -= right.z * m_Speed * 0.5;
			if (m_AnimationName2 != "RWalk")
			{
				m_AnimationName1 = m_AnimationName2;
				m_AnimationName2 = "RWalk";
				m_AnimationBlendRatio = 0.0f;
			}
		}
		
		if (Input::GetKeyTrigger(VK_SPACE) && m_JampTrigger)
		{
			m_Velocity = m_JampPower;
			m_JampTrigger = false;
		}

		//Idle
		if (m_AnimationName2 != "Idle")
		{
			m_AnimationName1 = m_AnimationName2;
			m_AnimationName2 = "Idle";
			m_AnimationBlendRatio = 0.0f;
		}


		m_AnimationBlendRatio += 0.05f;
		if (m_AnimationBlendRatio > 1.0f)
			m_AnimationBlendRatio = 1.0f;

		

		//弾発射
		if (Input::GetKeyTrigger(VK_LBUTTON))
		{
			Bullet* bullet = scene->AddGameObject<Bullet>(1);
			bullet->SetPosition(XMFLOAT3(m_Position.x, m_Position.y + 1, m_Position.z));
			bullet->SetRotation(XMFLOAT3(camera->GetRotation().x, bullet->GetRotation().y + camera->GetRotation().y, camera->GetRotation().z));
			m_SE->Play();
		}

		MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>();

		float groundHeight = meshField->GetHeight(m_Position);

		float cylinderHeight = 0.0f;

		auto cylinderList = scene->GetGameObjects<Cylinder>();

		for (Cylinder* cylinder : cylinderList)
		{
			XMFLOAT3 cylinderPosition = cylinder->GetPosition();
			XMFLOAT3 cylinderScale = cylinder->GetScale();

			XMFLOAT3 direction;
			direction.x = cylinderPosition.x - m_Position.x;
			direction.y = cylinderPosition.y - m_Position.y;
			direction.z = cylinderPosition.z - m_Position.z;

			float length;
			length = sqrtf(direction.x * direction.x
				+ direction.z * direction.z);

			if (length < cylinderScale.x) {
				if (-direction.y > cylinderScale.y - 0.5f) {
					groundHeight = cylinderPosition.y + cylinderScale.y;
				}
				else
				{
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
				}
			}
		}



		m_Velocity -= 0.02f;
		m_Position.y += m_Velocity;

		if (groundHeight > m_Position.y)
		{
			m_Position.y = groundHeight;
			m_Velocity = 0.0;
			m_JampTrigger = true;
		}
		else
		{
		}

		if (Input::GetKeyTrigger(VK_RETURN)) {
			m_Fadebool = true;
		}
		if (m_Fadebool)
			if (scene->GetGameObject<fadePoly>()->FadeOut()) {
				Manager::SetScene<Result>();
			}
	
		ImGui::Begin("PlayerParameter::Update");

		//  テキストの表示
		ImGui::Text("PlayerSpeed: % .3f", m_Speed);
		ImGui::Text("m_RotationY: % .3f", m_Rotation.y);


		ImGui::Text("Push RIGHTSHIFT go to SETTINGMODE");

		ImGui::End();
	}


	//PlayerImgui
	else{
		ImGui::Begin("PlayerParameter::StopUpdate");

		//  テキストの表示
		ImGui::Text("PlayerSpeed: % .3f", m_Speed);
		ImGui::Text("m_RotationY: % .3f", m_Rotation.y);

		ImGui::SliderFloat("Speed", &i_Speed, 0.0f, 1.0f, "%.3f");
		ImGui::SliderFloat("MaxSpeed", &i_MaxSpeed, 0.0f, 1.0f, "%.3f");
		ImGui::SliderFloat("MinSpeed", &i_MinSpeed, 0.0f, 1.0f, "%.3f");
		ImGui::SliderFloat("JampPower", &i_Jamp, 0.0f, 1.0f, "%.3f");

		ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);
		/*ImGui::Text("Push In to Game");*/
		if (ImGui::Button("Accept",sz)) {
			m_Speed = i_Speed;
			m_MaxSpeed = i_MaxSpeed;
			m_MinSpeed = i_MinSpeed;
			m_JampPower = i_Jamp;
		}

		ImGui::End();
	}
}

void Player::Draw()
{	
	//((AnimationModel*)m_Component)->Update((m_AnimationName1.c_str()), m_AnimationFrame,(m_AnimationName2.c_str()), m_AnimationFrame,0.5);
	((AnimationModel*)m_Component)->Update(m_AnimationName1.c_str(), m_AnimationFrame, m_AnimationName2.c_str(), m_AnimationFrame, m_AnimationBlendRatio);
	m_AnimationFrame++;
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y - XM_PI, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);


	m_Component->Draw();

	//asympとDirectXでは行列のたてとよこが逆なので変換が必要

	//ワールドマトリクス設定
	//XMMATRIX childWorld, childScale, childRot, childTrans;
	//childScale = XMMatrixScaling(1.0f / m_Scale.x, 1.0f / m_Scale.y, 1.0f / m_Scale.z);
	//childRot = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	//childTrans = XMMatrixTranslation(0.0f , 0.0f, 3.0f);
	//childWorld = childRot * childTrans * childScale */* * rightHandMatrix */ world;//worldをかけるのは最後にしなければならない
	//Renderer::SetWorldMatrix(childWorld);

	//m_ChildModel->Draw();
}
