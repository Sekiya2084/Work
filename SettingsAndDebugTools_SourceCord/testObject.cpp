#include "main.h"
#include "renderer.h"
#include "testObject.h"
#include "modelRenderer.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"

void TestObject::Init()
{
	m_Component = new ModelRenderer(this);
	((ModelRenderer*)m_Component)->Load("asset\\model\\sphere_smooth.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\envMappingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\envMappingPS.cso");

	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\earthenvmap.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_EnvTexture);
	assert(m_EnvTexture);

}

void TestObject::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_EnvTexture->Release();
}

void TestObject::Update()
{
	m_Rotation.x += 0.01f;
	m_Rotation.z += 0.01f;
}

void TestObject::Draw()
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


	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_EnvTexture);

	m_Component->Draw();

}