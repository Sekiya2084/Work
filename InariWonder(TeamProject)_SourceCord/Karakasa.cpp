#include "Karakasa.h"
#include "FieldObjectManager.h"
#include "Tackle.h"

void Karakasa::Attack(void)
{
	if (cnt == 60) {
		oldPos = _ObjectData.pos;
		s = _TargetP->GetObjectData().pos - _ObjectData.pos;
		l = D3DXVec2Length(&s);
		_Vec = { -(s.x / l), -(s.y / l) };
		_Dis = 100;
		tackleStep = 1;
	}

	//if (_TargetP->GetLife() == 0) {
	//	_EMM = STAY;
	//	_Vec = { 0.0f,0.0f };
	//	_Dis = 0;
	//	_TargetP = nullptr;
	//	_Speed = 1.0f;
	//	nowTakle = false;
	//	return;
	//}

	if (!nowTakle && (l > _AttackRange)) {
		s = _TargetP->GetObjectData().pos - _ObjectData.pos;
		l = D3DXVec2Length(&s);
		SetTarget(GO, { s.x / l, s.y / l }, l);
		_Vec;
		_Speed = _PutSpeed;
		oldPos = { 0.0f,0.0f };
		tackleStep = cnt = l = 0;
		s = { 0.0f,0.0f };
		return;
	}

	if (Movement(false)) {
		switch (tackleStep)
		{
		case 1:
			s = _TargetP->GetObjectData().pos - _ObjectData.pos;
			l = D3DXVec2Length(&s);
			_Vec = { s.x / l, s.y / l };
			_Dis = 150;
			_Speed *= 5;
			_MyManager->SetFieldObject(new Tackle(_MyManager, _ObjectData, _Vec, _Speed, _Dis));
			nowTakle = true;
			++tackleStep;
			break;
		case 2:
			s = oldPos - _ObjectData.pos;
			l = D3DXVec2Length(&s);
			_Vec = { (s.x / l), (s.y / l) };
			_Dis = 100;
			_Speed = _PutSpeed;
			nowTakle = false;
			++tackleStep;
			break;
		case 3:
			oldPos = { 0.0f,0.0f };
			tackleStep = cnt = l = 0;
			s = { 0.0f,0.0f };
			_Vec = { 0.0f,0.0f };
			break;
		default:
			break;
		}
	}
	++cnt;
}