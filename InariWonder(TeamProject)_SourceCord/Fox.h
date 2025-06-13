#pragma once
#ifndef FOX_H
#define FOX_H
/*------------------------------------------------------------------------------

		キツネ管理[Fox.h]

											Date:2023/11/21
											creator:小嶋夢紀
------------------------------------------------------------------------------*/


#include "FieldObject.h"

#include "texture.h"

#include "sprite.h"

#include "MouseGetter.h"

class Player;

class Enemy;

// プレイヤーのもとに帰ったらウロチョロさせるか追従させる

// 攻撃やアイテムをとってくるのも必要?
typedef enum {
	RETURN_GO,		// 目的地に行く
	RETURN_STAY,	// 目的地で待機
	RETURN_BACK,	// 目的地から帰還
	STAY_GO,		// 目的地に行く
	STAY_STAY,		// 目的地でずっと待機
	FREE_FOLLOW,	// ついてくる
	FREE_FREE,		// ウロチョロ
	BACK_BACK,		// 強制帰還中 強制期間中は何の指示を受けても無視して返る
	TACKLE,
}MOVE_MODE;

class Fox :public FieldObject
{
private:
	const unsigned int FOX_TEXTURE_NUMBER = LoadTexture((char*)"data/TEXTURE/kitsune.png");

	static const int FOX_TEXTURE_DIVISION_NUM_X = 4;	// テクスチャの横分割数
	static const int FOX_TEXTURE_DIVISION_NUM_Y = 4;	// テクスチャの縦分割数

	static const float FOX_TEXTURE_DIVISION_X;
	static const float FOX_TEXTURE_DIVISION_Y;

	Player* _Player = nullptr;

	static const int SPEED_MAX = 5.0f;	// 移動スピード
	int _Speed = SPEED_MAX;	// 移動スピード

	
	MouseGetter _Mouse;
	bool _IsMoveInput = true;

	static const int COME_RANGE = 200;		// キツネの探知範囲
	static const int _AttackRange = 100;

	D3DXVECTOR2 _Vec = D3DXVECTOR2(0.0f,0.0f);	// 力の働く向き

	float _Dis = 0.0f;		// 距離	当たり判定が true になったら0にする

	D3DXVECTOR2 _KBVec = { 0.0f,0.0f };
	LOOK _ProtoLook;


	int _AnimeCnt = 0;
	int _PatternCnt = 0;

	MOVE_MODE _MoveMode = FREE_FOLLOW;		// 行動モード

	LOOK _Direction = LOOK_DOWN;

	D3DXVECTOR2 _FUv = D3DXVECTOR2(0.0f, 0.0f);
	static const D3DXVECTOR2 _FUvW;

	Enemy* _Target = nullptr;								// 発見したターゲット

	int		_Life = 100;							// ライフ

	bool	_Fleaz = false;

	bool	_NowKB = false;				// ノックバック中か

	bool	_FireAbility = false;				// 炎スキル持ち

	bool lookFlag = false;
	bool _ReturnFlag = false;


	//void SetVecDis(D3DXVECTOR2& vec, float& dis, const OBJECT_DATA& od);	同じ計算をよくしているのでなんか関数が欲しいが取り敢えず後

	// この辺キツネの行動モードの奴
	const bool& Movement(const bool& f = true);		// 目的地に着いたらtrue

	void MoveGo(void);							// ここは行くだけだから処理内容は前のMoveと同じ
	void MoveStay(void);						// ステイ　RETURNなら数秒待機 STAYなら指示待ち待機
	void MoveBack(void);						// バック　というか巫女に近づく
	void MoveFree(void);						// ウロチョロ
	void Back(void);							// 強制帰還
	
	void SetTarget(const MOVE_MODE& mm, const D3DXVECTOR2& v, const float& l);	// ターゲット設定　マウスや探知範囲内に敵やオブジェクトが入ったら

	void SetBack(void);			// 巫女へ強制帰還

	const bool& AttackPossible(void);

	// 移動ロジックの処理
	void Move(void);

	void SetDirection(void);

	void SetUv(void);

	void SetVecLen(const D3DXVECTOR2& goal);
	const D3DXVECTOR2& KnockBack(void);

	void Attack(void);
public:
	Fox(FieldObjectManager* myfom,Player* player,D3DXVECTOR2 p = { 800,550 }, D3DXVECTOR2 s = { 70,70 }, float r = 50) :FieldObject(myfom,p,p,s,r, KIND_FOX),_Player(player){}
	virtual ~Fox() {}

	// ==========================================================================================================
	// 返り値は移動できるかの
	const bool& GetObjectColliderFlag(const OBJECT_DATA& od, const D3DXVECTOR2 move) {};
	// 返り値はどの量移動できるかの移動量
	const D3DXVECTOR2& GetMoveValue(const OBJECT_DATA& od, const D3DXVECTOR2 move) {};
	// ==========================================================================================================

	bool GetHitTrigger(const OBJECT_DATA& od) override;							//当たった瞬間
	bool GetHitStay(const OBJECT_DATA& od) override { return true; }			//当たっている時

	void Hit(const OBJECT_DATA& od) override {}									//当たった時の処理

	void SetObjectMove(FieldObject* fop);		// オブジェクトによるムーブフラグ

	void UpdateStart(void)override;
	void Update(void)override;
	void UpdateEnd(void)override;

	void Draw(const D3DXVECTOR2& decrement) const override { DrawSprite(FOX_TEXTURE_NUMBER, _ObjectData.pos - decrement, _ObjectData.size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), _FUv, _FUvW, 0.0f); }

	void SetDis(void) { _Dis = 0; }

	const D3DXVECTOR2& GetMoveValue(void) override;
	void SetMoveValue(const D3DXVECTOR2& move) override;

	void SetIsMoveInput(bool flug) { _IsMoveInput = flug; }

	const bool& GetFA(void) { return _FireAbility; }
	void SetFA(void) { _FireAbility = true; }

	const int& GetLife(void)const { return _Life; }
	void SetLife(const int& attack) { 
		_Life -= attack;
		_Life = _Life < 0 ? 0 : _Life;
	}

	void SetKnockBack(const D3DXVECTOR2& v);
};

#endif // !FOX_H

//D3DXVec2LengthSq

/*
必要な関数（想定
		　MoveGo		GOモードすべてに流用可能
		　MoveStay		STAYモードすべてに流用可能
		　MoveBack		BACKとFOLLOWに流用可能　FOLLOWの場合は別途巫女との距離でのフラグを求められる
		　FOLLOWは一定範囲外から出たらプレイヤーのもとへ行く
		　MoveFree		FREEにのみ使う
		　SetTarget		目的地を設定する関数　引数でRETURNかSTAYかを指定すればモードの移行がスムーズかも これはほぼ終わってる
		　SetBack		問答無用でBackにする関数　STAY中の狐を呼び戻したり、GO中の狐をキャンセルで巫女に戻るようにする
* */