// ----------------------------------------------------------
// スコア制御 [score.cpp]  
// 関谷勇人　2023/09/14 
// ----------------------------------------------------------

// ----------------------------------------------------------
// インクルード
// ----------------------------------------------------------
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "player.h"

// ----------------------------------------------------------
// マクロ定義
// ----------------------------------------------------------


// ----------------------------------------------------------
// グローバル変数
// ----------------------------------------------------------
static int g_ScoreTexNo = 0;
SCORE			g_Score;		//実体

// ----------------------------------------------------------
// 初期化
// ----------------------------------------------------------
void InitScore()
{
	g_ScoreTexNo = LoadTexture((char*)"data/TEXTURE/number.png");


	//実体の初期化
	g_Score.pos = D3DXVECTOR2(100.0f, 100.0f);
	g_Score.size = D3DXVECTOR2(100.0f, 100.0f);
	g_Score.score = 0;
}

// ----------------------------------------------------------
// スコア
// ----------------------------------------------------------
void UninitScore()
{

}

// ----------------------------------------------------------
// スコア更新
// ----------------------------------------------------------
void UpdateScore()
{

}

// ----------------------------------------------------------
// スコア描画
// ----------------------------------------------------------
void DrawScore()
{
	//加工用のスコア
	int score = g_Score.score;

	for (int i = 0; i < SCORE_DIGIT; i++)
	{

		PLAYER* pPlayer = GetPlayer();

		//加工↓
		//10で割ることによって1の位を割り出し
		int number = score % 10;
		//シフト演算
		score /= 10;

		g_Score.pos.x = 900.0f - g_Score.size.x * (SCORE_DIGIT - 1 - i);
		g_Score.pos.y = 100.0f;

		if (pPlayer->pos.x <= 960.0f)
		{
			DrawSprite(g_ScoreTexNo, 960.0f + g_Score.pos.x, g_Score.pos.y, g_Score.size.x, g_Score.size.y,
				number % SCORE_EFFECT_X * SCORE_EFFECT_W, number / SCORE_EFFECT_Y * SCORE_EFFECT_H, SCORE_EFFECT_W, SCORE_EFFECT_H);
		}
		else
		{
			DrawSprite(g_ScoreTexNo, pPlayer->pos.x + g_Score.pos.x, g_Score.pos.y, g_Score.size.x, g_Score.size.y,
				number % SCORE_EFFECT_X * SCORE_EFFECT_W, number / SCORE_EFFECT_Y * SCORE_EFFECT_H, SCORE_EFFECT_W, SCORE_EFFECT_H);
		}
	}
}
void AddScore(int value)
{
	g_Score.score = g_Score.score + value;
}