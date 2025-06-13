// ===================================================
//	FieldEvent_SingleSwitch.h		　フィールドイベント_シングルスイッチ
//	武藤海人								2024/01/15
// ===================================================
#pragma once

#ifndef FIELD_EVENT_SINGLE_SWITCH_H
#define FIELD_EVENT_SINGLE_SWITCH_H
#include "FieldEventBath.h"


class FieldEvent_SingleSwitch
	:public FieldEventBath
{
public:
	FieldEvent_SingleSwitch(Map* map,int targetNum,int next);

	void SetSwitchPos(int pos) { _SwitchPos = pos; }

	// FieldEventBath を介して継承されました
	void Update() override;

protected:

	int _SwitchPos = 0;


};

#endif