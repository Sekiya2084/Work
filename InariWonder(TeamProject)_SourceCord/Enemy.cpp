/*------------------------------------------------------------------------------

		キツネ管理[.cpp]

											Date:2023/11/21
											creator:小嶋夢紀
------------------------------------------------------------------------------*/
#include "Enemy.h"
#include "MouseGetter.h"
#include "input.h"
#include "FieldObjectManager.h"

#include "Player.h"
#include "Fox.h"

const float Enemy::ENEMY_TEXTURE_DIVISION_X = 1.0f / ENEMY_TEXTURE_DIVISION_NUM_X;
const float Enemy::ENEMY_TEXTURE_DIVISION_Y = 1.0f / ENEMY_TEXTURE_DIVISION_NUM_Y;

const D3DXVECTOR2 Enemy::_EUvW = D3DXVECTOR2(ENEMY_TEXTURE_DIVISION_X, ENEMY_TEXTURE_DIVISION_Y);

Enemy::Enemy(FieldObjectManager* myfom, const D3DXVECTOR2& p, const float& speed, const LOOK& ed, const int& moveX, const int& moveY, const bool& cw,
	const int& attackRenge, const int& range, const int& va, const D3DXVECTOR2& s, const float& r, const ENEMY_ID& id) :FieldObject(myfom, p, p, s, r, KIND_ENEMY), _Speed(speed), _MoveSquareX(moveX), _MoveSquareY(moveY), _CW(cw), _Id(id), _AttackRange(attackRenge), _Range(range), _ViewingAngle(va) {
	_Player = _MyManager->GetObject_SearchByTag<Player>(KIND_PLAYER);
	_Fox = _MyManager->GetObject_SearchByTag<Fox>(KIND_FOX);
	DiviVec(ed);
}

void Enemy::UpdateStart(void)
{
	if (!_NowKB) {
		if (!_TargetP) SetObjectMove(_Player);
		if (!_TargetP)SetObjectMove(_Fox);
		if (_Life == 0)
			SetIsDead();
	}

}

void Enemy::UpdateEnd(void)
{
	if (!_NowKB) {
		Move();
	}
}

void Enemy::Move()
{
	switch (_EMM)
	{
	case GO:
		Go();
		break;
	case STAY:
		Stay();
		break;
	case BACK:
		Back();
		break;
	case SHUTTLRUN:
		ShuttlRun();
		break;
	case ATTACK:
		Attack();
		break;
	default:
		break;
	}
}

void Enemy::SetObjectMove(FieldObject* fop, const ENEMY_MOVE_MODE& emm)
{
	if (!((_EMM == SHUTTLRUN) || (_EMM == BACK)))
		return;

	D3DXVECTOR2 s = fop->GetObjectData().pos - _ObjectData.pos;
	float l = D3DXVec2Length(&s);

	if (l < _Range) {

		float dR = (_Direction * 90);
		float hVA = _ViewingAngle / 2;

		int max = dR + hVA;
		int min = dR - hVA;

		float r = (atan2(-s.y, s.x)) * (180.0f / D3DX_PI);

		r += r < 0 ? 360 : 0;

		if ((min < 0) && (180 < r))r -= 360;

		// 視野角に入った
		if ((min < r) && (r < max)) {
			_OldPos = _ObjectData.pos;
			_OldVec = _Vec;
			_OldDis = _Dis;
			_TargetP = fop;
			SetTarget(emm, { s.x / l, s.y / l }, l);
		}

	}
}

void Enemy::Go(void)
{
	// 目的地に着いたら
	if (Movement() || (_Dis < _AttackRange)) {
		_Dis = 0;
		_Vec = { 0.0f,0.0f };
		_AnimeCnt = _PatternCnt = 0;
		_EMM = ATTACK;
	}
	else {
		if (_Dis > _Range) {
			_EMM = STAY;
			_Dis = 0;
			_Vec = { 0.0f,0.0f };
			_TargetP = nullptr;
		}
		else {
			D3DXVECTOR2 s = _TargetP->GetObjectData().pos - _ObjectData.pos;
			float l = D3DXVec2Length(&s);
			SetTarget(_EMM, { s.x / l, s.y / l }, l);
		}
	}
}

void Enemy::Stay(void)
{
	static int cnt = 0;
	if (cnt == 180) {
		cnt = 0;
		D3DXVECTOR2 s = _OldPos - _ObjectData.pos;
		float l = D3DXVec2Length(&s);
		SetTarget(BACK, { s.x / l, s.y / l }, l);
	}
	++cnt;
}

void Enemy::Back(void)
{
	// 目的地に着いたら
	if (Movement()) {
		_Vec = _OldVec;
		_Dis = _OldDis;
		_EMM = SHUTTLRUN;
	}
}

void Enemy::ShuttlRun(void)
{
	if (Movement()) {
		if (_MoveSquareX + _MoveSquareY) {
			int emm = (_Direction + (_CW ? (-1) : 1));		// 時計回りなら引く、反時計回りなら足す
			emm = (emm == (-1)) ? 3 : (emm == 4 ? 0 : emm);
			DiviVec((LOOK)emm);
		}
	}
}

const bool& Enemy::Movement(const bool& f)
{
	//移動中だったら
	if (_Dis >= _Speed) {			//対象との距離がスピードより大きかったら
		//_ObjectData.pos += _Vec * _Speed;		//移動 方向にスピード(移動量)をかけている
		_Dis -= _Speed;							//対象との距離を減らす
		_AnimeCnt++;
		if (_AnimeCnt == 10) {
			_AnimeCnt = 0;
			++_PatternCnt;
			if (_PatternCnt == ENEMY_TEXTURE_DIVISION_NUM_X)
				_PatternCnt = 0;
		}
		if (f) SetDirection();
		else SetUv();
		return false;
	}
	else {										//対象との距離がスピードより小さかったら
		//_ObjectData.pos += _Vec * _Dis;			// 移動量は残り距離
		_Dis = 0;
		_Vec = { 0.0f,0.0f };
		_AnimeCnt = _PatternCnt = 0;
		if (f) SetDirection();
		else SetUv();
		return true;
	}
}

void Enemy::SetTarget(const ENEMY_MOVE_MODE& emm, const D3DXVECTOR2& v, const float& l)
{
	_EMM = emm;
	_Vec = v;
	_Dis = l;
}

void Enemy::SetDirection(void)
{
	D3DXVECTOR2 avV((_Vec.x > 0 ? _Vec.x : -_Vec.x), (_Vec.y > 0 ? _Vec.y : -_Vec.y));	// Absolute value の略

	if (avV.y > (avV.x * 2)) {
		if ((_Vec.y < 0.0f))
			_Direction = LOOK_UP;
		if ((_Vec.y > 0.0f))
			_Direction = LOOK_DOWN;
	}

	else {
		if ((_Vec.x < 0.0f))
			_Direction = LOOK_LEFT;
		if ((_Vec.x > 0.0f))
			_Direction = LOOK_RIGHT;
	}

	SetUv();
}

void Enemy::SetDirection(const D3DXVECTOR2& vec)
{
	D3DXVECTOR2 avV((vec.x > 0 ? vec.x : -vec.x), (vec.y > 0 ? vec.y : -vec.y));	// Absolute value の略

	if (avV.y > (avV.x * 2)) {
		if ((vec.y < 0.0f))
			_Direction = LOOK_UP;
		if ((vec.y > 0.0f))
			_Direction = LOOK_DOWN;
	}

	else {
		if ((vec.x < 0.0f))
			_Direction = LOOK_LEFT;
		if ((vec.x > 0.0f))
			_Direction = LOOK_RIGHT;
	}

	SetUv();
}

void Enemy::SetUv(void)
{
	_EUv.x = ENEMY_TEXTURE_DIVISION_X * _PatternCnt;
	_EUv.y = ENEMY_TEXTURE_DIVISION_Y * _Direction;
}

void Enemy::DiviVec(const LOOK& d)
{
	_Direction = d;
	float proto = d * (D3DX_PI * 0.5f);
	D3DXVECTOR2 p((cosf(proto) * (_MoveSquareX * 50)) + _ObjectData.pos.x, (sinf(proto) * (_MoveSquareY * 50)) + _ObjectData.pos.y);	// 50はマップチップの大きさ
	D3DXVECTOR2 s((p.x - _ObjectData.pos.x), (p.y - _ObjectData.pos.y));
	float l = D3DXVec2Length(&s);
	_Vec = { s.x / l, -s.y / l };
	if (!l) _Vec = { 0.0f, 0.0f };
	_Dis = l;
}

const D3DXVECTOR2& Enemy::GetMoveValue()
{
	return _NowKB ? KnockBack() : (_Vec * ((_Dis >= _Speed) ? _Speed : _Dis));
}

void Enemy::SetMoveValue(const D3DXVECTOR2& move)
{
	_ObjectData.oldPos = _ObjectData.pos;
	_ObjectData.pos += move;
}

void Enemy::SetKnockBack(const D3DXVECTOR2& v)
{
	_NowKB = true;
	_ProtoLook = _Direction;
	//_Vec = { 0.0f,0.0f };
	_KBVec = v;
}

const D3DXVECTOR2& Enemy::KnockBack(void)
{
	if (!(_KBCnt % 10)) {
		_Direction = (_Direction == LOOK_LEFT ? LOOK_RIGHT : LOOK_LEFT);
		SetUv();
	}

	++_KBCnt;
	if (_KBCnt == 30) {
		_NowKB = false;
		_KBVec = { 0.0f,0.0f };
		_Direction = _ProtoLook;
		_KBCnt = 0;
	}

	return _KBVec * 7;
}
