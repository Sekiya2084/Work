// ----------------------------------------------------------
// �X�R�A���� [score.cpp]  
// �֒J�E�l�@2023/09/14 
// ----------------------------------------------------------

// ----------------------------------------------------------
// �C���N���[�h
// ----------------------------------------------------------
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "player.h"

// ----------------------------------------------------------
// �}�N����`
// ----------------------------------------------------------


// ----------------------------------------------------------
// �O���[�o���ϐ�
// ----------------------------------------------------------
static int g_ScoreTexNo = 0;
SCORE			g_Score;		//����

// ----------------------------------------------------------
// ������
// ----------------------------------------------------------
void InitScore()
{
	g_ScoreTexNo = LoadTexture((char*)"data/TEXTURE/number.png");


	//���̂̏�����
	g_Score.pos = D3DXVECTOR2(100.0f, 100.0f);
	g_Score.size = D3DXVECTOR2(100.0f, 100.0f);
	g_Score.score = 0;
}

// ----------------------------------------------------------
// �X�R�A
// ----------------------------------------------------------
void UninitScore()
{

}

// ----------------------------------------------------------
// �X�R�A�X�V
// ----------------------------------------------------------
void UpdateScore()
{

}

// ----------------------------------------------------------
// �X�R�A�`��
// ----------------------------------------------------------
void DrawScore()
{
	//���H�p�̃X�R�A
	int score = g_Score.score;

	for (int i = 0; i < SCORE_DIGIT; i++)
	{

		PLAYER* pPlayer = GetPlayer();

		//���H��
		//10�Ŋ��邱�Ƃɂ����1�̈ʂ�����o��
		int number = score % 10;
		//�V�t�g���Z
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