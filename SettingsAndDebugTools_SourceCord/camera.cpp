#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "scene.h"
#include "player.h"
#include "title.h"
#include "imgui.h"

void Camera::Init()
{
	//m_Position = XMFLOAT3(0.0f, 15.0f, -10.0f);
	m_Target = XMFLOAT3(10.0f, 5.0f, 10.0f);
}


void Camera::Uninit()
{
	
}

void Camera::Update()
{
	Scene* scene;
	scene = Manager::GetScene();


	Player* player;
	player = scene->GetGameObject<Player>();

	if (player != NULL) {
		m_Target = player->GetPosition();
		m_Target.y += 1.5f;

		if (Input::GetKeyTrigger(VK_RSHIFT)) {
			if (!m_CursorTrigger) {
				m_CursorTrigger = true;
				CursorInfo = ShowCursor(true);
			}
			else if (m_CursorTrigger) {
				m_CursorTrigger = false;
				CursorInfo = ShowCursor(false);
			}
		}

		POINT cursorPos;
		HWND hwnd = GetWindow();
		RECT rect;

		if (GetCursorPos(&cursorPos) && !m_CursorTrigger && GetActiveWindow) {
			if (GetWindowRect(hwnd, &rect)) {
				int centerX = (rect.left + rect.right) / 2;
				int centerY = (rect.top + rect.bottom) / 2;
				
				float deltaX = (float)(cursorPos.x - centerX);
				float deltaY = (float)(cursorPos.y - centerY);

				m_Rotation.y += deltaX * m_Sensi;

				XMFLOAT3 pRot = player->GetRotation();

				//回転値をプレイヤーに渡し、真後ろを追跡(フォローCAM？)
				player->SetRotation(XMFLOAT3(pRot.x, pRot.y+= deltaX * m_Sensi, pRot.z)); //

				if (deltaY > m_DeadZone || deltaY < -m_DeadZone)
				m_Rotation.x += deltaY * m_Sensi;

				if (m_Rotation.x > m_RotXMax) m_Rotation.x = m_RotXMax;
				if (m_Rotation.x < m_RotXMin) m_Rotation.x = m_RotXMin;

				SetCursorPos(centerX, centerY);
			}
		}
	}
	else
		m_Rotation.y += 0.003;

	//緊急時用キーボードカメラ
	//if (Input::GetKeyPress(VK_LEFT))
	//{
	//	m_Rotation.y -= 0.03f;
	//}
	//if (Input::GetKeyPress(VK_RIGHT))
	//{
	//	m_Rotation.y += 0.03f;
	//}
	//if (Input::GetKeyPress(VK_UP))
	//{
	//	m_Rotation.x -= 0.03f;
	//}
	//if (Input::GetKeyPress(VK_DOWN))
	//{
	//	m_Rotation.x += 0.03f;
	//}

	ImGui::Begin("CameraParameter");
	{
		//  テキストの表示
		//ImGui::Text("MousePointX: % .3f", Input::GetMousePointX());
		//ImGui::Text("MousePointY: % .3f", Input::GetMousePointY());
		//ImGui::Text("m_RotationX(Pitch): % .3f", m_Rotation.y);
		//ImGui::Text("Cursor: %d", CursorInfo);
		ImGui::SliderFloat("CameraSpeed", &i_Sensi, 0.001f, 0.01f, "%.3f");

		ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);
		/*ImGui::Text("Push In to Game");*/
		if (ImGui::Button("Accept", sz)) {
			m_Sensi = i_Sensi;
		}
	}
	ImGui::End();

	m_Position.x = m_Target.x - sinf(m_Rotation.y) * 3.0f;
	m_Position.y = m_Target.y - sinf(m_Rotation.x) * 3.0f;
	m_Position.z = m_Target.z - cosf(m_Rotation.y) * 3.0f;
}

void Camera::Draw()
{
	XMFLOAT3 up{ 0.0f,1.0f,0.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_Target), XMLoadFloat3(&up));

	Renderer::SetViewMatrix(viewMatrix);

	XMStoreFloat4x4(&m_ViewMatrix, viewMatrix);

	//プロジェクションマトリクス設定
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	
	Renderer::SetProjectionMatrix(projectionMatrix);

	//カメラ座標設定
	Renderer::SetCameraPosition(m_Position);
}

bool Camera::CheckView(XMFLOAT3 Position)
{
	XMFLOAT3 up{ 0.0f,1.0f,0.0f };
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_Target), XMLoadFloat3(&up));


	//プロジェクションマトリクス設定
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	XMMATRIX vp, invvp;
	XMVECTOR det;

	vp = viewMatrix * projectionMatrix;
	invvp = XMMatrixInverse(&det, vp);

	XMFLOAT3 vpos[4];
	XMFLOAT3 wpos[4];

	vpos[0] = XMFLOAT3(-1.0, 1.0f, 1.0f);
	vpos[1] = XMFLOAT3(1.0, 1.0f, 1.0f);
	vpos[2] = XMFLOAT3(-1.0, -1.0f, 1.0f);
	vpos[3] = XMFLOAT3(1.0, -1.0f, 1.0f);

	XMVECTOR vposv[4];
	XMVECTOR wposv[4];

	vposv[0] = XMLoadFloat3(&vpos[0]);
	vposv[1] = XMLoadFloat3(&vpos[1]);
	vposv[2] = XMLoadFloat3(&vpos[2]);
	vposv[3] = XMLoadFloat3(&vpos[3]);


	wposv[0] = XMVector3TransformCoord(vposv[0], invvp);
	wposv[1] = XMVector3TransformCoord(vposv[1], invvp);
	wposv[2] = XMVector3TransformCoord(vposv[2], invvp);
	wposv[3] = XMVector3TransformCoord(vposv[3], invvp);

	XMStoreFloat3(&wpos[0], wposv[0]);
	XMStoreFloat3(&wpos[1], wposv[1]);
	XMStoreFloat3(&wpos[2], wposv[2]);
	XMStoreFloat3(&wpos[3], wposv[3]);

	XMFLOAT3 v, v1, v2, n;


	v.x = Position.x - m_Position.x;
	v.y = Position.y - m_Position.y;
	v.z = Position.z - m_Position.z;

	//左面判定
	{
		v1.x = wpos[0].x - m_Position.x;
		v1.y = wpos[0].y - m_Position.y;
		v1.z = wpos[0].z - m_Position.z;

		v2.x = wpos[2].x - m_Position.x;
		v2.y = wpos[2].y - m_Position.y;
		v2.z = wpos[2].z - m_Position.z;

		n.x = v1.y * v2.z - v1.z * v2.y;
		n.y = v1.z * v2.x - v1.x * v2.z;
		n.z = v1.x * v2.y - v1.y * v2.x;

		float dot = n.x * v.x + n.y * v.y + n.z * v.z;

		if (dot < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool Camera::GetCursorEnable() {
	return m_CursorTrigger;
}