#include "main.h"
#include "renderer.h"
#include "bullet.h"
#include "modelRenderer.h"
#include "manager.h"
#include "enemy.h"
#include "score.h"
#include "box.h"

#include "explosion.h"
#include "player.h"

void Bullet::Init()
{
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\bullet.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	Scene* scene;
	scene = Manager::GetScene();

	Player* player;
	player = scene->GetGameObject<Player>();

	forward = player->GetForward();

	m_StartTime = std::chrono::system_clock::now();
}

void Bullet::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Bullet::Update()
{
	Scene* scene;
	scene = Manager::GetScene();

	m_NowTime = std::chrono::system_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(m_NowTime - m_StartTime).count();
	
	if ((double)elapsed_time == 2)
	{
		Explosion* explosion = scene->AddGameObject<Explosion>(1);
		explosion->SetPosition(m_Position);
		SetDestroy();
	}

	m_Position.x -= forward.x * 0.3f;
	m_Position.y -= forward.y * 0.3f;
	m_Position.z -= forward.z * 0.3f;

	//(std::vector <Enemy*>と同じ)
	auto enemyList = scene->GetGameObjects<Enemy>();
	for (Enemy* enemy : enemyList) {
		XMFLOAT3 enemyPosition = enemy->GetPosition();

		XMFLOAT3 direction;
		direction.x = enemyPosition.x - m_Position.x;
		direction.y = enemyPosition.y + 1 - m_Position.y;
		direction.z = enemyPosition.z - m_Position.z;

		float length;
		length = sqrtf(direction.x * direction.x
					+ direction.y * direction.y
					+ direction.z * direction.z);



		if (length < 1.0f)
		{
		Explosion* explosion = scene->AddGameObject<Explosion>(1);
			explosion->SetPosition(m_Position);

			enemy->SetDestroy();

			scene->GetGameObject<Score>()->AddCount(1);

			SetDestroy();
			return;
		}
	}

	auto boxList = scene->GetGameObjects<Box>();

	for (Box* box : boxList)
	{
		XMFLOAT3 boxPosition = box->GetPosition();
		XMFLOAT3 boxScale = box->GetScale();

		////短径衝突判定(AABB)
		//if (boxPosition.x - boxScale.x < m_Position.x &&
		//	m_Position.x < boxPosition.x + boxScale.x &&
		//	boxPosition.z - boxScale.z < m_Position.z &&
		//	m_Position.z < boxPosition.z + boxScale.z)
		//{
		//	//エフェクト生成→削除
		//	Explosion* explosion = scene->AddGameObject<Explosion>(1);
		//	explosion->SetPosition(m_Position);
		//	SetDestroy();
		//}

		// OBB
		XMFLOAT3 direction;
		direction.x = m_Position.x - boxPosition.x;
		direction.y = m_Position.y - boxPosition.y;
		direction.z = m_Position.z - boxPosition.z;
	
		//X分離軸
		XMFLOAT3 axisX = box->GetRight();
		float dotX = direction.x * axisX.x + direction.y * axisX.y + direction.z * axisX.z;

		//Z分離軸
		XMFLOAT3 axisZ = box->GetForward();
		float dotZ = direction.x * axisZ.x + direction.y * axisZ.y + direction.z * axisZ.z;

		if (-boxScale.x < dotX && dotX < boxScale.x &&
			-boxScale.z < dotZ && dotZ < boxScale.z)
		{
			Explosion* explosion = scene->AddGameObject<Explosion>(1);
			explosion->SetPosition(m_Position);
			SetDestroy();
		}
	}
}


void Bullet::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);


	m_Component->Draw();

}