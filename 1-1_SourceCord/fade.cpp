/*==============================================================================

   �t�F�[�h�Ǘ� [fade.cpp]
														 Author :�֒J�E�l
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
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_FadeTexNo = 0;
float g_fadeAlpha;
FADE_MODE g_fadeState;

//=============================================================================
// ����������
//=============================================================================
void InitFade(void)
{
	ID3D11Device* pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	g_FadeTexNo = LoadTexture((char*)"data/TEXTURE/fade_white.png");

	g_fadeAlpha = 0.0f;
	g_fadeState = FADE_NONE;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	switch (g_fadeState)
	{
	case FADE_NONE:
		break;
	case FADE_IN:
		g_fadeAlpha -= 0.01;

		//�t�F�[�h�C���̏I���`�F�b�N
		if (g_fadeAlpha <= 0.0f)
		{
			//�t�F�[�h�C���I��
			g_fadeState = FADE_NONE;
		}

		break;
	case FADE_OUT:
		g_fadeAlpha += 0.01;

		//�t�F�[�h�A�E�g�̏I���`�F�b�N
		if (g_fadeAlpha >= 1.0f)
		{
			//�t�F�[�h�A�E�g�I����IN��
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

		//�t�F�[�h�A�E�g�̏I���`�F�b�N
		if (g_fadeAlpha >= 1.0f)
		{
			g_fadeState = FADE_IN;
			SetScene(SCENE_GAMEOVER);
		}
	default: break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFade(void)
{
	//�t�F�[�h�̕`��

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
// �t�F�[�h�̃Z�b�g
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