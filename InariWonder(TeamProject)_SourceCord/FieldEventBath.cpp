// ===================================================
//	FieldEventBath.cpp			フィールドイベントクラス
//	武藤海人								2023/11/22
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
	//受け取った対象を配列に追加
	_TriggerObjectArry[_TriggerNum] = fo;
	//配列の中身の数を更新
	_TriggerNum++;
	//中身が指定された数と同じになったらfalse
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
	{	//左上
		at = pos - wh;
		x = (int)at.x / BLOCK_SIZE_X;
		y = (int)at.y / BLOCK_SIZE_Y;

		lt = y * _MapP->GetMapSizeX() + x;
	}

	{	//右上
		at.y = pos.y - wh.y;
		at.x = pos.x + wh.x;
		x = (int)at.x / BLOCK_SIZE_X;
		y = (int)at.y / BLOCK_SIZE_Y;

		rt = y * _MapP->GetMapSizeX() + x;
	}

	{	//左下
		at.y = pos.y + wh.y;
		at.x = pos.x - wh.x;
		x = (int)at.x / BLOCK_SIZE_X;
		y = (int)at.y / BLOCK_SIZE_Y;

		lb = y * _MapP->GetMapSizeX() + x;
	}

	{	//右下
		at = pos + wh;
		x = (int)at.x / BLOCK_SIZE_X;
		y = (int)at.y / BLOCK_SIZE_Y;

		rb = y * _MapP->GetMapSizeX() + x;
	}

	{	//中心
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
