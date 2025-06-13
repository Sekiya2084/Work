// ===================================================
// FieldObject.cpp							���N���X
//	�����C�l								2023/11/22
// ===================================================
#include "FieldObject.h"
#include "FieldObjectManager.h"


OBJECT_DATA::OBJECT_DATA(D3DXVECTOR2 p, D3DXVECTOR2 op, D3DXVECTOR2 s, float r, FIELD_OBJECT_KIND fok)
	:pos(p), oldPos(op), size(s), range(r), kind(fok)
{}

//bool ObjectFox::GetHitTrigger(const OBJECT_DATA& od)
//{
//	return false;
//}
//
//bool ObjectFox::GetHitStay(const OBJECT_DATA& od)
//{
//	return false;
//}
//
//bool ObjectFox::GetHitSarchArea(const OBJECT_DATA& od)
//{
//	//����
//	D3DXVECTOR2 sub = _ObjectData.pos - od.pos;
//	//����
//	float dis = D3DXVec2Length(&sub);
//	//���ۂ̋������݂��̋���������̑傫���ƃT�[�`�͈͂�菬����������
//	return (od.range + _SarchRange >= dis) ? true : false;
//}
//
//bool ObjectFox::GetHitActionArea(const OBJECT_DATA& od)
//{
//	//����
//	D3DXVECTOR2 sub = _ObjectData.pos - od.pos;
//	//����
//	float dis = D3DXVec2Length(&sub);
//	//���ۂ̋������݂��̋���������̑傫���ƃT�[�`�͈͂�菬����������
//	return (od.range + _ActionRange >= dis) ? true : false;
//}
