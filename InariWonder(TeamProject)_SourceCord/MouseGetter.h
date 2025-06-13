// ===================================================
// FieldObject.h					�}�E�X�����擾�N���X
//	�����C�l								2023/11/22
// ===================================================
#pragma once


#ifndef MOUSE_GETTER_H
#define MOUSE_GETTER_H

#include "main.h"
#include "Map.h"

///
///�\����
///

typedef struct {
	D3DXVECTOR2 sub;		//�}�E�X�̍��W�ƑΏۂ̍��W�̍����@�}�E�X�i�ړI�n�j�[�Ώہi���ݒn�j
	D3DXVECTOR2 vel;		//�}�E�X���Ώۂ���ǂ̕����ɂ��邩���L�����ĒP�ʉ~���������
	float		length;		//�O�p�֐��Ŏ擾�����Ώۂƃ}�E�X�̋���

}MOUSE_GETTER_DATA;

/// <summary>
/// �N���X
/// </summary>
class MouseGetter
{
public:
	MouseGetter() {};
	~MouseGetter() {};

	static MOUSE_GETTER_DATA GetMouseGetterData(const D3DXVECTOR2& pos);
	static MOUSE_GETTER_DATA GetMouseGetterDataWorld(const D3DXVECTOR2& worldPos);

	bool GetWindowOverMousePosition();//�E�B���h�E��Ƀ}�E�X�����邩�ǂ���

	static void SetMapPointa(Map* m);

private:

protected:

public:
	static Map* s_MapP;

};


#endif // !MOUSE_GETTER_H