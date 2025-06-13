#include "FieldEvent_FoxHole.h"
#include "FieldObject.h"[
#include "Fox.h"

FieldEvent_FoxHole::FieldEvent_FoxHole(Map* map)
	:FieldEventBath(map,1,0,0)
{
}

void FieldEvent_FoxHole::Update()
{
	if (_At == -1) {
		TriggerOn();
	}
	else {
		if (_Length > 0) {
			Move();
		}
		else {
			NextTarget();
		}
	}
}

bool FieldEvent_FoxHole::SetRoutePosition(D3DXVECTOR2 pos)
{
	_RoutePositionList.push_back(pos);

	return (_TARGET_ARRY_SIZE < _RoutePositionList.size()) ? true : false;
}

void FieldEvent_FoxHole::TriggerOn()
{
	D3DXVECTOR2 pos = _TriggerObjectArry[0]->GetObjectData().pos;
	D3DXVECTOR2 size = _TriggerObjectArry[0]->GetObjectData().size * 0.5f;
	if (GetMapPositionCollider(pos, size, _StartPos)) {
		NextTarget();
		if(_TriggerObjectArry[0]->GetObjectData().kind==FIELD_OBJECT_KIND::KIND_FOX){
			Fox* fox=(Fox*)_TriggerObjectArry[0];
			fox->SetIsMoveInput(false);
		}
	}
}

void FieldEvent_FoxHole::Move()
{
	if (_Length < _Speed) {
		D3DXVECTOR2 val = _Vel * _Length;
		_TriggerObjectArry[0]->SetMoveValue(val);
		_Length = 0;
	}
	else {
		D3DXVECTOR2 val = _Vel * _Speed;
		_TriggerObjectArry[0]->SetMoveValue(val);
		_Length -= _Speed;
	}
}

void FieldEvent_FoxHole::NextTarget()
{
	_At++;
	if (_At >= _RoutePositionList.size()) {
		_At = -1;
		if (_TriggerObjectArry[0]->GetObjectData().kind == FIELD_OBJECT_KIND::KIND_FOX) {
			Fox* fox = (Fox*)_TriggerObjectArry[0];
			fox->SetIsMoveInput(true);
		}
		return;
	}

	D3DXVECTOR2 pos = _RoutePositionList[_At] - _TriggerObjectArry[0]->GetObjectData().pos;

	D3DXVec2Normalize(&_Vel, &pos);		//ˆÚ“®•ûŒü‚ðVel‚É“ü‚ê‚é

	_Length = D3DXVec2Length(&pos);
}
