#include "AbilityFire.h"
#include "FieldObjectManager.h"
#include "Enemy.h"

void AbilityFire::Update(void)
{
	auto enemys = _MyManager->GetObjectByTag<Enemy>(KIND_ENEMY);
	if (!enemys.empty()) {
		for (auto e : enemys) {
			if (CollisionBB(_ObjectData.pos, e->GetObjectData().pos, _ObjectData.size, e->GetObjectData().size)) {
				SetIsDead();
				e->SetKnockBack(_Vec);
				e->SetLife(1);
			}
		}
	}
}
