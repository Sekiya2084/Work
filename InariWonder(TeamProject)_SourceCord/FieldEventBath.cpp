// ===================================================
//	FieldEventBath.cpp			�t�B�[���h�C�x���g�N���X
//	�����C�l								2023/11/22
// ===================================================
#include "FieldEventBath.h"
#include "FieldObject.h"
#include "Map.h"

FieldEventBath::FieldEventBath(Map* map, int trigger, int target,int next) 
	: _MapP(map), _TRIGGER_ARRY_SIZE(trigger), _TARGET_ARRY_SIZE(target),_Next(next)
{
	_TriggerObjectArry = new FieldObject * [trigger];
}

FieldEventBath::~FieldEventBath()
{
	_TargetArry.clear();
	delete[] _TriggerObjectArry;
}

bool FieldEventBath::SetTriggerObject(FieldObject* fo)
{
	//�󂯎�����Ώۂ�z��ɒǉ�
	_TriggerObjectArry[_TriggerNum] = fo;
	//�z��̒��g�̐����X�V
	_TriggerNum++;
	//���g���w�肳�ꂽ���Ɠ����ɂȂ�����false
	return (_TriggerNum < _TRIGGER_ARRY_SIZE) ? true : false;
}

void FieldEventBath::SetTargetArry(int* arry)
{
	for (int i = 0; i < _TARGET_ARRY_SIZE; i++) {
		_TargetArry.push_back(arry[i]);
	}
}

void FieldEventBath::GetFivePosition(D3DXVECTOR2& pos, D3DXVECTOR2& wh, int& lt, int& rt, int& lb, int& rb, int& st)
{
	int y, x;
	D3DXVECTOR2 at;
	{	//����
		at = pos - wh;
		x = (int)at.x / BLOCK_SIZE_X;
		y = (int)at.y / BLOCK_SIZE_Y;

		lt = y * _MapP->GetMapSizeX() + x;
	}

	{	//�E��
		at.y = pos.y - wh.y;
		at.x = pos.x + wh.x;
		x = (int)at.x / BLOCK_SIZE_X;
		y = (int)at.y / BLOCK_SIZE_Y;

		rt = y * _MapP->GetMapSizeX() + x;
	}

	{	//����
		at.y = pos.y + wh.y;
		at.x = pos.x - wh.x;
		x = (int)at.x / BLOCK_SIZE_X;
		y = (int)at.y / BLOCK_SIZE_Y;

		lb = y * _MapP->GetMapSizeX() + x;
	}

	{	//�E��
		at = pos + wh;
		x = (int)at.x / BLOCK_SIZE_X;
		y = (int)at.y / BLOCK_SIZE_Y;

		rb = y * _MapP->GetMapSizeX() + x;
	}

	{	//���S
		at = pos;
		x = (int)at.x / BLOCK_SIZE_X;
		y = (int)at.y / BLOCK_SIZE_Y;

		st = y * _MapP->GetMapSizeX() + x;
	}
}

bool FieldEventBath::GetMapPositionCollider(int& map, int& lt, int& rt, int& lb, int& rb, int& st)
{
	return (lt == map ||
		rt == map ||
		lb == map ||
		rb == map ||
		st == map)
		? true : false;
}

bool FieldEventBath::GetMapPositionCollider(D3DXVECTOR2& pos, D3DXVECTOR2& wh, int& map)
{
	int lt, rt, lb, rb, st;
	GetFivePosition(pos, wh, lt, rt, lb, rb, st);

	return GetMapPositionCollider(map, lt, rt, lb, rb, st);
}
