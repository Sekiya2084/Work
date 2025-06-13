#pragma once

#ifndef FOX_ABILITY_H
#define FOX_ABILITY_H

#include "main.h"
#include "FieldObjectManager.h"
#include "texture.h"
#include "Fox.h"




///
///  列挙体
/// 

typedef enum ABILITY_KIND {
	ABILITY_MIKO_HEAL,			//巫女の回復
	ABILITY_MIKO_ATTACK,		//攻撃？
	ABILITY_MIKO_SHIELD,		//1回ダメージ無効
	ABILITY_FOX_FIRE,			//キツネの炎
	ABILITY_FOX_ICE,			//キツネの氷

	ABILITY_MAX
}ABILITY_KIND;


class Ability
{
public:
	Ability() : _IsActive (false) {};
	~Ability();

	void SetIsActive(bool is)	{ _IsActive = is; }				//できればあんまり使いたくない、でもギミックとして能力を封じるのを使うかも
	bool GetIsActive()			{ return _IsActive; }

	//アビリティ使用者とターゲット、敵の場所とかマウスカーソルの位置などを引数で与えて使用する
	//移動するのでもいいし、その場のに残るのでもいい
	virtual void UseAbility(const OBJECT_DATA od,const D3DXVECTOR2& target) = 0;

	virtual void Update() = 0;									//能力別で挙動が変わる可能性がある　移動させるなら
			
	virtual void Draw() = 0;									//アビリティのフィールドオブジェクト上の見た目

	//狐の見た目が変わるかもしれないから	これは肉付けだから使わないと思う
	TEXTURE_DATA GetFoxAbilityTexture() {};
	
	void SetFieldObjectManagerPoint(FieldObjectManager* fOManager) { if (_FOManager == nullptr)_FOManager = fOManager; }		//中身が入ってなかった時だけ

private:
	//Ability();									//基本使わせない

protected:
	bool _IsActive;									//能力を使える状態か？　所持しているかどうかとか

	int _COOL_TIME;									//アビリティ使用してからもう1度使えるようになるまでの時間	巫女の場合はアイテム式なるから使わないかも　この変数そのままスキルのスタック数として使ってもいい
	int _Time;

	//template<typename T>T _TexData;				//アビリティごとに固定の画像　typeidで型を調べて、IntかTEXDATAか確認する
	TEXTURE_DATA* _TexData = nullptr;

	static FieldObjectManager* _FOManager;			//これを使用してフィールド上にアビリティのオブジェクトを生成する
};

#endif // !FOX_ABILITY_H