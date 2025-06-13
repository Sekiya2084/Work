#pragma once
#ifndef FOX_H
#define FOX_H
/*------------------------------------------------------------------------------

		�L�c�l�Ǘ�[Fox.h]

											Date:2023/11/21
											creator:�������I
------------------------------------------------------------------------------*/


#include "FieldObject.h"

#include "texture.h"

#include "sprite.h"

#include "MouseGetter.h"

class Player;

class Enemy;

// �v���C���[�̂��ƂɋA������E���`���������邩�Ǐ]������

// �U����A�C�e�����Ƃ��Ă���̂��K�v?
typedef enum {
	RETURN_GO,		// �ړI�n�ɍs��
	RETURN_STAY,	// �ړI�n�őҋ@
	RETURN_BACK,	// �ړI�n����A��
	STAY_GO,		// �ړI�n�ɍs��
	STAY_STAY,		// �ړI�n�ł����Ƒҋ@
	FREE_FOLLOW,	// ���Ă���
	FREE_FREE,		// �E���`����
	BACK_BACK,		// �����A�Ғ� �������Ԓ��͉��̎w�����󂯂Ă��������ĕԂ�
	TACKLE,
}MOVE_MODE;

class Fox :public FieldObject
{
private:
	const unsigned int FOX_TEXTURE_NUMBER = LoadTexture((char*)"data/TEXTURE/kitsune.png");

	static const int FOX_TEXTURE_DIVISION_NUM_X = 4;	// �e�N�X�`���̉�������
	static const int FOX_TEXTURE_DIVISION_NUM_Y = 4;	// �e�N�X�`���̏c������

	static const float FOX_TEXTURE_DIVISION_X;
	static const float FOX_TEXTURE_DIVISION_Y;

	Player* _Player = nullptr;

	static const int SPEED_MAX = 5.0f;	// �ړ��X�s�[�h
	int _Speed = SPEED_MAX;	// �ړ��X�s�[�h

	
	MouseGetter _Mouse;
	bool _IsMoveInput = true;

	static const int COME_RANGE = 200;		// �L�c�l�̒T�m�͈�
	static const int _AttackRange = 100;

	D3DXVECTOR2 _Vec = D3DXVECTOR2(0.0f,0.0f);	// �͂̓�������

	float _Dis = 0.0f;		// ����	�����蔻�肪 true �ɂȂ�����0�ɂ���

	D3DXVECTOR2 _KBVec = { 0.0f,0.0f };
	LOOK _ProtoLook;


	int _AnimeCnt = 0;
	int _PatternCnt = 0;

	MOVE_MODE _MoveMode = FREE_FOLLOW;		// �s�����[�h

	LOOK _Direction = LOOK_DOWN;

	D3DXVECTOR2 _FUv = D3DXVECTOR2(0.0f, 0.0f);
	static const D3DXVECTOR2 _FUvW;

	Enemy* _Target = nullptr;								// ���������^�[�Q�b�g

	int		_Life = 100;							// ���C�t

	bool	_Fleaz = false;

	bool	_NowKB = false;				// �m�b�N�o�b�N����

	bool	_FireAbility = false;				// ���X�L������

	bool lookFlag = false;
	bool _ReturnFlag = false;


	//void SetVecDis(D3DXVECTOR2& vec, float& dis, const OBJECT_DATA& od);	�����v�Z���悭���Ă���̂łȂ񂩊֐����~��������芸������

	// ���̕ӃL�c�l�̍s�����[�h�̓z
	const bool& Movement(const bool& f = true);		// �ړI�n�ɒ�������true

	void MoveGo(void);							// �����͍s�����������珈�����e�͑O��Move�Ɠ���
	void MoveStay(void);						// �X�e�C�@RETURN�Ȃ琔�b�ҋ@ STAY�Ȃ�w���҂��ҋ@
	void MoveBack(void);						// �o�b�N�@�Ƃ������ޏ��ɋ߂Â�
	void MoveFree(void);						// �E���`����
	void Back(void);							// �����A��
	
	void SetTarget(const MOVE_MODE& mm, const D3DXVECTOR2& v, const float& l);	// �^�[�Q�b�g�ݒ�@�}�E�X��T�m�͈͓��ɓG��I�u�W�F�N�g����������

	void SetBack(void);			// �ޏ��֋����A��

	const bool& AttackPossible(void);

	// �ړ����W�b�N�̏���
	void Move(void);

	void SetDirection(void);

	void SetUv(void);

	void SetVecLen(const D3DXVECTOR2& goal);
	const D3DXVECTOR2& KnockBack(void);

	void Attack(void);
public:
	Fox(FieldObjectManager* myfom,Player* player,D3DXVECTOR2 p = { 800,550 }, D3DXVECTOR2 s = { 70,70 }, float r = 50) :FieldObject(myfom,p,p,s,r, KIND_FOX),_Player(player){}
	virtual ~Fox() {}

	// ==========================================================================================================
	// �Ԃ�l�͈ړ��ł��邩��
	const bool& GetObjectColliderFlag(const OBJECT_DATA& od, const D3DXVECTOR2 move) {};
	// �Ԃ�l�͂ǂ̗ʈړ��ł��邩�̈ړ���
	const D3DXVECTOR2& GetMoveValue(const OBJECT_DATA& od, const D3DXVECTOR2 move) {};
	// ==========================================================================================================

	bool GetHitTrigger(const OBJECT_DATA& od) override;							//���������u��
	bool GetHitStay(const OBJECT_DATA& od) override { return true; }			//�������Ă��鎞

	void Hit(const OBJECT_DATA& od) override {}									//�����������̏���

	void SetObjectMove(FieldObject* fop);		// �I�u�W�F�N�g�ɂ�郀�[�u�t���O

	void UpdateStart(void)override;
	void Update(void)override;
	void UpdateEnd(void)override;

	void Draw(const D3DXVECTOR2& decrement) const override { DrawSprite(FOX_TEXTURE_NUMBER, _ObjectData.pos - decrement, _ObjectData.size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), _FUv, _FUvW, 0.0f); }

	void SetDis(void) { _Dis = 0; }

	const D3DXVECTOR2& GetMoveValue(void) override;
	void SetMoveValue(const D3DXVECTOR2& move) override;

	void SetIsMoveInput(bool flug) { _IsMoveInput = flug; }

	const bool& GetFA(void) { return _FireAbility; }
	void SetFA(void) { _FireAbility = true; }

	const int& GetLife(void)const { return _Life; }
	void SetLife(const int& attack) { 
		_Life -= attack;
		_Life = _Life < 0 ? 0 : _Life;
	}

	void SetKnockBack(const D3DXVECTOR2& v);
};

#endif // !FOX_H

//D3DXVec2LengthSq

/*
�K�v�Ȋ֐��i�z��
		�@MoveGo		GO���[�h���ׂĂɗ��p�\
		�@MoveStay		STAY���[�h���ׂĂɗ��p�\
		�@MoveBack		BACK��FOLLOW�ɗ��p�\�@FOLLOW�̏ꍇ�͕ʓr�ޏ��Ƃ̋����ł̃t���O�����߂���
		�@FOLLOW�͈��͈͊O����o����v���C���[�̂��Ƃ֍s��
		�@MoveFree		FREE�ɂ̂ݎg��
		�@SetTarget		�ړI�n��ݒ肷��֐��@������RETURN��STAY�����w�肷��΃��[�h�̈ڍs���X���[�Y���� ����͂قڏI����Ă�
		�@SetBack		�ⓚ���p��Back�ɂ���֐��@STAY���̌ς��Ăі߂�����AGO���̌ς��L�����Z���śޏ��ɖ߂�悤�ɂ���
* */