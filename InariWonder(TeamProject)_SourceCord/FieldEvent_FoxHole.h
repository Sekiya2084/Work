#pragma once
#ifndef FAIELD_EVENT_FOX_HOLE_H
#define FAIELD_EVENT_FOX_HOLE_H

#include "FieldEventBath.h"
#include "main.h"
#include <vector>

class FieldEvent_FoxHole :
    public FieldEventBath
{
public:
    FieldEvent_FoxHole(Map* map);   //mapはmap targetは狐の中継点の数 Vector型にしたからいらない
    // FieldEventBath を介して継承されました
    void Update() override;

    bool SetRoutePosition(D3DXVECTOR2 pos);

    void SetStartPos(int pos) { _StartPos = pos; }

private:
    void TriggerOn();                           //Atが-1の時に呼び出す
    void Move();                                //移動しつつLengthを短くする
    void NextTarget();                          //lengthが0になったら呼び出す関数、lengthの長さとAtを更新

private:
    float _Speed = 3.0f;                        //このイベント専用の移動速度
    std::vector<D3DXVECTOR2> _RoutePositionList;      //経由する地点を記憶するための配列
    D3DXVECTOR2 _Vel;                           //移動する向き

    int _At = -1;                               //状態、-1がマップとの当たり判定を取って、当たっていたら0にする、そこからlengthが0になったら次言ってレングスを更新の繰り返し
    float _Length = 0;                          //これが0になったらAtを増やす

    int _StartPos = 0;                          //どのチップを狐が踏んだらEvent開始かを記憶する関数
};

#endif // !FAIELD_EVENT_FOX_HOLE_H