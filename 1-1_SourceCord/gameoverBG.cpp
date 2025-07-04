/*==============================================================================

   リザルト背景管理 [gameoverBG.cpp]
														 Author :関谷勇人
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "gameoverBG.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static GAMEOVERBG g_GameoverBG; //実体

static int g_GameoverBGTexNo = 0;
//=============================================================================
// 初期化処理
//=============================================================================
void InitGameoverBG(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャの読み込み
	g_GameoverBGTexNo = LoadTexture((char*)"data/TEXTURE/gameover.png");

	g_GameoverBG.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_GameoverBG.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameoverBG(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameoverBG(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGameoverBG(void)
{
	//タイトル背景の描画
	DrawSpriteLeftTop(g_GameoverBGTexNo,
		g_GameoverBG.pos.x, g_GameoverBG.pos.y,
		g_GameoverBG.size.x, g_GameoverBG.size.y,
		0.0f, 0.0f,
		1.0f, 1.0f);
}