#include "FieldEvent_SingleSwitch.h"
#include "FieldObject.h"
#include "Map.h"

FieldEvent_SingleSwitch::FieldEvent_SingleSwitch(Map* map, int triggerNum, int next)
	:FieldEventBath(map, 1, triggerNum, next)
{
}

void FieldEvent_SingleSwitch::Update()
{
	if (_IsActive) {
		FieldObject* target = *_TriggerObjectArry;
		int lt, rt, lb, rb, st;
		D3DXVECTOR2 wh = { target->GetObjectData().size.x * 0.5f, target->GetObjectData().size.y * 0.5f };
		D3DXVECTOR2 pos = target->GetObjectData().pos;

		GetFivePosition(pos, wh, lt, rt, lb, rb, st);

		if (GetMapPositionCollider(_SwitchPos, lt, rt, lb, rb, st)
			)
		{
			_MapP->SetChangeChips(_TargetArry, _TARGET_ARRY_SIZE, _Next);
			std::vector<int>but;
			but.push_back(_SwitchPos);
			_MapP->SetChangeChips(but, 1, 23);
			_IsActive = false;
		}
	}
}
