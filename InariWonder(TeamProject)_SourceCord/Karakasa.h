#pragma once
#ifndef KARAKASA_H
#include "Enemy.h"

//ƒLƒcƒl‚Æ‘Ì“–‚½‚èŠÔŠu“¯‚¶

class Karakasa :public Enemy
{
	int cnt = 0;
	bool nowTakle = false;
	D3DXVECTOR2 oldPos = { 0.0f,0.0f };
	int tackleStep = 0;

	D3DXVECTOR2 s = { 0.0f,0.0f };
	float l = 0;

	float _PutSpeed;
public:
	Karakasa(FieldObjectManager* myfom, const D3DXVECTOR2& p = { 0,0 }, const float& speed = 5, const LOOK& ed = LOOK_RIGHT, const int& moveX = 3, const int& moveY = 3, const bool& cw = false)
		:Enemy(myfom, p, speed, ed, moveX, moveY, cw, 150, 400, 60, { 72,102 }, 72, ENEMY_KARAKASA), _PutSpeed(speed) {}

	void Attack(void)override;		// ‘Ì“–‚½‚è
};

#endif
