// ===================================================
//	Map.h									�}�b�v�N���X
//	�����C�l								2023/11/22
// ===================================================
#pragma once
#ifndef MAP_H
#define MAP_H


#include "main.h"
#include "FieldObject.h"
#include "texture.h"
#include <vector>

//�}�b�v�̃`�b�v�̑傫���A����̓I�u�W�F�N�g���Q�Ƃ���}�b�v�̑傫���ɉe������
#define BLOCK_SIZE_X	(50.0f)
#define BLOCK_SIZE_Y	(50.0f)

//�`��͈�	��ʓ��ɉ�10�c8�ŕ`�悵�����Ȃ� WIDE 10  HIGHT 8�@�œ���
#define DRAW_WIDE		(40)
#define DRAW_HIGHT		(24)

//�����蔻�肪��������u���b�N�̍ŏ��̒l�H�@0~9�͂��蔲���\�̑����`�b�v�@10~�͓����蔻������߂��Q�`�b�v
#define COLLISION_BLOCK_BEGIN		(51)

class Map
{
public:
	Map(int* mapP,int mapX,int mapY);
	Map(int* mapP,int mapX,int mapY,TEXTURE_DATA td);		//Map�̃e�N�X�`����16*16��256�Œ�ɂ������@�ł��o�O�����邽�ߕύX������
	~Map();

	virtual void Update();

	virtual void Draw();

	virtual void SetCameraTarget(D3DXVECTOR2 target);	//�J�����̒��S�_���w�肷���� Draw�̑O�ɗ\������

	void SetChangeChips(int* arry, int arrySize, int next);
	void SetChangeChips(const std::vector<int>& arry, int arrySize, int next);

	bool GetObjectColliderFlug(const OBJECT_DATA& od, const D3DXVECTOR2& move);		//���܂肢����Ȃ��悤��

	D3DXVECTOR2 GetObjectMoveValue(OBJECT_DATA od, D3DXVECTOR2 move);		

	D3DXVECTOR2 GetDrawDecrement() { return _DrawDecrement; }

	int GetMapSizeX() { return _MapSizeX; }
	int GetMapSizeY() { return _MapSizeY; }

private:
	Map();		//�����̃R���X�g���N�^�͎g�킹�Ȃ�

protected:

	virtual void SetFieldEvent() {};		//���̒���Event�̃Z�b�g���s���A������R���X�g���N�^�ŌĂяo��



	//�ϐ�

protected:
	//�}�b�v���̂̑傫���@MineCraft�ł����P�`�����N16*16�݂����Ȃ���
	int _MapSizeX,_MapSizeY;
	//�u���b�N�̑傫���@MineCraft�ł����P�u���b�N�P���[�g���݂����Ȋ���
	float _BLOCK_SIZE_X = BLOCK_SIZE_X;
	float _BLOCK_SIZE_Y = BLOCK_SIZE_Y;

	//�`��̒��S
	D3DXVECTOR2 _DrawTarget;
	//��ʃX�N���[���Ɏg������
	D3DXVECTOR2 _DrawDecrement;
	

	//�`�敝
	int _DRAW_WIDE = DRAW_WIDE;
	int _DRAW_HIGHT = DRAW_HIGHT;

	int* _MapData = nullptr;

	TEXTURE_DATA* _MapTex = nullptr;

						//�C�x���g���ꊇ�Ǘ����邽�߂̂��
};


#endif // !MAP_H