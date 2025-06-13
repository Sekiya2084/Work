/*==============================================================================

   �v���C���[�Ǘ� [player.cpp]
														 Author :�֒J�@�E�l
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
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER g_Player; //����

static int g_PlayerTexNo = 0;
static int g_ShotSeNo = 0;

float yadd = 0.0f;
float rxadd = 0.0f;
float lxadd = 0.0f;

static int g_AnimePattern = 0;
static int g_AnimeSkipFrame = 0;

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	ID3D11Device* pDevice = GetDevice();

	//�T�E���h�̓ǂݍ���
	g_ShotSeNo = LoadSound((char*)"data/SE/jamp.wav");

	//�e�N�X�`���̓ǂݍ���
	g_PlayerTexNo = LoadTexture((char*)"data/TEXTURE/player.png");

	//������
	g_Player.use = false;
	g_Player.Jtrigger = true;
	g_Player.uv = D3DXVECTOR2(0.0f, 0.0f);
	/*g_Player.oldpos = g_Player.pos;*/
	
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;

	SetPlayer(D3DXVECTOR2(960.0f, 900.0f), D3DXVECTOR2(54.0f, 54.0f));
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	//1�t���[���O���i�[
	g_Player.oldpos = g_Player.pos;
	
	//�j���[�g�����|�[�Y
	g_Player.uv.x = 0.0f;

//�W�����v����
	//�L�[�{�[�h
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

			//�{�����[������
			SetVolume(g_ShotSeNo, 0.6f);

			g_Player.Jtrigger = false;
		}
	}

//y�������x
	g_Player.pos.y += yadd;
	yadd += 0.6f;

//�W�����v�̕`��
	if (g_Player.Jtrigger == false)
	{
		g_AnimePattern = 4.0f;
		g_Player.uv.x = 0.2f * g_AnimePattern;
	}
	else
	{
		
	}

//�f�o�b�O���̒n�ʔ��� -> ���S����
	if(g_Player.pos.y > SCREEN_HEIGHT)
	{
		g_Player.use = false;
	}
	
//�_�b�V������
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

//��_�b�V�����̈ړ�
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

//x�������x
	g_Player.pos.x += (rxadd + lxadd);
	if (lxadd <= 0.0f)
	{
		lxadd += 0.3f;
	}

	if (rxadd >= 0.0f)
	{
		rxadd -= 0.3f;
	}

	////�e����
	//if (GetKeyboardTrigger(DIK_B))
	//{
	//	SetBullet(g_Player.pos - D3DXVECTOR2(0.0f,g_Player.size.y / 2), D3DXVECTOR2(0.0f, -15.0f), D3DXVECTOR2(75, 75));
	//	//SE�𗬂�
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	//�v���C���[�̕`��
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
// ���̂̃A�h���X�擾�֐�
//=============================================================================
PLAYER * GetPlayer()
{
	return &g_Player;
}

//=============================================================================
// �v���C���[�̃Z�b�g�֐�
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

//collision������y�������x���Z�b�g�p
void Setyadd(float add)
{
	yadd = add;
}