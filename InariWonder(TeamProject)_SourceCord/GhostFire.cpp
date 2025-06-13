#include "GhostFire.h"
#include "FieldObjectManager.h"
#include "Player.h"
#include "Fox.h"
#include "Collider.h"

GhostFire::GhostFire(FieldObjectManager* myfom, const D3DXVECTOR2& pos, const D3DXVECTOR2& target) :Fire(myfom, pos, { 1.0f, 0.0f, 1.0f, 1.0f }, KIND_ENEMY_FIRE) {
	_Player = _MyManager->GetObject_SearchByTag<Player>(KIND_PLAYER);
	_Fox = _MyManager->GetObject_SearchByTag<Fox>(KIND_FOX);
	D3DXVECTOR2 sub = target - pos;
	float length = D3DXVec2Length(&sub);
	_Vec = { sub.x / length,sub.y / length };
	_Rot = atan2f((target.y - pos.y), (target.x - pos.x));
}

void GhostFire::Update(void)
{
	if (CollisionBB(_ObjectData.pos, _Player->GetObjectData().pos, _ObjectData.size, _Player->GetObjectData().size)) {
		SetIsDead();
		_Player->SetKnockBack(_Vec);
		_Player->SetLife(1);
	}
	if (CollisionBB(_ObjectData.pos, _Fox->GetObjectData().pos, _ObjectData.size, _Fox->GetObjectData().size)) {
		SetIsDead();
		_Fox->SetKnockBack(_Vec);
		_Fox->SetLife(20);
	}
}
