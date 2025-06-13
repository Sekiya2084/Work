// ===================================================
//	Map.cpp									�}�b�v�N���X
//	�����C�l								2023/11/22
// ===================================================
#include "Map.h"
#include "sprite.h"

Map::Map(int* mapP, int mapX, int mapY)
	:_MapSizeX(mapX),_MapSizeY(mapY)
{
	int num = _MapSizeX * _MapSizeY;

	//�}�b�v�̑傫�����w��
	_MapData = new int[num];

	//���g��ݒ�
	for (int i = 0; i < num; i++) {
		_MapData[i] = mapP[i];
	}

	_MapTex = new TEXTURE_DATA((char*)"data/TEXTURE/chip2.png", 8, 8, 64);
}

Map::Map(int* mapP, int mapX, int mapY, TEXTURE_DATA td)
	:_MapSizeX(mapX), _MapSizeY(mapY)
{
	int num = _MapSizeX * _MapSizeY;

	//�}�b�v�̑傫�����w��
	_MapData = new int[num];

	//���g��ݒ�
	for (int i = 0; i < num; i++) {
		_MapData[i] = mapP[i];
	}

	_MapTex = new TEXTURE_DATA(td);
}

Map::~Map()
{
	//���[�N�΍�
	delete[] _MapData;

	delete _MapTex;
}

void Map::Update()
{
}

void Map::Draw()
{
	int num = 0;		//�e�N�X�`���ԍ��p
	D3DXVECTOR2 pos, size;
	size = { BLOCK_SIZE_X ,BLOCK_SIZE_Y };
	int startX = (int)(_DrawTarget.x / BLOCK_SIZE_X	-_DRAW_WIDE * 0.5f);
	int startY = (int)(_DrawTarget.y / BLOCK_SIZE_Y	-_DRAW_HIGHT * 0.5f);

	//�������}�b�v�[
	if (startX < 0)startX = 0;
	else if (startX > _MapSizeX - DRAW_WIDE)startX = _MapSizeX - DRAW_WIDE;
	if (startY < 0)startY = 0;
	else if (startY > _MapSizeY - DRAW_HIGHT)startY = _MapSizeY - DRAW_HIGHT;

	int endX = startX + _DRAW_WIDE ;
	int endY = startY + _DRAW_HIGHT;

	////�������}�b�v�[
	//if (endX > _MapSizeX)endX = _MapSizeX;
	//if (endY > _MapSizeY)endY = _MapSizeY;

	for (int y = startY; y <= endY; y++) {
		for (int x = startX; x <= endX; x++) {
			num = _MapSizeX * y + x;
			pos = { BLOCK_SIZE_X * x,BLOCK_SIZE_Y * y };
			pos -= _DrawDecrement;							//�X�N���[�������𔽉f
			//DrawAnimation_LT(*_MapTex, pos, size, _MapData[num]);
			DrawTile_LT(*_MapTex, pos, size, _MapData[num]);
		}
	}
}

void Map::SetCameraTarget(D3DXVECTOR2 target)
{
	_DrawTarget = target; 

	//������ݒ�
	if (_DrawTarget.x <= BLOCK_SIZE_X * (DRAW_WIDE * 0.5f)) {
		//_DrawDecrement.x = target.x- (BLOCK_SIZE_X * (DRAW_WIDE * 0.5));
		_DrawDecrement.x = 0;
	}
	else if (_DrawTarget.x >= (_MapSizeX* BLOCK_SIZE_X) -BLOCK_SIZE_X * (DRAW_WIDE * 0.5f)) {
		_DrawDecrement.x = (_MapSizeX * BLOCK_SIZE_X) - (BLOCK_SIZE_X * DRAW_WIDE);
	}
	else {
		_DrawDecrement.x = target.x - (BLOCK_SIZE_X * (DRAW_WIDE * 0.5f));
	}

	if (_DrawTarget.y <= BLOCK_SIZE_Y * (DRAW_HIGHT * 0.5f)) {
		//_DrawDecrement.y = target.y- (BLOCK_SIZE_Y * (DRAW_HEIGHT * 0.5));
		_DrawDecrement.y = 0;
	}
	else if (_DrawTarget.y >= (_MapSizeY* BLOCK_SIZE_Y) -BLOCK_SIZE_Y * (DRAW_HIGHT * 0.5f)) {
		_DrawDecrement.y = (_MapSizeY * BLOCK_SIZE_Y) - (BLOCK_SIZE_Y *  DRAW_HIGHT);
	}
	else {
		_DrawDecrement.y = target.y - (BLOCK_SIZE_Y * (DRAW_HIGHT * 0.5f));
	}	
}

void Map::SetChangeChips(int* arry, int arrySize, int next)
{
	//�z����ɓ����Ă���v�f�l�̏ꏊ�̒l��next�ɕς���
	for (int i = 0; i < arrySize; i++) {
		_MapData[arry[i]] = next;
	}
}

void Map::SetChangeChips(const std::vector<int>& arry, int arrySize, int next)
{
	//�z����ɓ����Ă���v�f�l�̏ꏊ�̒l��next�ɕς���
	for (int i = 0; i < arrySize; i++) {
		_MapData[arry[i]] = next;
	}
}

bool Map::GetObjectColliderFlug(const OBJECT_DATA& od, const D3DXVECTOR2& move)
{
	if ((move.x + move.y) == 0.0f)return true;
	D3DXVECTOR2 pos = od.pos + move;

	//�㉺���E�̈ʒu
	int top,bot,left,right;
	top =	((int)(pos.y - od.size.y * 0.5f))/(int)BLOCK_SIZE_Y;
	bot =	((int)(pos.y + od.size.y * 0.5f))/(int)BLOCK_SIZE_Y;
	left =	((int)(pos.x - od.size.x * 0.5f))/(int)BLOCK_SIZE_X;
	right = ((int)(pos.x + od.size.x * 0.5f))/(int)BLOCK_SIZE_X;

	//����E�㍶���E�����ꂼ��̔z���̏ꏊ
	int lt, rt, lb, rb;
	lt = top * _MapSizeX + left;
	rt = top * _MapSizeX + right;
	lb = bot * _MapSizeX + left;
	rb = bot * _MapSizeX + right;

	//�i�s�������ʂ��i�s�s�u���b�N��������t�@���X
	if (_MapData[lt]>=COLLISION_BLOCK_BEGIN)return false;
	if (_MapData[rt]>=COLLISION_BLOCK_BEGIN)return false;
	if (_MapData[lb]>=COLLISION_BLOCK_BEGIN)return false;
	if (_MapData[rb]>=COLLISION_BLOCK_BEGIN)return false;

	//�h�R������������Ȃ�������true
	return true;
}

D3DXVECTOR2 Map::GetObjectMoveValue(OBJECT_DATA od, D3DXVECTOR2 move)
{
	D3DXVECTOR2 vel = move;

	int x = 0;
	if (vel.x != 0 && vel.x < 0) { x = -1; }
	else if (vel.x != 0 && vel.x > 0) { x = 1; }

	int y = 0;
	if (vel.y != 0 && vel.y < 0) { y = -1; }
	else if (vel.y != 0 && vel.y > 0) { y = 1; }
	bool isX, isY;
	isX = isY = false;
	while (true) {
		if (x != 0) {
			vel.x -= x;
			//x���v���X�Ȃ̂Ɉړ��������}�C�i�X�ɂȂ�����
			if (x > 0 && vel.x < 0) {
				vel.x = x = 0;
			}
			///x���}�C�i�X�Ȃ̂Ɉړ��������v���X�ɂȂ�����
			else if (x < 0 && vel.x > 0) {
				vel.x = x = 0;
			}
			//�i�߂邩�ǂ���
			isX = GetObjectColliderFlug(od, vel);			
		}

		//�ǂ��炩��ON��������
		if (isX || isY)break;

		if (y != 0) {
			vel.y -= y;
			//y���v���X�Ȃ̂Ɉړ��������}�C�i�X�ɂȂ�����
			if (y > 0 && vel.y < 0) {
				vel.y = y = 0;
			}
			//y���}�C�i�X�Ȃ̂Ɉړ��������v���X�ɂȂ�����
			else if (y < 0 && vel.y > 0) {
				vel.y = y = 0;
			}
			//�i�߂邩�ǂ���
			isY = GetObjectColliderFlug(od, vel);
		}

		//�ǂ��炩��ON��������
		if (isX || isY)break;
		//����0��������
		if (vel.x == 0 && vel.y == 0)break;
	}

	return vel;
}
