/*==============================================================================

   タイトル背景管理 [titleBG.cpp]
														 Author :関谷勇人
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "titleBG.h"
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
static TITLEBG g_TitleBG; //実体

static int g_TitleBGTexNo = 0;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTitleBG(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャの読み込み
	g_TitleBGTexNo = LoadTexture((char*)"data/TEXTURE/title.png");

	g_TitleBG.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_TitleBG.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitleBG(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitleBG(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitleBG(void)
{
	//タイトル背景の描画
	DrawSpriteLeftTop(g_TitleBGTexNo,
		g_TitleBG.pos.x, g_TitleBG.pos.y,
		g_TitleBG.size.x, g_TitleBG.size.y,
		0.0f, 0.0f,
		1.0f, 1.0f);
}