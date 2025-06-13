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
    FieldEvent_FoxHole(Map* map);   //map��map target�͌ς̒��p�_�̐� Vector�^�ɂ������炢��Ȃ�
    // FieldEventBath ����Čp������܂���
    void Update() override;

    bool SetRoutePosition(D3DXVECTOR2 pos);

    void SetStartPos(int pos) { _StartPos = pos; }

private:
    void TriggerOn();                           //At��-1�̎��ɌĂяo��
    void Move();                                //�ړ�����Length��Z������
    void NextTarget();                          //length��0�ɂȂ�����Ăяo���֐��Alength�̒�����At���X�V

private:
    float _Speed = 3.0f;                        //���̃C�x���g��p�̈ړ����x
    std::vector<D3DXVECTOR2> _RoutePositionList;      //�o�R����n�_���L�����邽�߂̔z��
    D3DXVECTOR2 _Vel;                           //�ړ��������

    int _At = -1;                               //��ԁA-1���}�b�v�Ƃ̓����蔻�������āA�������Ă�����0�ɂ���A��������length��0�ɂȂ����玟�����ă����O�X���X�V�̌J��Ԃ�
    float _Length = 0;                          //���ꂪ0�ɂȂ�����At�𑝂₷

    int _StartPos = 0;                          //�ǂ̃`�b�v���ς����񂾂�Event�J�n�����L������֐�
};

#endif // !FAIELD_EVENT_FOX_HOLE_H