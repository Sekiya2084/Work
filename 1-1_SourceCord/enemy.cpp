/*==============================================================================

   敵管理 [enemy.cpp]
														 Author :関谷　勇人
														 Date   :2023/06/29
--------------------------------------------------------------------------------

==============================================================================*/
#include "enemy.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ENEMY g_Enemy[MAX_ENEMY]; //実体

static int g_EnemyTexNo = 0; //テクスチャID

static int g_AnimePattern = 0;
static int g_AnimeSkipFrame = 0;
//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャの読み込み
	g_EnemyTexNo = LoadTexture((char*)"data/TEXTURE/kenemy.png");

	//初期化
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_Enemy[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Enemy[i].vel = D3DXVECTOR2(0.0f, 0.0f);
		g_Enemy[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Enemy[i].rot = 0.0f;
		g_Enemy[i].uv.x = 0.0f;
		g_Enemy[i].uv.y = 0.0f;
		g_Enemy[i].g_Animeskipframe = 0;
		g_Enemy[i].g_AnimePattern = 0;

		g_Enemy[i].use = false;
	}

	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	PLAYER* pPlayer = GetPlayer();
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i].use)
		{
			if (pPlayer->pos.x - 960.0f <= g_Enemy[i].pos.x  || pPlayer->pos.x + 960.0f  >= g_Enemy[i].pos.x)
			{
				//移動
				g_Enemy[i].pos += g_Enemy[i].vel;
				
				g_Enemy[i].uv.x = 0.5f * g_Enemy[i].g_AnimePattern;
				g_Enemy[i].uv.y = 1.0f;

				g_Enemy[i].g_Animeskipframe++;

				if (g_Enemy[i].g_Animeskipframe > 15)
				{
					g_Enemy[i].g_AnimePattern++;
					g_Enemy[i].g_Animeskipframe = 0;

					if (g_Enemy[i].g_AnimePattern > 1)
						g_Enemy[i].g_AnimePattern = 0;
				}

				////画面外判定(画面外へ行った時使用フラグをFalseへ)
				//if (g_Enemy[i].pos.x > SCREEN_WIDTH + g_Enemy[i].size.x / 2 || 
				//	g_Enemy[i].pos.y > SCREEN_HEIGHT + g_Enemy[i].size.y / 2	|| 
				//	g_Enemy[i].pos.x < 0.0f - g_Enemy[i].size.x / 2 || 
				//	g_Enemy[i].pos.y < 0.0f - g_Enemy[i].size.y / 2
				//	)
				//{
				//	g_Enemy[i].use = false;
				//}
			}
			else
			{
				continue;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i].use) 
		{
			//敵の描画
			DrawSpriteColorRotate(g_EnemyTexNo,
				g_Enemy[i].pos.x, g_Enemy[i].pos.y,
				g_Enemy[i].size.x, g_Enemy[i].size.y,
				g_Enemy[i].uv.x, g_Enemy[i].uv.y,
				0.5f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				g_Enemy[i].rot
			);
		}
	}
}

//=============================================================================
// セット関数
//=============================================================================
void SetEnemy(D3DXVECTOR2 spos, D3DXVECTOR2 svel, D3DXVECTOR2 ssize)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (!g_Enemy[i].use)
		{
			g_Enemy[i].pos = spos;
			g_Enemy[i].vel = svel;
			g_Enemy[i].size = ssize;

			g_Enemy[i].use = true;
			break;
		}
	}
}

//=============================================================================
// 実体のアドレス取得関数
//=============================================================================
ENEMY* GetEnemy(void) 
{
	return g_Enemy;
}