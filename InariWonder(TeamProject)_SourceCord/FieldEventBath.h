// ===================================================
//	FieldEventBath.h		�@�t�B�[���h�C�x���g�N���X
//	�����C�l								2024/01/14
// ===================================================

#pragma once
#ifndef FIELD_EVENT_BATH_H
#define FIELD_EVENT_BATH_H
#include "main.h"
#include <vector>

class FieldObject;
class Map;

class FieldEventBath
{
public:
	FieldEventBath(Map* map, int trigger, int target,int next);
	~FieldEventBath();

	//�܂��ǉ��ł��邩��bool�^�ŕԂ��@�v��Ȃ�����
	bool SetTriggerObject(FieldObject* fo);

	void SetTargetArry(int* arry);

	//�w�肵���������N���A������}�b�v�̏������������邽�߂̊֐�
	virtual void Update() = 0;


	bool GetIsActive() { return _IsActive; }

protected:
	void GetFivePosition(D3DXVECTOR2& pos, D3DXVECTOR2& wh, int& lt, int& rt, int& lb, int& rb, int& st);

	bool GetMapPositionCollider(int& map, int& lt, int& rt, int& lb, int& rb, int& st);

	bool GetMapPositionCollider(D3DXVECTOR2& pos, D3DXVECTOR2& wh, int& map);

protected:

	bool _IsActive = true;		//�g������false�ɂ���@�f���[�g�͂��Ԃ񂵂Ȃ�

	//�t�B�[���h�C�x���g���N�����邽�߂̃I�u�W�F�N�g�̏��
	const int _TRIGGER_ARRY_SIZE;
	int _TriggerNum = 0;
	FieldObject** _TriggerObjectArry = nullptr;

	//�t�B�[���h�C�x���g�����s����}�b�v�̃|�C���^
	Map* _MapP = nullptr;

	//�t�B�[���h���ǂ��ς��邩���L������Ƃ���
	const int _TARGET_ARRY_SIZE;
	//int* _TargetArry = nullptr;
	std::vector<int> _TargetArry;
	int _Next = 0;
};

#endif // !FIELD_EVENT_BATH_H