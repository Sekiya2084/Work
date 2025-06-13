#include "Ice.h"
#include "FieldObjectManager.h"
#include "Player.h"
#include "Fox.h"

Ice::Ice(FieldObjectManager* myfom, const D3DXVECTOR2& pos,const D3DXVECTOR2& freezerPos, const D3DXVECTOR2& size, const FIELD_OBJECT_KIND& fok)
	:FieldObject(myfom, pos, pos, size, 50, fok), _FreezerPos(freezerPos)
{
}

void Ice::Update(void)
{
	static Player* player = _MyManager->GetObject_SearchByTag<Player>(KIND_PLAYER);
	static Fox* fox = _MyManager->GetObject_SearchByTag<Fox>(KIND_FOX);

	static D3DXVECTOR2 sub;
	static float length;

	if (CollisionBB(_ObjectData.pos, player->GetObjectData().pos, _ObjectData.size, player->GetObjectData().size)) {
		sub = _FreezerPos - player->GetObjectData().pos;
		length = D3DXVec2Length(&sub);
		player->SetKnockBack({-(sub.x / length), -(sub.y / length) });
		player->SetLife(1);
	}
	if (CollisionBB(_ObjectData.pos, fox->GetObjectData().pos, _ObjectData.size, fox->GetObjectData().size)) {
		sub = _FreezerPos - fox->GetObjectData().pos;
		length = D3DXVec2Length(&sub);
		fox->SetKnockBack({ -(sub.x / length), -(sub.y / length) });
		fox->SetLife(20);
	}
}

const bool& Ice::CollisionBB(const D3DXVECTOR2& pos1, const D3DXVECTOR2& pos2, const D3DXVECTOR2& size1, const D3DXVECTOR2& size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X²‚Ì”»’è
	if (min1.x < max2.x && max1.x > min2.x)
		//Y²‚Ì”»’è
		if (min1.y < max2.y && max1.y > min2.y)
			//‘S‚Ä‚ÌğŒ‚ªTRUE‚È‚çƒqƒbƒg”»’è
			return true;
	return false;
}