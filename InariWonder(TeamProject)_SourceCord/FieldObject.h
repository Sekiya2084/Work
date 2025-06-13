// ===================================================
// FieldObject.h							���N���X
//	�����C�l								2023/11/22
// ===================================================

#pragma once

#ifndef FIELD_OBJECT_H
#define FIELD_OBJECT_H

#include "main.h"
class FieldObjectManager;

///
///  ��
/// 

typedef enum {
	KIND_NULL,
	KIND_PLAYER,				//�v���C���[
	KIND_PLAYER_FIRE,
	KIND_PLAYER_ABILITY,		//�v���C���[�̃A�r���e�B
	KIND_PLAYER_BULLET,			//�v���C���[�̒e
	KIND_PLAYER_HEALAREA,		//�v���C���[�̉񕜔͈�
	KIND_FOX,					//��
	KIND_FOX_ABILITY,			//�ς̃A�r���e�B
	KIND_FOX_FIRE,
	KIND_FOX_TACKLE,
	KIND_ENEMY,					//�G
	KIND_ENEMY_FIRE,
	KIND_ENEMY_ICE,
	KIND_ENEMY_TACKLE,
	KIND_BOSS_LEFT,
	KIND_BOSS_RIGHT,
	KIND_BOSS_ICE,
	KIND_OBJECT,				//�؍ނȂǂ̏��
	KIND_WOOD,
	KIND_MAX
}FIELD_OBJECT_KIND;	//�I�u�W�F�̎��

typedef enum {
	LOOK_RIGHT = 0,
	LOOK_UP = 1,
	LOOK_LEFT = 2,
	LOOK_DOWN = 3
}LOOK;

/// <summary>
/// �\���� 
/// </summary>

typedef struct OBJECT_DATA {
	OBJECT_DATA() {};
	OBJECT_DATA(D3DXVECTOR2 p, D3DXVECTOR2 op, D3DXVECTOR2 s, float r, FIELD_OBJECT_KIND fok);

	D3DXVECTOR2 pos;		//�ꏊ
	D3DXVECTOR2 oldPos;		//�̂̏ꏊ
	D3DXVECTOR2 size;		//�`��p�ABB�Ɏg������̑傫��
	float range;			//Trigger����Ɏg���O�ϗp
	FIELD_OBJECT_KIND kind;
}OBJECT_DATA;


class Map;

//�N���X

class FieldObject
{
public:
	FieldObject(FieldObjectManager* myfom, const D3DXVECTOR2& p = { 0,0 }, const D3DXVECTOR2& op = { 0,0 }, const D3DXVECTOR2& s = { 100,100 }, const float& r = 50, const FIELD_OBJECT_KIND& fok = KIND_NULL)
		:_ObjectData(OBJECT_DATA(p, op, s, r, fok)), _MyManager(myfom){};
	FieldObject(OBJECT_DATA od)
		:_ObjectData(OBJECT_DATA(od)) {};

	

	const OBJECT_DATA& GetObjectData() {return _ObjectData;}

	virtual bool GetHitTrigger(const OBJECT_DATA& od) = 0;			//���������u��
	virtual bool GetHitStay(const OBJECT_DATA& od) = 0;				//�������Ă��鎞

	virtual void Hit(const OBJECT_DATA& od) = 0;					//�����������̏���

	virtual bool GetIsDead() { return _IsDead; }					//�폜���邱�Ƃ�`����֐��A����������Ȃ炢�����Ă悵
	virtual bool GetIsActive() { return _IsActive; }				//�폜���邱�Ƃ�`����֐��A����������Ȃ炢�����Ă悵

	virtual const D3DXVECTOR2& GetMoveValue() { return D3DXVECTOR2(0.0f,0.0f); };	//���t���[���ňړ��������ő��
	virtual void SetMoveValue(const D3DXVECTOR2& move) { _ObjectData.pos += move; };					//�ǂꂾ���ړ��ł��邩���}�b�v�N���X����󂯎�邽�߂̂���

	void SetMapPointa(Map* map) { _MapP = map; };
	void SetFieldObjectManager(FieldObjectManager* fom) { _MyManager = fom; }
	/*
	��
	if(GetHitTrigger(od)){
		od.Hit(this);			//�����������Ƃ�od�ɒm�点��B���\�[�X�̏���Ȃ�A�N�[���^�C���̐ݒ�Ȃ�A�A�C�e���Ȃ炱���ŏ����悤�ɏ���
		this.Hit(od);			//�����������Ƃ������ɒm�点��
	}
	*/

	virtual void UpdateStart() = 0;
	virtual void Update() = 0;
	virtual void UpdateEnd() = 0;

	virtual void Draw(const D3DXVECTOR2& decrement) const = 0;

protected:
	Map* _MapP = nullptr;

	OBJECT_DATA _ObjectData;

	bool _IsDead = false;
	bool _IsActive = false;

	FieldObjectManager* _MyManager = nullptr;

	void SetIsDead() { _IsDead = true; }
};



#endif // !FIELD_OBJECT_H