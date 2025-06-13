/*==============================================================================

   フェード管理 [fade.cpp]
														 Author :関谷勇人
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
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
static int g_FadeTexNo = 0;
float g_fadeAlpha;
FADE_MODE g_fadeState;

//=============================================================================
// 初期化処理
//=============================================================================
void InitFade(void)
{
	ID3D11Device* pDevice = GetDevice();

	//テクスチャの読み込み
	g_FadeTexNo = LoadTexture((char*)"data/TEXTURE/fade_white.png");

	g_fadeAlpha = 0.0f;
	g_fadeState = FADE_NONE;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	switch (g_fadeState)
	{
	case FADE_NONE:
		break;
	case FADE_IN:
		g_fadeAlpha -= 0.01;

		//フェードインの終了チェック
		if (g_fadeAlpha <= 0.0f)
		{
			//フェードイン終了
			g_fadeState = FADE_NONE;
		}

		break;
	case FADE_OUT:
		g_fadeAlpha += 0.01;

		//フェードアウトの終了チェック
		if (g_fadeAlpha >= 1.0f)
		{
			//フェードアウト終了後INへ
			g_fadeState = FADE_IN;
			SCENE* pScene = GetScene();
			switch (*pScene)
			{
			case SCENE_TITLE:
				SetScene(SCENE_GAME);
				break;
			case SCENE_GAME:
				SetScene(SCENE_RESULT);
				break;
			case SCENE_RESULT:
				SetScene(SCENE_TITLE);
				break;
			case SCENE_GAMEOVER:
				SetScene(SCENE_TITLE);
				break;
			default:break;
			}
		}
		break;
	case FADE_SOUT:
		g_fadeAlpha += 0.01;

		//フェードアウトの終了チェック
		if (g_fadeAlpha >= 1.0f)
		{
			g_fadeState = FADE_IN;
			SetScene(SCENE_GAMEOVER);
		}
	default: break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFade(void)
{
	//フェードの描画

	PLAYER* pPlayer = GetPlayer();

	SCENE* pScene = GetScene();

	if (*pScene == SCENE_GAME)
	{
		if (pPlayer->pos.x <= 960.0f)
		{
			DrawSpriteColor(g_FadeTexNo,
				SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
				SCREEN_WIDTH, SCREEN_HEIGHT,
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, g_fadeAlpha);
		}
		else
		{
			DrawSpriteColor(g_FadeTexNo,
				pPlayer->pos.x, SCREEN_HEIGHT / 2,
				SCREEN_WIDTH, SCREEN_HEIGHT,
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, g_fadeAlpha);
		}
	}
	else 
	{
		DrawSpriteColor(g_FadeTexNo,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, g_fadeAlpha);
	}
}
//=============================================================================
// フェードのセット
//=============================================================================
void SetFade(FADE_MODE state)
{
	g_fadeState = state;

	if (g_fadeState == FADE_IN)
	{
		g_fadeAlpha = 1.0f;
	}
	else if(g_fadeState == FADE_OUT)
	{
		g_fadeAlpha = 0.0f;
	}
	else if (g_fadeState == FADE_SOUT)
	{
		g_fadeAlpha = 0.0f;
	}
}