/*==============================================================================

   プレイヤー管理 [player.cpp]
														 Author :関谷　勇人
														 Date   :2023/06/29
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "bullet.h"
#include "sound.h"
#include "collision.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static PLAYER g_Player; //実体

static int g_PlayerTexNo = 0;
static int g_ShotSeNo = 0;

float yadd = 0.0f;
float rxadd = 0.0f;
float lxadd = 0.0f;

static int g_AnimePattern = 0;
static int g_AnimeSkipFrame = 0;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	ID3D11Device* pDevice = GetDevice();

	//サウンドの読み込み
	g_ShotSeNo = LoadSound((char*)"data/SE/jamp.wav");

	//テクスチャの読み込み
	g_PlayerTexNo = LoadTexture((char*)"data/TEXTURE/player.png");

	//初期化
	g_Player.use = false;
	g_Player.Jtrigger = true;
	g_Player.uv = D3DXVECTOR2(0.0f, 0.0f);
	/*g_Player.oldpos = g_Player.pos;*/
	
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;

	SetPlayer(D3DXVECTOR2(960.0f, 900.0f), D3DXVECTOR2(54.0f, 54.0f));
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//1フレーム前を格納
	g_Player.oldpos = g_Player.pos;
	
	//ニュートラルポーズ
	g_Player.uv.x = 0.0f;

//ジャンプ処理
	//キーボード
	if (GetKeyboardTrigger(DIK_SPACE) || GetKeyboardPress(DIK_UP))
	{	
		if(g_Player.Jtrigger)
		{
			if (rxadd >= 8.0f || lxadd <= -8.0f)
			{
				yadd = -20.0f;
			}
			else
			{
				yadd = -16.0f;
			}
			PlaySound(g_ShotSeNo, 0);

			//ボリューム調整
			SetVolume(g_ShotSeNo, 0.6f);

			g_Player.Jtrigger = false;
		}
	}

//y軸加速度
	g_Player.pos.y += yadd;
	yadd += 0.6f;

//ジャンプの描画
	if (g_Player.Jtrigger == false)
	{
		g_AnimePattern = 4.0f;
		g_Player.uv.x = 0.2f * g_AnimePattern;
	}
	else
	{
		
	}

//デバッグ時の地面判定 -> 死亡判定
	if(g_Player.pos.y > SCREEN_HEIGHT)
	{
		g_Player.use = false;
	}
	
//ダッシュ判定
	if (GetKeyboardPress(DIK_LSHIFT))
	{
		if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT))
		{
			g_Player.uv.x = 0.2f * g_AnimePattern;
			g_Player.uv.y = 0.5f;

			g_AnimeSkipFrame++;

			if (g_AnimeSkipFrame > 3)
			{
				g_AnimePattern++;
				g_AnimeSkipFrame = 0;

				if (g_AnimePattern > 3)
					g_AnimePattern = 1;
			}
			lxadd = -7.0f;
		}
		if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT))
		{
			g_Player.uv.x = 0.2f * g_AnimePattern;
			g_Player.uv.y = 0.0f;

			g_AnimeSkipFrame++;

			if (g_AnimeSkipFrame > 3)
			{
				g_AnimePattern++;
				g_AnimeSkipFrame = 0;

				if (g_AnimePattern > 3)
					g_AnimePattern = 1;
			}
			rxadd = 7.0f;
		}
	}

//非ダッシュ時の移動
	else 
	{
		if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_LEFT))
		{
			g_Player.uv.x = 0.2f * g_AnimePattern;
			g_Player.uv.y = 0.5f;

			g_AnimeSkipFrame++;

			if (g_AnimeSkipFrame > 7)
			{
				g_AnimePattern++;
				g_AnimeSkipFrame = 0;

				if (g_AnimePattern > 3)
					g_AnimePattern = 1;
			}
			lxadd = -5.0f;
		}
		if (GetKeyboardPress(DIK_D) || GetKeyboardPress(DIK_RIGHT))
		{
			g_Player.uv.x = 0.2f * g_AnimePattern;
			g_Player.uv.y = 0.0f;

			g_AnimeSkipFrame++;

			if (g_AnimeSkipFrame > 7)
			{
				g_AnimePattern++;
				g_AnimeSkipFrame = 0;

				if (g_AnimePattern > 3)
					g_AnimePattern = 1;
			}
			rxadd = 5.0f;
		}
	}

//x軸加速度
	g_Player.pos.x += (rxadd + lxadd);
	if (lxadd <= 0.0f)
	{
		lxadd += 0.3f;
	}

	if (rxadd >= 0.0f)
	{
		rxadd -= 0.3f;
	}

	////弾発射
	//if (GetKeyboardTrigger(DIK_B))
	//{
	//	SetBullet(g_Player.pos - D3DXVECTOR2(0.0f,g_Player.size.y / 2), D3DXVECTOR2(0.0f, -15.0f), D3DXVECTOR2(75, 75));
	//	//SEを流す
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	//プレイヤーの描画
	if (g_Player.use)
	{
		DrawSprite(g_PlayerTexNo,
			g_Player.pos.x, g_Player.pos.y,
			g_Player.size.x, g_Player.size.y,
			g_Player.uv.x, g_Player.uv.y,
			0.2f,0.5f 
		);
	}
}

//=============================================================================
// 実体のアドレス取得関数
//=============================================================================
PLAYER * GetPlayer()
{
	return &g_Player;
}

//=============================================================================
// プレイヤーのセット関数
//=============================================================================
void SetPlayer(D3DXVECTOR2 p, D3DXVECTOR2 s)
{
	if (!g_Player.use)
	{
		g_Player.pos = p;
		g_Player.size = s;
		g_Player.use = true;
	}
}

//collision処理時y軸加速度リセット用
void Setyadd(float add)
{
	yadd = add;
}