// ===================================================
//	FieldEvent_TwinSwitch.cpp		�@�t�B�[���h�C�x���g_�c�C���X�C�b�`
//	�����C�l								2024/01/15
// ===================================================


#include "FieldEvent_TwinSwitch.h"
#include "FieldObject.h"
#include "Map.h"

FieldEvent_TwinSwitch::FieldEvent_TwinSwitch(Map* map, int target,int next)
	:FieldEventBath(map, 2, target,next)
{
}

void FieldEvent_TwinSwitch::Update()
{
	if (_IsActive) {
		bool isFirst = false;
		bool isSecond = false;

		//1�l�ڂ̃g���K�[�̔���
		FieldObject* target = _TriggerObjectArry[0];
		int lt, rt, lb, rb, st;
		D3DXVECTOR2 wh = { target->GetObjectData().size.x * 0.5f, target->GetObjectData().size.y * 0.5f };
		D3DXVECTOR2 pos = target->GetObjectData().pos;

		GetFivePosition(pos, wh, lt, rt, lb, rb, st);

		if (lt == _TwinSwitch_Miko ||
			rt == _TwinSwitch_Miko ||
			lb == _TwinSwitch_Miko ||
			rb == _TwinSwitch_Miko ||
			st == _TwinSwitch_Miko
			)isFirst = true;
		if (lt == _TwinSwitch_Fox ||
			rt == _TwinSwitch_Fox ||
			lb == _TwinSwitch_Fox ||
			rb == _TwinSwitch_Fox ||
			st == _TwinSwitch_Fox
			)isSecond = true;

		//��l�ڂ̃g���K�[�̔���
		target = _TriggerObjectArry[1];
		wh = { target->GetObjectData().size.x * 0.5f, target->GetObjectData().size.y * 0.5f };
		pos = target->GetObjectData().pos;

		GetFivePosition(pos, wh, lt, rt, lb, rb, st);

		if (lt == _TwinSwitch_Miko ||
			rt == _TwinSwitch_Miko ||
			lb == _TwinSwitch_Miko ||
			rb == _TwinSwitch_Miko ||
			st == _TwinSwitch_Miko
			)isFirst = true;
		if (lt == _TwinSwitch_Fox ||
			rt == _TwinSwitch_Fox ||
			lb == _TwinSwitch_Fox ||
			rb == _TwinSwitch_Fox ||
			st == _TwinSwitch_Fox
			)isSecond = true;

		if (isFirst && isSecond) {
			_MapP->SetChangeChips(_TargetArry, _TARGET_ARRY_SIZE, _Next);

			std::vector<int>but;
			but.push_back(_TwinSwitch_Miko); 
			_MapP->SetChangeChips(but, 1, 20);
			but.clear();

			but.push_back(_TwinSwitch_Fox);
			_MapP->SetChangeChips(but, 1, 21);
			_IsActive = false;
		}
	}
}

