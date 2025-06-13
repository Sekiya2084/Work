// ===================================================
//	FieldEvent_TwinSwitch.h		�@�t�B�[���h�C�x���g_�c�C���X�C�b�`
//	�����C�l								2024/01/15
// ===================================================


#pragma once
#ifndef FIELD_EVENT_BATH_TWIN_SWITCH_H
#define	FIELD_EVENT_BATH_TWIN_SWITCH_H

#include "FieldEventBath.h"

class FieldEvent_TwinSwitch:public FieldEventBath
{
public:
	FieldEvent_TwinSwitch(Map* map, int targetNum,int next);

	//�������X�C�b�`�̃}�b�v���ł̏ꏊ��ݒ肷��֐�
	void SetTwinSwitch(int miko, int fox) { _TwinSwitch_Miko = miko; _TwinSwitch_Fox = fox; }

	// FieldEventBath ����Čp������܂���
	void Update() override;

private:

private:
	int _TwinSwitch_Miko;
	int _TwinSwitch_Fox;
};


#endif // !FIELD_EVENT_BATH_H