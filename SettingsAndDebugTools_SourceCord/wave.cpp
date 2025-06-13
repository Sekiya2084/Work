#include "main.h"
#include "renderer.h"
#include "wave.h"

void Wave::Init()
{

	//頂点バッファ生成
	for (int x = 0; x < 21; x++)
	{
		for (int z = 0; z < 21; z++)
		{
			m_Vertex[x][z].Position = XMFLOAT3((x - 10) * 5.0f, 0.0f, (z - 10) * -5.0f);
			m_Vertex[x][z].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_Vertex[x][z].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertex[x][z].TexCoord = XMFLOAT2(x, z);
		}
	}

	for (int x = 1; x <= 19; x++)
	{
		for (int z = 1; z <= 19; z++)
		{
			XMFLOAT3 vx, vz, vn;
			vx.x = m_Vertex[x + 1][z].Position.x - m_Vertex[x - 1][z].Position.x;
			vx.y = m_Vertex[x + 1][z].Position.y - m_Vertex[x - 1][z].Position.y;
			vx.z = m_Vertex[x + 1][z].Position.z - m_Vertex[x - 1][z].Position.z;

			vz.x = m_Vertex[x][z - 1].Position.x - m_Vertex[x][z + 1].Position.x;
			vz.y = m_Vertex[x][z - 1].Position.y - m_Vertex[x][z + 1].Position.y;
			vz.z = m_Vertex[x][z - 1].Position.z - m_Vertex[x][z + 1].Position.z;

			vn.x = vz.y * vx.z - vz.z * vx.y;
			vn.y = vz.z * vx.x - vz.x * vx.z;
			vn.z = vz.x * vx.y - vz.y * vx.x;

			float len = sqrtf(vn.x * vn.x + vn.y * vn.y + vn.z * vn.z);
			vn.x /= len;
			vn.y /= len;
			vn.z /= len;

			m_Vertex[x][z].Normal = vn;
		}
	}
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * (21 * 21);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	//ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = m_Vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//インデックスバッファ
	{
		unsigned int index[((21 + 1) * 2) * 20 - 2];

		int i = 0;
		for (int x = 0; x < 20; x++)
		{
			for (int z = 0; z < 21; z++)
			{
				index[i] = x * 21 + z;
				i++;

				index[i] = (x + 1) * 21 + z;
				i++;
			}

			if (x == 19)
				break;

			index[i] = (x + 1) * 21 + 20;
			i++;
			index[i] = (x + 1) * 21;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		//ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		m_Rotation = XMFLOAT3(0, 180, 0);

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;

	LoadFromWICFile(L"asset\\texture\\wave.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	//環境マップテクスチャ読み込み
	LoadFromWICFile(L"asset\\texture\\envwave.jpg", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_EnvTexture);
	assert(m_EnvTexture);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\waveVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\wavePS.cso");
}

void Wave::Uninit()
{

	m_VertexBuffer->Release();
	m_Texture->Release();
	m_EnvTexture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Wave::Update()
{
	float amplitude = 0.1f;
	float waveLength = 1.0f;
	float waveCycle = 2.0f;

	for (int x = 0; x < 21; x++)
	{
		for (int z = 0; z < 21; z++)
		{
			float dx = m_Vertex[z][x].Position.x - m_Vertex[0][0].Position.x;
			float dz = m_Vertex[z][x].Position.z - m_Vertex[0][0].Position.z;
			float length = sqrtf(dx * dx + dz * dz);

			m_Vertex[x][z].Position.y = amplitude * sinf(2.0f * XM_PI * (length / waveLength - m_Time /waveCycle));
			
			/*m_Vertex[x][z].Position.y += amplitude * sinf(2.0f * XM_PI * (length / waveLength - m_Time /waveCycle));*/
		}
	}

	m_Time += 1.0f / 60.0f;


	for (int x = 1; x < 20; x++)
	{
		for (int z = 1; z < 20; z++)
		{
			XMFLOAT3 vx, vz, vn;
			vx.x = m_Vertex[x + 1][z].Position.x - m_Vertex[x - 1][z].Position.x;
			vx.y = m_Vertex[x + 1][z].Position.y - m_Vertex[x - 1][z].Position.y;
			vx.z = m_Vertex[x + 1][z].Position.z - m_Vertex[x - 1][z].Position.z;

			vz.x = m_Vertex[x][z - 1].Position.x - m_Vertex[x][z + 1].Position.x;
			vz.y = m_Vertex[x][z - 1].Position.y - m_Vertex[x][z + 1].Position.y;
			vz.z = m_Vertex[x][z - 1].Position.z - m_Vertex[x][z + 1].Position.z;

			vn.x = vz.y * vx.z - vz.z * vx.y;
			vn.y = vz.z * vx.x - vz.x * vx.z;
			vn.z = vz.x * vx.y - vz.y * vx.x;

			float len = sqrtf(vn.x * vn.x + vn.y * vn.y + vn.z * vn.z);
			vn.x /= len;
			vn.y /= len;
			vn.z /= len;

			m_Vertex[x][z].Normal = vn;
		}
	}
	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	
	memcpy(vertex, m_Vertex, sizeof(VERTEX_3D) * 21 * 21);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
}

void Wave::Draw()
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

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//マテリアル設定
	MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_EnvTexture);

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);
}

float Wave::GetHeight(XMFLOAT3 Position)
{
	int x, z;
	//ブロック番号算出
	x = Position.x / 5.0f + 10.0f;
	z = Position.z / -5.0f + 10.0f;

	XMFLOAT3 pos0, pos1, pos2, pos3;
	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	XMFLOAT3 v12, v1p;
	v12.x = pos2.x - pos1.x;
	v12.y = pos2.y - pos1.y;
	v12.z = pos2.z - pos1.z;

	v1p.x = Position.x - pos1.x;
	v1p.y = Position.y - pos1.y;
	v1p.z = Position.z - pos1.z;

	float cy = v12.z * v1p.x - v12.x * v1p.z;

	float py;
	XMFLOAT3 n;
	if (cy > 0.0f)
	{
		XMFLOAT3 v10;
		v10.x = pos0.x - pos1.x;
		v10.y = pos0.y - pos1.y;
		v10.z = pos0.z - pos1.z;

		n.x = v10.y * v12.z - v10.z * v12.y;
		n.y = v10.z * v12.x - v10.x * v12.z;
		n.z = v10.x * v12.y - v10.y * v12.x;
	}
	else
	{
		XMFLOAT3 v13;
		v13.x = pos3.x - pos1.x;
		v13.y = pos3.y - pos1.y;
		v13.z = pos3.z - pos1.z;

		n.x = v12.y * v13.z - v12.z * v13.y;
		n.y = v12.z * v13.x - v12.x * v13.z;
		n.z = v12.x * v13.y - v12.y * v13.x;
	}

	py = -((Position.x - pos1.x) * n.x + (Position.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;
}