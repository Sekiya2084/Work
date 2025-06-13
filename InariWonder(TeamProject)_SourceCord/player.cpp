/*------------------------------------------------------------------------------

		プレイヤー管理[Player.cpp]

											Date:2023/11/21
											creator:小嶋夢紀
------------------------------------------------------------------------------*/
#include "input.h"
#include "Player.h"
#include "myString.h"
#include "Map.h"
#include "AbilityFire.h"
#include "FieldObjectManager.h"

#include <string>

#define PLAYER_MOVE	(1)

const float Player::PLAYER_TEXTURE_DIVISION_X = 1.0f / PLAYER_TEXTURE_DIVISION_NUM_X;
const float Player::PLAYER_TEXTURE_DIVISION_Y = 1.0f / PLAYER_TEXTURE_DIVISION_NUM_Y;

const D3DXVECTOR2 Player::_PUvW = D3DXVECTOR2(PLAYER_TEXTURE_DIVISION_X, PLAYER_TEXTURE_DIVISION_Y);

void Player::UpdateStart(void) {
	if (_NowKB) {
		KnockBack();
	}
	else {
		static int cnt = 0;
		if (_ObjectData.pos == _ObjectData.oldPos)++cnt;
		else {
			cnt = 0;
			_NoMove = false;
		}
		if (cnt == 300) _NoMove = true;

		if (GetKeyboardTrigger(DIK_F))
			_MyManager->SetFieldObject(new AbilityFire(_MyManager, _ObjectData.pos, _Direction));
	}

}

void Player::Move()
{
	D3DXVECTOR2 move = MoveInput();
	if (_MapP->GetObjectColliderFlug(this->GetObjectData(), move)) {
		this->SetMoveValue(_MapP->GetObjectMoveValue(this->GetObjectData(), move));
	}
	//_ObjectData.pos += move;
}

void Player::SetUv(void)
{
	_PUv = { PLAYER_TEXTURE_DIVISION_X * _PatternCnt,PLAYER_TEXTURE_DIVISION_Y * _Direction };
}

const D3DXVECTOR2& Player::GetMoveValue()
{
	return (_NowKB ? KnockBack() : MoveInput());
}


void Player::SetMoveValue(const D3DXVECTOR2& move)
{
	_ObjectData.oldPos = _ObjectData.pos;
	_ObjectData.pos += move;
}

D3DXVECTOR2 Player::MoveInput()
{
	if (_NowKB)return { 0.0f,0.0f };
	D3DXVECTOR2 move = { 0,0 };		// 返される移動値
	D3DXVECTOR2 vec = { 0,0 };		// 方向

	float length = 0.0f;

	//上移動
	if (GetKeyboardPress(DIK_W)&& _IsMoveInput)
	{
		vec.y -= _PLAYER_SPEED;
	}
	//下移動
	if (GetKeyboardPress(DIK_S) && _IsMoveInput)
	{
		vec.y += _PLAYER_SPEED;
	}
	//左移動
	if (GetKeyboardPress(DIK_A) && _IsMoveInput)
	{
		vec.x -= _PLAYER_SPEED;
	}
	//右移動
	if (GetKeyboardPress(DIK_D) && _IsMoveInput)
	{
		vec.x += _PLAYER_SPEED;
	}
	
	//if (GetKeyboardPress(DIK_SPACE) && _IsMoveInput)
	//{
	//	//Player* p = new Player(_ObjectData.pos + D3DXVECTOR2(200, 0));
	//	//_FOManager->SetFieldObject(p);
	//}

	length = D3DXVec2Length(&vec);

	if (length) {
		move.x = vec.x / length;
		move.y = vec.y / length;

		//_AnimTime++;
		_AnimeCnt++;
		if (_AnimeCnt == 15) {
			_AnimeCnt = 0;
			++_PatternCnt;
			if (_PatternCnt == PLAYER_TEXTURE_DIVISION_NUM_X)
				_PatternCnt = 0;
		}
	}
	else {
		//_LookVel = _LookVel;
		_PatternCnt = _AnimeCnt = 0;
	}

	if ((move.y < 0.0f))
		_Direction = LOOK_UP;
	if ((move.y > 0.0f))
		_Direction = LOOK_DOWN;
	if ((move.x < 0.0f))
		_Direction = LOOK_LEFT;
	if ((move.x > 0.0f))
		_Direction = LOOK_RIGHT;

	SetUv();

	/*if (length == 0) {
		_LookVel = _LookVel;
		_AnimTime = 0;
	}*/
	/*else if (0 < move.x)_LookVel = LOOK_RIGHT;
	else if (move.x < 0)_LookVel = LOOK_LEFT;
	else if (move.y > 0)_LookVel = LOOK_DOWN;
	else if (0>move.y)_LookVel = LOOK_UP;*/

	move.x *= _PLAYER_SPEED;
	move.y *= _PLAYER_SPEED;

	return move;
}

void Player::SetMove()
{
	
}

void Player::Draw(const D3DXVECTOR2& decrement)const
{
	DrawSprite(_TEXTURE_NUMBER.texNo, _ObjectData.pos - decrement, _ObjectData.size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), _PUv, _PUvW, 0.0f);
	/*D3DXVECTOR2 drawP = _ObjectData.pos - decrement;

	int anim = (((int)_LookVel) * _TEXTURE_NUMBER.wide) + (_AnimTime / _ANIM_TIME % _TEXTURE_NUMBER.wide);

	DrawAnimation(_TEXTURE_NUMBER, drawP, _ObjectData.size,anim);*/
	/*int debug = _ObjectData.pos.y - decrement.y;

	MyString* pos = new MyString(std::to_string(debug));

	pos->DrawString(D3DXVECTOR2(0, 0), D3DXVECTOR2(50, 50), D3DXCOLOR(1, 1, 1, 1));

	delete pos;*/
}

const D3DXVECTOR2& Player::KnockBack(void)
{
	static int cnt = 0;

	if (!(cnt % 10)) {
		_Direction = (_Direction == LOOK_LEFT ? LOOK_RIGHT : LOOK_LEFT);
		SetUv();
	}

	if (cnt == 30) {
		_NowKB = false;
		_KBVec = { 0.0f,0.0f };
		_Direction = _ProtoLook;
		cnt = 0;
	}
	++cnt;

	return _KBVec * 7;
}

void Player::SetKnockBack(const D3DXVECTOR2& v)
{
	_NowKB = true;
	_KBVec = v;
	_ProtoLook = _Direction;
}