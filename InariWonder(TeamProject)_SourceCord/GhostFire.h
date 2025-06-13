#pragma once

#include "Fire.h"

class Player;
class Fox;

class GhostFire : public Fire
{
	Player* _Player;
	Fox* _Fox;

public:
	GhostFire(FieldObjectManager* myfom, const D3DXVECTOR2& pos, const D3DXVECTOR2& target);
	~GhostFire() {}

	void Update(void)override;
};