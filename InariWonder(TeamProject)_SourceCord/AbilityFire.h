#pragma once
#include "Fire.h"

class AbilityFire : public Fire
{
public:
	AbilityFire(FieldObjectManager* myfom, const D3DXVECTOR2 pos, LOOK looking) :Fire(myfom,pos, {1.0f, 0.45f, 0.25f, 1.0f}, KIND_PLAYER_FIRE) {
		_Rot = looking * (-D3DX_PI * 0.5f);
		_Vec = { cosf(_Rot),sinf(_Rot)};
	}
	~AbilityFire() {}

	void Update(void)override;
};
