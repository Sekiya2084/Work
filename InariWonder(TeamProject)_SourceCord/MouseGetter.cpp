#include "MouseGetter.h"
#include "input.h"

Map* MouseGetter::s_MapP = nullptr;

MOUSE_GETTER_DATA MouseGetter::GetMouseGetterData(const D3DXVECTOR2& pos)
{
    MOUSE_GETTER_DATA ret;

    ret.sub = GetMousePosition() - pos;         //差分

    ret.length = D3DXVec2Length(&ret.sub);      //対象までの長さを取得

    D3DXVec2Normalize(&ret.vel, &ret.sub);      //subを単位円化したものをvelに入れる
    //ret.vel = { ret.sub.x / ret.length, ret.sub.y / ret.length }; //これでもいい、というかたぶんこのほうが早い

    return ret;
}

MOUSE_GETTER_DATA MouseGetter::GetMouseGetterDataWorld(const D3DXVECTOR2& worldPos)
{
    //マップのポインタが入っていたらこれを使える、入ってなかったら何も入ってないやつを返す
    if (s_MapP != nullptr) {
        MOUSE_GETTER_DATA ret;

        ret.sub = GetMousePosition() - worldPos + s_MapP->GetDrawDecrement();         //差分

        ret.length = D3DXVec2Length(&ret.sub);      //対象までの長さを取得

        D3DXVec2Normalize(&ret.vel, &ret.sub);      //subを単位円化したものをvelに入れる 方向
        //ret.vel = { ret.sub.x / ret.length, ret.sub.y / ret.length }; //これでもいい、というかたぶんこのほうが早い

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
