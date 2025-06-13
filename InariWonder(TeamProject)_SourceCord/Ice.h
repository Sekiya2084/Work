#pragma once

#include "FieldObject.h"
#include "sprite.h"

class Player;
class Fox;

class Ice : public FieldObject
{
	int TEX_NUM = LoadTexture((char*)"data/TEXTURE/attackIce.png");
	D3DXVECTOR2 _FreezerPos;

	int cnt = 0;

	virtual void Freeze(void) = 0;

protected:
	const bool& CollisionBB(const D3DXVECTOR2& pos1, const D3DXVECTOR2& pos2, const D3DXVECTOR2& size1, const D3DXVECTOR2& size2);
public:
	Ice(FieldObjectManager* myfom, const D3DXVECTOR2& pos, const D3DXVECTOR2& freezerPos, const D3DXVECTOR2& size, const FIELD_OBJECT_KIND& fok);
	virtual ~Ice() {}

	virtual bool GetHitTrigger(const OBJECT_DATA& od) { return true; }			//ìñÇΩÇ¡ÇΩèuä‘
	virtual bool GetHitStay(const OBJECT_DATA& od) { return true; }			//ìñÇΩÇ¡ÇƒÇ¢ÇÈéû

	virtual void Hit(const OBJECT_DATA& od) {}

	const D3DXVECTOR2& GetMoveValue() { return {0.0f,0.0f}; }	//ç°ÉtÉåÅ[ÉÄÇ≈à⁄ìÆÇµÇΩÇ¢ç≈ëÂó 

	void SetMoveValue(const D3DXVECTOR2& move) {}

	void UpdateStart(void) override {}
	virtual void Update(void) override;
	void UpdateEnd(void) override {
		if (cnt == 150)SetIsDead();
		++cnt;
	}
	void Draw(const D3DXVECTOR2& decrement) const override{
		DrawSprite(TEX_NUM, _ObjectData.pos - decrement, _ObjectData.size);
	}
};