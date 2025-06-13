#pragma once

#include "FieldObject.h"
#include "sprite.h"
#include "texture.h"

class Fire : public FieldObject
{
protected:
	int TEX_NUM = LoadTexture((char*)"data/TEXTURE/Fire.png");
	D3DXVECTOR2 _Vec;
	int _Speed = 10;
	D3DXCOLOR _Color;
	//bool _Mirror = false;

	float _Rot = 0.0f;

	float _Mirror = 0.0f;
	float _MirrorW = 1.0f;

	int cnt = 0;

	D3DXVECTOR2 proto;
protected:
	const bool& CollisionBB(const D3DXVECTOR2& pos1, const D3DXVECTOR2& pos2, const D3DXVECTOR2& size1, const D3DXVECTOR2& size2);
public:
	Fire(FieldObjectManager* myfom, const D3DXVECTOR2& pos, const D3DXCOLOR& color, const FIELD_OBJECT_KIND& fok) :FieldObject(myfom, pos, { 0.0f,0.0f }, { 70.0f,42.0f }, 30, fok), _Color(color), proto({0.0f,0.0f}) {}
	virtual ~Fire() {}

	virtual bool GetHitTrigger(const OBJECT_DATA& od) { return true; }			//ìñÇΩÇ¡ÇΩèuä‘
	virtual bool GetHitStay(const OBJECT_DATA& od) { return true; }			//ìñÇΩÇ¡ÇƒÇ¢ÇÈéû

	virtual void Hit(const OBJECT_DATA& od) {}

	const D3DXVECTOR2& GetMoveValue() override { return (_Vec * _Speed); }	//ç°ÉtÉåÅ[ÉÄÇ≈à⁄ìÆÇµÇΩÇ¢ç≈ëÂó 

	void SetMoveValue(const D3DXVECTOR2& move) override {
		_ObjectData.oldPos = _ObjectData.pos;
		_ObjectData.pos += move; 
	}

	void UpdateStart(void) override {
		if (cnt == 15) {
			_Mirror = (_Mirror == 1.0f ? 0.0f : 1.0f);
			_MirrorW = (_MirrorW == (-1.0f) ? 1.0f : (-1.0f));
			cnt = 0;
		}
		++cnt;
	}
	virtual void Update(void) override {}
	void UpdateEnd(void) override {
		if (proto == _ObjectData.pos)
			SetIsDead();
		proto = _ObjectData.pos;
	}
	void Draw(const D3DXVECTOR2& decrement) const override {
		DrawSprite(TEX_NUM, _ObjectData.pos - decrement, _ObjectData.size, _Color, {0.0f,_Mirror }, { 1.0f,_MirrorW }, _Rot);
	}
};