// ===================================================
//	FieldEventBath.h		　フィールドイベントクラス
//	武藤海人								2024/01/14
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

	//まだ追加できるかをbool型で返す　要らないかも
	bool SetTriggerObject(FieldObject* fo);

	void SetTargetArry(int* arry);

	//指定した条件をクリアしたらマップの情報を書き換えるための関数
	virtual void Update() = 0;


	bool GetIsActive() { return _IsActive; }

protected:
	void GetFivePosition(D3DXVECTOR2& pos, D3DXVECTOR2& wh, int& lt, int& rt, int& lb, int& rb, int& st);

	bool GetMapPositionCollider(int& map, int& lt, int& rt, int& lb, int& rb, int& st);

	bool GetMapPositionCollider(D3DXVECTOR2& pos, D3DXVECTOR2& wh, int& map);

protected:

	bool _IsActive = true;		//使ったらfalseにする　デリートはたぶんしない

	//フィールドイベントを起動するためのオブジェクトの情報
	const int _TRIGGER_ARRY_SIZE;
	int _TriggerNum = 0;
	FieldObject** _TriggerObjectArry = nullptr;

	//フィールドイベントを実行するマップのポインタ
	Map* _MapP = nullptr;

	//フィールドをどう変えるかを記憶するところ
	const int _TARGET_ARRY_SIZE;
	//int* _TargetArry = nullptr;
	std::vector<int> _TargetArry;
	int _Next = 0;
};

#endif // !FIELD_EVENT_BATH_H