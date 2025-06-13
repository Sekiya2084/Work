/*------------------------------------------------------------------------------

		キツネ管理[Fox.cpp]

											Date:2023/11/21
											creator:小嶋夢紀
------------------------------------------------------------------------------*/
#include "Fox.h"
#include "input.h"

#include <time.h>

#include "FieldObjectManager.h"

#include "Player.h"
#include "Enemy.h"

#include "Tackle.h"

const float Fox::FOX_TEXTURE_DIVISION_X = 1.0f / FOX_TEXTURE_DIVISION_NUM_X;
const float Fox::FOX_TEXTURE_DIVISION_Y = 1.0f / FOX_TEXTURE_DIVISION_NUM_Y;

const D3DXVECTOR2 Fox::_FUvW = D3DXVECTOR2(FOX_TEXTURE_DIVISION_X, FOX_TEXTURE_DIVISION_Y);

void Fox::UpdateStart(void)
{
	static int lookCnt = 0;

	if (!_NowKB) {
		static int cnt = 0;

		if (!lookFlag && !lookCnt && _MoveMode == RETURN_STAY) {
			lookFlag = true;
			++lookCnt;
		}

		if (lookCnt)
			++lookCnt;

		if (lookCnt == 40) {
			lookFlag = false;
		}

		_ReturnFlag = lookFlag;

		if (_MoveMode != RETURN_STAY)lookCnt = 0;

		//Zキーが押されたとき巫女に強制帰還
		if (GetKeyboardTrigger(DIK_Z))SetBack();

		if (!(_MoveMode == RETURN_GO || _MoveMode == BACK_BACK || _MoveMode == TACKLE)) {
			//左クリック押されたとき クリックされた床に目的地を設定
			if (_Mouse.GetWindowOverMousePosition() && IsMouseLeftTriggered()) {
				MOUSE_GETTER_DATA mgd = _Mouse.GetMouseGetterDataWorld(_ObjectData.pos);
				SetTarget(STAY_GO, mgd.vel, mgd.length);
			}

			auto enemy = _MyManager->GetObjectByTag<Enemy>(KIND_ENEMY);
			if (!enemy.empty())
				for (auto p : enemy)
					SetObjectMove(p);


			//if (_Player->GetNoMove()) _MoveMode = FREE_FREE;
		}

		if (_Fleaz) {
			++cnt;
			_Speed = SPEED_MAX * 0.5f;
		}
		if (cnt == 60) {
			_Fleaz = false;
			_Speed = SPEED_MAX;
			cnt = 0;
		}

		if (!lookFlag && (_MoveMode == RETURN_STAY)) {
			lookCnt = 41;
		}

		if (lookFlag && (lookCnt < 41)) {
			_Target = nullptr;
			_MoveMode = RETURN_STAY;
			_Vec = { 0.0f, 0.0f };
			_Dis = 0;
		}

	}
}

void Fox::Update(void)
{
	if (!_NowKB) {

	}
}

void Fox::UpdateEnd(void)
{
	if (!_NowKB) {
		Move();
	}
}

void Fox::Move(void)
{
	if (_IsMoveInput) {
		switch (_MoveMode)
		{
		case RETURN_GO:
			MoveGo();
			break;
		case RETURN_STAY:
			MoveStay();
			break;
		case RETURN_BACK:
			MoveBack();
			break;
		case STAY_GO:
			MoveGo();
			break;
		case STAY_STAY:
			MoveStay();
			break;
		case FREE_FOLLOW:
			MoveBack();
			break;
		case FREE_FREE:
			MoveFree();
			break;
		case TACKLE:
			Attack();
			break;
		case BACK_BACK:
			Back();
			break;

		default:
			break;
		}
		//SetDirection();
		//Animation();
	}
}

void Fox::SetObjectMove(FieldObject* fop)
{
	D3DXVECTOR2 sub = fop->GetObjectData().pos - _ObjectData.pos;
	float length = D3DXVec2Length(&sub);
	// lengthが範囲より小さかったらtrue
	if (length < COME_RANGE) {
		if (Enemy* e = dynamic_cast<Enemy*>(fop))
			_Target = e;
		SetTarget(RETURN_GO, D3DXVECTOR2(sub.x / length, sub.y / length), length);
	}
}

void Fox::SetTarget(const MOVE_MODE& mm, const D3DXVECTOR2& v, const float& l)
{
	_MoveMode = mm;
	_Vec = v;
	_Dis = l;
}

void Fox::SetBack(void)
{
	_MoveMode = BACK_BACK;		// 強制帰還モードに変更
	_Target = nullptr;
	SetVecLen(_Player->GetObjectData().pos);
}

const bool& Fox::AttackPossible(void)
{
	if (_Target) {
		if (_Dis < _AttackRange)
			return true;
	}
	return false;
}

void Fox::MoveGo(void)
{
	if (Movement() || AttackPossible()) {
		// 目的地に着いたら
		if (_MoveMode == RETURN_GO) {
			_MoveMode = TACKLE;
			_Dis = 0;
			_Vec = { 0.0f,0.0f };
		}
		else if (_MoveMode == STAY_GO)
			_MoveMode = STAY_STAY;
	}
	else {	// 追尾し続けるかする
		if (_Target)
			SetVecLen(_Target->GetObjectData().pos);
	}
}

void Fox::MoveStay(void)
{
	static int Cnt = 0;

	// RETURNモードなら秒数をとって　STAYなら何もせず待機
	if (_MoveMode == RETURN_STAY) {
		// RETURNモードならSTAYからBACKにモード変更
		if (Cnt == 180) {
			Cnt = 0;
			SetVecLen(_Player->GetObjectData().pos);
			_MoveMode = RETURN_BACK;
		}
		++Cnt;
	}
}

void Fox::MoveBack(void)
{
	D3DXVECTOR2 sub = _Player->GetObjectData().pos - _ObjectData.pos;
	float length = D3DXVec2Length(&sub);

	if (_MoveMode == FREE_FOLLOW)
		if (length > COME_RANGE)
			SetTarget(FREE_FOLLOW, D3DXVECTOR2(sub.x / length, sub.y / length), length);

	if (Movement()) _MoveMode = FREE_FOLLOW;
	else SetTarget(RETURN_BACK, D3DXVECTOR2(sub.x / length, sub.y / length), length);
}

const bool& Fox::Movement(const bool& f)
{
	//移動中だったら
	if (_Dis >= _Speed) {							//対象との距離がスピードより大きかったら
		//_ObjectData.pos += _Vec * _Speed;			//移動 方向にスピード(移動量)をかけている
		_Dis -= _Speed;								//対象との距離を減らす
		_AnimeCnt++;
		if (_AnimeCnt == 10) {
			_AnimeCnt = 0;
			++_PatternCnt;
			if (_PatternCnt == FOX_TEXTURE_DIVISION_NUM_X)
				_PatternCnt = 0;
		}
		if (f) SetDirection();
		else SetUv();
		return false;
	}
	else {											//対象との距離がスピードより小さかったら
		//_ObjectData.pos += _Vec * _Dis;			// 移動量は残り距離
		_Dis = 0;
		_PatternCnt = _AnimeCnt = 0;
		_Vec = { 0.0f,0.0f };
		if (f) SetDirection();
		else SetUv();
		return true;
	}
}

void Fox::MoveFree(void)
{
	static int cnt = 0;
	if (Movement() && (cnt == 180)) {
		cnt = 0;

		D3DXVECTOR2 free = _ObjectData.pos;
		free.x += ((rand() % 100) * (rand() % 2 ? (-1) : 1));
		free.y += ((rand() % 100) * (rand() % 2 ? (-1) : 1));

		SetVecLen(free);
	}
	++cnt;
}

void Fox::Back(void)
{
	if (Movement()) _MoveMode = FREE_FOLLOW;
	else SetVecLen(_Player->GetObjectData().pos);
}

bool Fox::GetHitTrigger(const OBJECT_DATA& od)
{
	static bool frag = false;

	if (!frag) {
		D3DXVECTOR2 sub = od.pos - _ObjectData.pos;
		float length = D3DXVec2Length(&sub);
		float size = (_ObjectData.size.x / 2) + (od.size.x / 2);

		//足した半径とベクトル長とで大きさを判定する
		//差分のベクトル長の方が小さければヒットしている
		if (length < size)
		{
			frag = true;
		}
	}
	else
		frag = false;

	return frag;
}

void Fox::SetDirection(void)
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

void Fox::SetUv(void)
{
	_FUv = { FOX_TEXTURE_DIVISION_X * _PatternCnt, FOX_TEXTURE_DIVISION_Y * _Direction };
}

void Fox::SetVecLen(const D3DXVECTOR2& goal)
{
	D3DXVECTOR2 sub = goal - _ObjectData.pos;
	float length = D3DXVec2Length(&sub);
	if (length) _Vec = { sub.x / length, sub.y / length };
	else _Vec = { 0.0f, 0.0f };
	_Dis = length;
}

const D3DXVECTOR2& Fox::GetMoveValue(void)
{
	return (_NowKB ? KnockBack() : (_Vec * ((_Dis >= _Speed) ? _Speed : _Dis)));
}

void Fox::SetMoveValue(const D3DXVECTOR2& move)
{
	_ObjectData.oldPos = _ObjectData.pos;
	_ObjectData.pos += move;
}

void Fox::SetKnockBack(const D3DXVECTOR2& v)
{
	_NowKB = true;
	_ProtoLook = _Direction;
	_Vec = { 0.0f,0.0f };
	_KBVec = v;
}

const D3DXVECTOR2& Fox::KnockBack(void)
{
	static int cnt = 0;

	if (!(cnt % 10)) {
		_Direction = (_Direction == LOOK_LEFT ? LOOK_RIGHT : LOOK_LEFT);
		SetUv();
	}

	++cnt;
	if (cnt == 30) {
		_NowKB = false;
		_KBVec = { 0.0f,0.0f };
		_Direction = _ProtoLook;
		cnt = 0;
	}

	return _KBVec * 7;
}

// 挙動がなんか変　見たらわかる
void Fox::Attack(void)
{
	static int cnt = 0;
	static bool nowTakle = false;
	static D3DXVECTOR2 oldPos = { 0.0f,0.0f };
	static int tackleStep = 0;

	static D3DXVECTOR2 s = { 0.0f,0.0f };
	static float l = 0;

	static bool flag = false;

	/*D3DXVECTOR2 sub = _Target->GetObjectData().pos - _ObjectData.pos;
	float len = D3DXVec2Length(&sub);*/

	if (flag) {
		_MoveMode = RETURN_STAY;
		_Vec = { 0.0f,0.0f };
		_Dis = 0;
		_Target = nullptr;
		_Speed = _Fleaz ? SPEED_MAX * 0.5f : SPEED_MAX;
		cnt = tackleStep = 0;
		flag = false;
		return;
	}

	if (_Target != nullptr) {

		if (_Target->GetLife() == 0) {
			//_MoveMode = RETURN_STAY;
			_Target = nullptr;
			flag = true;
		}

		if (cnt == 40) {
			oldPos = _ObjectData.pos;
			s = _Target->GetObjectData().pos - _ObjectData.pos;
			l = D3DXVec2Length(&s);
			_Vec = { -(s.x / l), -(s.y / l) };
			_Dis = 100;
			tackleStep = 1;
		}

		if ((tackleStep == 1) && (l > _AttackRange)) {
			oldPos = { 0.0f,0.0f };
			s = _Target->GetObjectData().pos - _ObjectData.pos;
			l = D3DXVec2Length(&s);
			SetTarget(RETURN_GO, { s.x / l,s.y / l }, l);
			cnt = tackleStep = 0;
			return;
		}
	}


	if (Movement(false)) {
		switch (tackleStep)
		{
		case 1:
			s = _Target->GetObjectData().pos - _ObjectData.pos;
			l = D3DXVec2Length(&s);
			_Vec = { (s.x / l), (s.y / l) };
			_Dis = 150;
			_Speed *= 10;
			_MyManager->SetFieldObject(new Tackle(_MyManager, _ObjectData, _Vec, _Speed, _Dis));
			nowTakle = true;
			++tackleStep;
			break;
		case 2:
			s = oldPos - _ObjectData.pos;
			l = D3DXVec2Length(&s);
			_Vec = { (s.x / l), (s.y / l) };
			_Dis = 100;
			_Speed = _Fleaz ? SPEED_MAX * 0.5f : SPEED_MAX;
			nowTakle = false;
			++tackleStep;
			break;
		case 3:
			oldPos = { 0.0f,0.0f };
			tackleStep = 0;
			cnt = 0;
			l = 0;
			s = { 0.0f,0.0f };
			_Vec = { 0.0f,0.0f };
			break;
		default:
			break;
		}
	}
	++cnt;
}