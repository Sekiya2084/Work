//=============================================================================
// �����蔻�菈�� [collision.cpp]
// 
// Author : �֒J�@�E�l
//			2023/06/29
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "block.h"
#include "map.h"
#include "fade.h"
#include "score.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
bool CollisionBCSq(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
bool swc = true;

void InitCollision(void)
{
	swc = true;
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(void)
{
	// �|�C���^�[�̎擾
	PLAYER* pPlayer = GetPlayer();
	BULLET* pBullet = GetBullet();
	ENEMY* pEnemy = GetEnemy();
	BLOCK* pBlock = GetBlock();
	SCENE* pScene = GetScene();
	
	
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY; enemyCnt++)
	{//�u���b�N�̏�����`�F�b�N
		if ((pEnemy + enemyCnt)->use)
		{//�g�p���Ă�G�����`�F�b�N
			if (pPlayer->use)
			{//�g�p���Ă���v���C���[�����`�F�b�N����
				//old����ɂ����l��
				float OldPlayerTop = pPlayer->oldpos.y - pPlayer->size.y / 2;
				float OldPlayerBottom = pPlayer->oldpos.y + pPlayer->size.y / 2;
				float OldPlayerLeft = pPlayer->oldpos.x - pPlayer->size.x / 2;
				float OldPlayerRight = pPlayer->oldpos.x + pPlayer->size.x / 2;

				float EnemyTop = (pEnemy + enemyCnt)->pos.y - (pEnemy + enemyCnt)->size.y / 2;
				float EnemyBottom = (pEnemy + enemyCnt)->pos.y + (pEnemy + enemyCnt)->size.y / 2;
				float EnemyLeft = (pEnemy + enemyCnt)->pos.x - (pEnemy + enemyCnt)->size.x / 2;
				float EnemyRight = (pEnemy + enemyCnt)->pos.x + (pEnemy + enemyCnt)->size.x / 2;

				float PlayerTop = pPlayer->pos.y - pPlayer->size.y / 2;
				float PlayerBottom = pPlayer->pos.y + pPlayer->size.y / 2;
				float PlayerLeft = pPlayer->pos.x - pPlayer->size.x / 2;
				float PlayerRight = pPlayer->pos.x + pPlayer->size.x / 2;
				//BB
				if (EnemyBottom > PlayerTop &&
					EnemyRight > PlayerLeft &&
					EnemyLeft < PlayerRight &&
					EnemyTop < PlayerBottom)
				{
					bool hit = false;
					//�G�l�~�[���ƃv���C���[��
					if (EnemyBottom >= PlayerTop &&
						EnemyBottom <= OldPlayerTop)
					{
						pPlayer->use = false;
						hit = true;
					}
					//�G�l�~�[��ƃv���C���[��
					if (EnemyTop <= PlayerBottom &&
						EnemyTop >= OldPlayerBottom)
					{
						Setyadd(-7.0f);
						(pEnemy + enemyCnt)->use = false;
						AddScore(100);
					}
					//�u���b�N�E�ƃ{�[����
					if (EnemyRight >= PlayerLeft &&
						EnemyRight <= OldPlayerLeft)
					{
						pPlayer->use = false;
					}
					//�u���b�N���ƃ{�[���E
					if (EnemyLeft <= PlayerRight &&
						EnemyLeft >= OldPlayerRight)
					{
						pPlayer->use = false;
					}
				}
			}
		}
	}


	for (int blockCnt = 0; blockCnt < MAX_BLOCK; blockCnt++)
	{//�u���b�N�̏�����`�F�b�N
		if ((pBlock + blockCnt)->use)
		{//�g�p���Ă�G�����`�F�b�N
			if (pPlayer->use)
			{//�g�p���Ă���v���C���[�����`�F�b�N����
				//old����ɂ����l��
				float OldPlayerTop = pPlayer->oldpos.y - pPlayer->size.y / 2;
				float OldPlayerBottom = pPlayer->oldpos.y + pPlayer->size.y / 2;
				float OldPlayerLeft = pPlayer->oldpos.x - pPlayer->size.x / 2;
				float OldPlayerRight = pPlayer->oldpos.x + pPlayer->size.x / 2;

				float BlockTop = (pBlock + blockCnt)->pos.y - (pBlock + blockCnt)->size.y / 2;
				float BlockBottom = (pBlock + blockCnt)->pos.y + (pBlock + blockCnt)->size.y / 2;
				float BlockLeft = (pBlock + blockCnt)->pos.x - (pBlock + blockCnt)->size.x / 2;
				float BlockRight = (pBlock + blockCnt)->pos.x + (pBlock + blockCnt)->size.x / 2;

				float PlayerTop = pPlayer->pos.y - pPlayer->size.y / 2;
				float PlayerBottom = pPlayer->pos.y + pPlayer->size.y / 2;
				float PlayerLeft = pPlayer->pos.x - pPlayer->size.x / 2;
				float PlayerRight = pPlayer->pos.x + pPlayer->size.x / 2;
				//BB
				if (BlockBottom > PlayerTop &&
					BlockRight > PlayerLeft &&
					BlockLeft < PlayerRight &&
					BlockTop < PlayerBottom)
				{
					bool hit = false;
					//�u���b�N���ƃ{�[����
					if (BlockBottom >= PlayerTop &&
						BlockBottom <= OldPlayerTop)
					{
						Setyadd(0.0f);
						pPlayer->Jtrigger = true;
						pPlayer->pos.y = pPlayer->oldpos.y;
						hit = true;
					}
					//�u���b�N��ƃ{�[����
					if (BlockTop <= PlayerBottom &&
						BlockTop >= OldPlayerBottom)
					{
						Setyadd(0.0f);
						pPlayer->Jtrigger = true;
						pPlayer->pos.y = pPlayer->oldpos.y;
						hit = true;
					}
					//�u���b�N�E�ƃ{�[����
					if (BlockRight >= PlayerLeft &&
						BlockRight <= OldPlayerLeft)
					{
						pPlayer->pos.x = pPlayer->oldpos.x;
						hit = true;
					}
					//�u���b�N���ƃ{�[���E
					if (BlockLeft <= PlayerRight &&
						BlockLeft >= OldPlayerRight)
					{
						pPlayer->pos.x = pPlayer->oldpos.x;
						hit = true;
					}
					//�����������̋��ʏ���
					if (hit)
					{
						if (swc)
						{
							if ((pBlock + blockCnt)->type == 1)
							{
								SetFade(FADE_OUT);
								swc = false;
							}
						}
					}
				}
			}
		}
	}
	
	//�G�ƃu���b�N
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY; enemyCnt++)
	{//�e�̑������`�F�b�N
		if ((pEnemy + enemyCnt)->use)
		{//�g�p���Ă�e�����`�F�b�N����
			for (int blockCnt = 0; blockCnt < MAX_BLOCK; blockCnt++)
			{//�G�̑������`�F�b�N
				if ((pBlock + blockCnt)->use)
				{//�g�p���Ă���G�����`�F�b�N����
					if (CollisionBCSq((pEnemy + enemyCnt)->pos, (pBlock + blockCnt)->pos, (pEnemy + enemyCnt)->size.x / 2, (pBlock + blockCnt)->size.x / 2))
					{
						(pEnemy + enemyCnt)->vel *= -1;
					}
				}
			}
		}
	}

	// �e�ƓG
	//for (int bulletCnt = 0; bulletCnt < MAX_BULLET; bulletCnt++)
	//{//�e�̑������`�F�b�N
	//	if ((pBullet + bulletCnt)->use)
	//	{//�g�p���Ă�e�����`�F�b�N����
	//		for (int enemyCnt = 0; enemyCnt < MAX_ENEMY; enemyCnt++)
	//		{//�G�̑������`�F�b�N
	//			if ((pEnemy + enemyCnt)->use)
	//			{//�g�p���Ă���G�����`�F�b�N����
	//				if (CollisionBCSq((pBullet + bulletCnt)->pos, (pEnemy + enemyCnt)->pos, (pBullet + bulletCnt)->size.x / 2, (pEnemy + enemyCnt)->size.x / 2))
	//				{
	//					//�������Ă���Ƃ��̏���
	//					(pBullet + bulletCnt)->use = false; //�e����
	//					(pEnemy + enemyCnt)->use = false; //�G����
	//				}
	//			}
	//		}
	//	}
	//}

	//�v���C���[�ƃu���b�N


	// �{�X�ƒe

	// �����ƓG�̒e

}

//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X���̔���
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y���̔���
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//�S�Ă̏�����TRUE�Ȃ�q�b�g����
			return true;
		}
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistance�̃x�N�g�����𓾂�
	float length;
	length = D3DXVec2Length(&vDistance);

	//1��2�̔��a�𑫂�
	float size = size1 + size2;

	//���������a�ƃx�N�g�����Ƃő傫���𔻒肷��
	//�����̃x�N�g�����̕�����������΃q�b�g���Ă���
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBCSq(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistance�̃x�N�g������2��̒l�𓾂�
	float length;
	length = D3DXVec2LengthSq(&vDistance);

	//1��2�̔��a�𑫂���2�悷��
	float size = (size1 + size2) * (size1 + size2);

	//���������a�ƃx�N�g�����Ƃő傫���𔻒肷��
	//�����̃x�N�g�����̕�����������΃q�b�g���Ă���
	if (length < size)
	{
		return true;
	}

	return false;
}