#pragma once
#ifndef ENEMY_H
#define ENEMY_H
/*------------------------------------------------------------------------------

		�L�c�l�Ǘ�[Enemy.h]

											Date:2023/11/21
											creator:�������I
------------------------------------------------------------------------------*/


#include "FieldObject.h"

#include "texture.h"

#include "sprite.h"

/*
	�G�̈���

	�Ǘ���
	�ʒu
	���x
	�ŏ��̌���
	���ɐi�ރ}�X��
	�c�ɐi�ރ}�X��
	���v��肩(true�Ȃ玞�v���)
	�U���J�n����
	���싗��
	����p(0 �` 359)

* /

/*
�@�ړ�
	�ړI�n��ݒ肷��֐�
	�ړI�n�܂ňړ�����֐�
	�ړI�n�őҋ@����֐�

�@���G
	������������Ƃ���ƍ��G�Ώۂ�����ꏊ�̍�������p�x���擾���āA���̊p�x�����ȓ���������True��Ԃ�
	�������w�肷��֐��@�A�j���[�V�����ł��g��
*/

typedef enum
{
	ENEMY_KARAKASA,
	ENEMY_TYOTSIN,
	ENEMY_YUKIONNA,
	ENEMY_ID_MAX
}ENEMY_ID;


typedef enum {
	GO,			// �ړI�n�ɍs��
	STAY,		// �ړI�n�őҋ@
	BACK,		// �ړI�n����A��

	SHUTTLRUN,	// �K��s��

	ATTACK,		// �U��
}ENEMY_MOVE_MODE;

class MouseGetter;

class Player;
class Fox;

class Enemy :public FieldObject
{
protected:
	const int TEXTURE_NUMBER[3] = { 
		LoadTexture((char*)"data/TEXTURE/enemy1.png"),
		LoadTexture((char*)"data/TEXTURE/enemy2.png"),
		LoadTexture((char*)"data/TEXTURE/enemy3.png")
	};

	Player* _Player;
	Fox* _Fox;

	static const int ENEMY_TEXTURE_DIVISION_NUM_X = 4;	// �e�N�X�`���̉�������
	static const int ENEMY_TEXTURE_DIVISION_NUM_Y = 4;	// �e�N�X�`���̏c������

	static const float ENEMY_TEXTURE_DIVISION_X;
	static const float ENEMY_TEXTURE_DIVISION_Y;

	bool _Move = false;

	D3DXVECTOR2 _Vec = D3DXVECTOR2(0.0f,0.0f);

	float _Dis = 0.0f;		// ����

	float _Speed = 1.0f;	// �ړ��X�s�[�h

	int _Life = 3;		// �̗�

	ENEMY_MOVE_MODE _EMM = SHUTTLRUN;					// �s�����[�h
	int _Range = 500;									// ���G�͈�
	int _ViewingAngle = 90;								// ����p
	FieldObject* _TargetP = nullptr;				// ���������G�̃|�C���^�[���Ƃ�
	D3DXVECTOR2 _OldPos = D3DXVECTOR2(0.0f, 0.0f);		// �G�����O�̈ʒu
	int _OldDis = 0;									// �G�����O�̖ڕW�܂ł̋���
	D3DXVECTOR2 _OldVec = D3DXVECTOR2(0.0f, 0.0f);		// �G�����O�̃x�N�g��

	D3DXVECTOR2 _KBVec = {0.0f,0.0f};
	LOOK _ProtoLook;
	bool _NowKB = false;

	int _AttackCnt = 0;

	int _AttackRange = 0;								// �U���̎˒� �ɂ�񂱑�푈�݂����Ɏ˒����ɂȂ�����U���J�n

	int _AnimeCnt = 0;
	int _PatternCnt = 0;

	bool _CW;		// ���v���ɉ�邩�����v���ɉ񂷂�

	const bool& Movement(const bool& f = true);

	void Go(void);
	void Stay(void);
	void Back(void);

	void ShuttlRun(void);

	virtual void Attack(void) = 0;

	void Move(void);
	
	void SetTarget(const ENEMY_MOVE_MODE& emm, const D3DXVECTOR2& v, const float& l);	// �^�[�Q�b�g�ݒ�@�}�E�X��T�m�͈͓��ɓG��I�u�W�F�N�g����������

	void DiviVec(const LOOK& d);

	LOOK _Direction = LOOK_DOWN;

	D3DXVECTOR2 _EUv = D3DXVECTOR2(0.0f, 0.0f);
	static const D3DXVECTOR2 _EUvW;

	void SetDirection(void);
	void SetDirection(const D3DXVECTOR2& vec);

	void SetUv(void);

	ENEMY_ID _Id = ENEMY_ID_MAX;

	int _MoveSquareX = 0;		// ���ɉ��}�X�i�ނ�
	int _MoveSquareY = 0;		// �c�ɉ��}�X�i�ނ�

	const D3DXVECTOR2& KnockBack(void);
	int _KBCnt = 0;

public:
	// moveX��moveY�̓}�X��
	Enemy(FieldObjectManager* myfom, const D3DXVECTOR2& p = { 0,0 }, const float& speed = 5, const LOOK& ed = LOOK_RIGHT, const int& moveX = 3, const int& moveY = 3, const bool& cw = false,
		const int& attackRenge = 0, const int& range = 500,const int& va = 90, const D3DXVECTOR2& s = { 72,102 }, const float& r = 50, const ENEMY_ID& id = ENEMY_ID_MAX);
	virtual ~Enemy() {
		_TargetP = nullptr;
	}


	bool GetHitTrigger(const OBJECT_DATA& od) override { return true; }			//���������u��
	bool GetHitStay(const OBJECT_DATA& od) override { return true; }			//�������Ă��鎞

	void Hit(const OBJECT_DATA& od) override {}									//�����������̏���


	void SetObjectMove(FieldObject* fop, const ENEMY_MOVE_MODE& emm = GO);

	void SetKnockBack(const D3DXVECTOR2& v);
	const int& GetLife(void) { return _Life; }
	void SetLife(const int& attack) {
		_Life -= attack;
		_Life = (_Life < 0 ? 0 : _Life);
	}

	const D3DXVECTOR2& GetMoveValue() override;
	void SetMoveValue(const D3DXVECTOR2& move) override;


	void UpdateStart(void)override;
	void Update(void)override {}
	void UpdateEnd(void)override;

	void Draw(const D3DXVECTOR2& decrement) const override { DrawSprite(TEXTURE_NUMBER[_Id], _ObjectData.pos - decrement, _ObjectData.size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), _EUv, _EUvW, 0.0f); }
};

#endif // !ENEMY_H

// �G�͂��Ƃ̂����̂��ǂ�