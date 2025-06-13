/////////////////////////////////////////////////////////
//  ìñÇΩÇËîªíËä«óù.cpp						Collider.cpp
//		ïêì°äCêl						2024/01/13
/////////////////////////////////////////////////////////

#include "Collider.h"

bool BBTrriger(OBJECT_DATA od1, OBJECT_DATA od2)
{
	D3DXVECTOR2 min,max,nowmin,nowmax, oldmin, oldmax;

	{
		//min1 max1Çë„ì¸
		float hw = od1.size.x * 0.5f;
		float hh = od1.size.y * 0.5f;
		min = od1.pos - D3DXVECTOR2(hw, hh);
		max = od1.pos + D3DXVECTOR2(hw, hh);	

		//min2 max2Çë„ì¸
		hw = od2.size.x * 0.5f;
		hh = od2.size.y * 0.5f;
		nowmin = od2.pos - D3DXVECTOR2(hw, hh);
		nowmax = od2.pos + D3DXVECTOR2(hw, hh);
		//oldmin oldmaxÇë„ì¸
		oldmin = od2.oldPos - D3DXVECTOR2(hw, hh);
		oldmax = od2.oldPos + D3DXVECTOR2(hw, hh);
	}

	if (
		(
		min.x<nowmax.x && max.x>nowmin.x
		&&
		min.y<nowmax.y && max.y>nowmin.y
		)&&(
		min.x>oldmax.x && max.x<oldmin.x
		&&
		min.y>oldmax.y && max.y< oldmin.y
		)
		) 
	{
		return true;
	}

	return false;
}

bool BCTrriger(OBJECT_DATA od1, OBJECT_DATA od2)
{

	return false;
}

bool BBHit(OBJECT_DATA od1, OBJECT_DATA od2)
{

	D3DXVECTOR2 min, max, nowmin, nowmax;

	{
		//min1 max1Çë„ì¸
		float hw = od1.size.x * 0.5f;
		float hh = od1.size.y * 0.5f;
		min = od1.pos - D3DXVECTOR2(hw, hh);
		max = od1.pos + D3DXVECTOR2(hw, hh);

		//min2 max2Çë„ì¸
		hw = od2.size.x * 0.5f;
		hh = od2.size.y * 0.5f;
		nowmin = od2.pos - D3DXVECTOR2(hw, hh);
		nowmax = od2.pos + D3DXVECTOR2(hw, hh);
	}

	if (
		min.x<nowmax.x && max.x>nowmin.x
		&&
		min.y<nowmax.y && max.y>nowmin.y
		)
	{
		return true;
	}
	return false;
}

bool BCHit(OBJECT_DATA od1, OBJECT_DATA od2)
{
	return false;
}

bool BBRerese(OBJECT_DATA od1, OBJECT_DATA od2)
{

	D3DXVECTOR2 min, max, nowmin, nowmax, oldmin, oldmax;

	{
		//min1 max1Çë„ì¸
		float hw = od1.size.x * 0.5f;
		float hh = od1.size.y * 0.5f;
		min = od1.pos - D3DXVECTOR2(hw, hh);
		max = od1.pos + D3DXVECTOR2(hw, hh);

		//min2 max2Çë„ì¸
		hw = od2.size.x * 0.5f;
		hh = od2.size.y * 0.5f;
		nowmin = od2.pos - D3DXVECTOR2(hw, hh);
		nowmax = od2.pos + D3DXVECTOR2(hw, hh);
		//oldmin oldmaxÇë„ì¸
		oldmin = od2.oldPos - D3DXVECTOR2(hw, hh);
		oldmax = od2.oldPos + D3DXVECTOR2(hw, hh);
	}

	if (
		(
			min.x > nowmax.x && max.x < nowmin.x
			&&
			min.y>nowmax.y && max.y < nowmin.y
			) && (
			min.x < oldmax.x && max.x > oldmin.x
			&&
			min.y < oldmax.y && max.y > oldmin.y
			)
		)
	{
		return true;
	}
	return false;
}

bool BCRerese(OBJECT_DATA od1, OBJECT_DATA od2)
{
	return false;
}
