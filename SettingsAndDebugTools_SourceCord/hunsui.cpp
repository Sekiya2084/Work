#include "main.h"
#include "renderer.h"
#include "hunsui.h"
#include "modelRenderer.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"

void Hunsui::Init()
{
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\hunnsuiw.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

}

void Hunsui::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Hunsui::Update()
{
	m_Component->Update();
}

void Hunsui::Draw()
{

	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	if (camera->CheckView(m_Position) == false)
		return;

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