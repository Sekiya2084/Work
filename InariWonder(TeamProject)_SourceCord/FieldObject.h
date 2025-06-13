// ===================================================
// FieldObject.h							基底クラス
//	武藤海人								2023/11/22
// ===================================================

#pragma once

#ifndef FIELD_OBJECT_H
#define FIELD_OBJECT_H

#include "main.h"
class FieldObjectManager;

///
///  列挙
/// 

typedef enum {
	KIND_NULL,
	KIND_PLAYER,				//プレイヤー
	KIND_PLAYER_FIRE,
	KIND_PLAYER_ABILITY,		//プレイヤーのアビリティ
	KIND_PLAYER_BULLET,			//プレイヤーの弾
	KIND_PLAYER_HEALAREA,		//プレイヤーの回復範囲
	KIND_FOX,					//狐
	KIND_FOX_ABILITY,			//狐のアビリティ
	KIND_FOX_FIRE,
	KIND_FOX_TACKLE,
	KIND_ENEMY,					//敵
	KIND_ENEMY_FIRE,
	KIND_ENEMY_ICE,
	KIND_ENEMY_TACKLE,
	KIND_BOSS_LEFT,
	KIND_BOSS_RIGHT,
	KIND_BOSS_ICE,
	KIND_OBJECT,				//木材などの情報
	KIND_WOOD,
	KIND_MAX
}FIELD_OBJECT_KIND;	//オブジェの種類

typedef enum {
	LOOK_RIGHT = 0,
	LOOK_UP = 1,
	LOOK_LEFT = 2,
	LOOK_DOWN = 3
}LOOK;

/// <summary>
/// 構造体 
/// </summary>

typedef struct OBJECT_DATA {
	OBJECT_DATA() {};
	OBJECT_DATA(D3DXVECTOR2 p, D3DXVECTOR2 op, D3DXVECTOR2 s, float r, FIELD_OBJECT_KIND fok);

	D3DXVECTOR2 pos;		//場所
	D3DXVECTOR2 oldPos;		//昔の場所
	D3DXVECTOR2 size;		//描画用、BBに使う判定の大きさ
	float range;			//Trigger判定に使う外積用
	FIELD_OBJECT_KIND kind;
}OBJECT_DATA;


class Map;

//クラス

class FieldObject
{
public:
	FieldObject(FieldObjectManager* myfom, const D3DXVECTOR2& p = { 0,0 }, const D3DXVECTOR2& op = { 0,0 }, const D3DXVECTOR2& s = { 100,100 }, const float& r = 50, const FIELD_OBJECT_KIND& fok = KIND_NULL)
		:_ObjectData(OBJECT_DATA(p, op, s, r, fok)), _MyManager(myfom){};
	FieldObject(OBJECT_DATA od)
		:_ObjectData(OBJECT_DATA(od)) {};

	

	const OBJECT_DATA& GetObjectData() {return _ObjectData;}

	virtual bool GetHitTrigger(const OBJECT_DATA& od) = 0;			//当たった瞬間
	virtual bool GetHitStay(const OBJECT_DATA& od) = 0;				//当たっている時

	virtual void Hit(const OBJECT_DATA& od) = 0;					//当たった時の処理

	virtual bool GetIsDead() { return _IsDead; }					//削除することを伝える関数、条件があるならいじってよし
	virtual bool GetIsActive() { return _IsActive; }				//削除することを伝える関数、条件があるならいじってよし

	virtual const D3DXVECTOR2& GetMoveValue() { return D3DXVECTOR2(0.0f,0.0f); };	//今フレームで移動したい最大量
	virtual void SetMoveValue(const D3DXVECTOR2& move) { _ObjectData.pos += move; };					//どれだけ移動できるかをマップクラスから受け取るためのもの

	void SetMapPointa(Map* map) { _MapP = map; };
	void SetFieldObjectManager(FieldObjectManager* fom) { _MyManager = fom; }
	/*
	例
	if(GetHitTrigger(od)){
		od.Hit(this);			//当たったことをodに知らせる。リソースの消費なり、クールタイムの設定なり、アイテムならここで消すように処理
		this.Hit(od);			//当たったことを自分に知らせる
	}
	*/

	virtual void UpdateStart() = 0;
	virtual void Update() = 0;
	virtual void UpdateEnd() = 0;

	virtual void Draw(const D3DXVECTOR2& decrement) const = 0;

protected:
	Map* _MapP = nullptr;

	OBJECT_DATA _ObjectData;

	bool _IsDead = false;
	bool _IsActive = false;

	FieldObjectManager* _MyManager = nullptr;

	void SetIsDead() { _IsDead = true; }
};



#endif // !FIELD_OBJECT_H