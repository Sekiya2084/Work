// ===================================================
//	FieldEvent_TwinSwitch.h		　フィールドイベント_ツインスイッチ
//	武藤海人								2024/01/15
// ===================================================


#pragma once
#ifndef FIELD_EVENT_BATH_TWIN_SWITCH_H
#define	FIELD_EVENT_BATH_TWIN_SWITCH_H

#include "FieldEventBath.h"

class FieldEvent_TwinSwitch:public FieldEventBath
{
public:
	FieldEvent_TwinSwitch(Map* map, int targetNum,int next);

	//押されるスイッチのマップ内での場所を設定する関数
	void SetTwinSwitch(int miko, int fox) { _TwinSwitch_Miko = miko; _TwinSwitch_Fox = fox; }

	// FieldEventBath を介して継承されました
	void Update() override;

private:

private:
	int _TwinSwitch_Miko;
	int _TwinSwitch_Fox;
};


#endif // !FIELD_EVENT_BATH_H