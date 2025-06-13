/*==============================================================================

   �Q�[���Ǘ� [game.cpp]
														 Author : �֒J�@�E�l
														 Date   : 2023/06/26
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "collision.h"
#include "input.h"
#include "sound.h"
#include "map.h"
#include "score.h"
#include "gameBG.h"

static int g_GameBGMNo = 0;
bool swg = true;

//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{
	InitGameBG();
	//�T�E���h�̓ǂݍ���
	g_GameBGMNo = LoadSound((char*)"data/BGM/mariost1.wav");

	//BGM�𗬂�
	PlaySound(g_GameBGMNo, -1);

	//�{�����[������
	SetVolume(g_GameBGMNo, 0.5f);

	InitCollision();
	// �v���C���[�Ǘ��̏���������
	InitPlayer();

	// �e�Ǘ��̏���������
	InitBullet();

	// �G�Ǘ��̏���������
	InitEnemy();

	//�}�b�v�̓ǂݍ���
	InitMap();

	//�X�R�A�̏���������
	InitScore();

	swg = true;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	UninitGameBG();

	// �v���C���[�Ǘ��̏I������
	UninitPlayer();

	// �e�Ǘ��̏I������
	UninitBullet();

	// �G�Ǘ��̏I������
	UninitEnemy();

	//�}�b�v�̏I������
	UninitMap();

	//�X�R�A�̏I������
	UninitScore();

	//�T�E���h�̒�~
	StopSoundAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	UpdateGameBG();
	//�����蔻��
	UpdateCollision();

	//�}�b�v�f�[�^�X�V
	UpdateMap();

	// �v���C���[�Ǘ��̍X�V����
	UpdatePlayer();

	// �e�Ǘ��̍X�V����
	UpdateBullet();

	// �G�Ǘ��̍X�V����
	UpdateEnemy();

	// �X�R�A�̍X�V����
	UpdateScore();

	PLAYER* pPlayer = GetPlayer();
	//���S���Q�[���I�[�o�[��ʂ֑J��
	if (!pPlayer->use && swg)
	{
		swg = false;
		SetFade(FADE_SOUT);
		//SetScene(SCENE_GAMEOVER);
		//SetFade(FADE_IN);
	}
	////�G���^�[�L�[�ŗ��E�ł���p
	//else if	(GetKeyboardTrigger(DIK_RETURN))
	//{
	//	SetFade(FADE_OUT);
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	DrawGameBG();
	//�}�b�v�`��
	DrawMap();

	// �v���C���[�Ǘ��̕`�揈��
	DrawPlayer();

	// �e�Ǘ��̕`�揈��
	DrawBullet();

	// �G�Ǘ��̕`�揈��
	DrawEnemy();

	//�X�R�A�`��
	DrawScore();
}
