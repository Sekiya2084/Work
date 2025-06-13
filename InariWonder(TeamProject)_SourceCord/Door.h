#ifndef DOOR_H
#define DOOR_H
#pragma once

#include "FieldObject.h"
#include "texture.h"

#define ANIM_TIME (60)      //�A�j���[�V�����Ɏg�p���鎞�Ԃ̊J�n����

class FieldEventBath;

class Door :
    public FieldObject
{
public:
    Door(FieldObjectManager* myfom, D3DXVECTOR2 pos, D3DXVECTOR2 size);
    ~Door() {};

    void SetTrigger(FieldEventBath* feb) { _Trigger = feb; }

    // FieldObject ����Čp������܂���
    bool GetHitTrigger(const OBJECT_DATA& od) override;

    bool GetHitStay(const OBJECT_DATA& od) override;

    void Hit(const OBJECT_DATA& od) override;

    void UpdateStart() override;

    void Update() override;

    void UpdateEnd() override;

    void Draw(const D3DXVECTOR2& decrement) const override;
    

private:

    FieldEventBath* _Trigger;

    bool _IsActive = false;

    TEXTURE_DATA _Texture = TEXTURE_DATA((char*)"data/TEXTURE/gate_verical.png", 3, 1, 3);

    int _Anim = ANIM_TIME;

};

#endif // !Door