#include "Door.h"
#include "FieldEventBath.h"
#include "sprite.h"


Door::Door(FieldObjectManager* myfom, D3DXVECTOR2 pos,D3DXVECTOR2 size):
FieldObject(myfom,pos,pos,size,100.0f, FIELD_OBJECT_KIND::KIND_OBJECT)
{
}

bool Door::GetHitTrigger(const OBJECT_DATA& od)
{
	return false;
}

bool Door::GetHitStay(const OBJECT_DATA& od)
{
	return false;
}

void Door::Hit(const OBJECT_DATA& od)
{
}

void Door::UpdateStart()
{
}

void Door::Update()
{
	if (_IsActive && _Anim > 0) {
		_Anim--;
	}
}

void Door::UpdateEnd()
{
	//アクティブがfalseになったらマップEventが実行されたってことだから
	if (!_Trigger->GetIsActive() && !_IsActive) {
		_IsActive = true;
	}
}

void Door::Draw(const D3DXVECTOR2& decrement) const
{
	int anim = 2 - _Anim / 30;
	DrawAnimation(_Texture, _ObjectData.pos - decrement, _ObjectData.size, anim);
}
