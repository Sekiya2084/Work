#include "Fire.h"

const bool& Fire::CollisionBB(const D3DXVECTOR2& pos1, const D3DXVECTOR2& pos2, const D3DXVECTOR2& size1, const D3DXVECTOR2& size2)
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