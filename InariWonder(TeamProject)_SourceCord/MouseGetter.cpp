#include "MouseGetter.h"
#include "input.h"

Map* MouseGetter::s_MapP = nullptr;

MOUSE_GETTER_DATA MouseGetter::GetMouseGetterData(const D3DXVECTOR2& pos)
{
    MOUSE_GETTER_DATA ret;

    ret.sub = GetMousePosition() - pos;         //����

    ret.length = D3DXVec2Length(&ret.sub);      //�Ώۂ܂ł̒������擾

    D3DXVec2Normalize(&ret.vel, &ret.sub);      //sub��P�ʉ~���������̂�vel�ɓ����
    //ret.vel = { ret.sub.x / ret.length, ret.sub.y / ret.length }; //����ł������A�Ƃ��������Ԃ񂱂̂ق�������

    return ret;
}

MOUSE_GETTER_DATA MouseGetter::GetMouseGetterDataWorld(const D3DXVECTOR2& worldPos)
{
    //�}�b�v�̃|�C���^�������Ă����炱����g����A�����ĂȂ������牽�������ĂȂ����Ԃ�
    if (s_MapP != nullptr) {
        MOUSE_GETTER_DATA ret;

        ret.sub = GetMousePosition() - worldPos + s_MapP->GetDrawDecrement();         //����

        ret.length = D3DXVec2Length(&ret.sub);      //�Ώۂ܂ł̒������擾

        D3DXVec2Normalize(&ret.vel, &ret.sub);      //sub��P�ʉ~���������̂�vel�ɓ���� ����
        //ret.vel = { ret.sub.x / ret.length, ret.sub.y / ret.length }; //����ł������A�Ƃ��������Ԃ񂱂̂ق�������

        return ret;
    }
    return MOUSE_GETTER_DATA();
}

bool MouseGetter::GetWindowOverMousePosition()
{
    D3DXVECTOR2 pos = GetMousePosition();
    if (pos.x < 0 || pos.y < 0)return false;
    if (pos.x > SCREEN_WIDTH || pos.y > SCREEN_HEIGHT)return false;
    return true;
}

void MouseGetter::SetMapPointa(Map* m)
{
    s_MapP = m;
}
