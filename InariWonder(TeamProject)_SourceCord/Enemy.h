#pragma once
#ifndef ENEMY_H
#define ENEMY_H
/*------------------------------------------------------------------------------

		キツネ管理[Enemy.h]

											Date:2023/11/21
											creator:小嶋夢紀
------------------------------------------------------------------------------*/


#include "FieldObject.h"

#include "texture.h"

#include "sprite.h"

/*
	敵の引数

	管理者
	位置
	速度
	最初の向き
	横に進むマス数
	縦に進むマス数
	時計回りか(trueなら時計回り)
	攻撃開始距離
	視野距離
	視野角(0 ～ 359)

* /

/*
　移動
	目的地を設定する関数
	目的地まで移動する関数
	目的地で待機する関数

　索敵
	今自分がいるところと索敵対象がいる場所の差分から角度を取得して、その角度が一定以内だったらTrueを返す
	向きを指定する関数　アニメーションでも使う
*/

typedef enum
{
	ENEMY_KARAKASA,
	ENEMY_TYOTSIN,
	ENEMY_YUKIONNA,
	ENEMY_ID_MAX
}ENEMY_ID;


typedef enum {
	GO,			// 目的地に行く
	STAY,		// 目的地で待機
	BACK,		// 目的地から帰還

	SHUTTLRUN,	// 規定行動

	ATTACK,		// 攻撃
}ENEMY_MOVE_MODE;

class MouseGetter;

class Player;
class Fox;

class Enemy :public FieldObject
{
protected:
	const int TEXTURE_NUMBER[3] = { 
		LoadTexture((char*)"data/TEXTURE/enemy1.png"),
		LoadTexture((char*)"data/TEXTURE/enemy2.png"),
		LoadTexture((char*)"data/TEXTURE/enemy3.png")
	};

	Player* _Player;
	Fox* _Fox;

	static const int ENEMY_TEXTURE_DIVISION_NUM_X = 4;	// テクスチャの横分割数
	static const int ENEMY_TEXTURE_DIVISION_NUM_Y = 4;	// テクスチャの縦分割数

	static const float ENEMY_TEXTURE_DIVISION_X;
	static const float ENEMY_TEXTURE_DIVISION_Y;

	bool _Move = false;

	D3DXVECTOR2 _Vec = D3DXVECTOR2(0.0f,0.0f);

	float _Dis = 0.0f;		// 距離

	float _Speed = 1.0f;	// 移動スピード

	int _Life = 3;		// 体力

	ENEMY_MOVE_MODE _EMM = SHUTTLRUN;					// 行動モード
	int _Range = 500;									// 索敵範囲
	int _ViewingAngle = 90;								// 視野角
	FieldObject* _TargetP = nullptr;				// 発見した敵のポインターをとる
	D3DXVECTOR2 _OldPos = D3DXVECTOR2(0.0f, 0.0f);		// 敵発見前の位置
	int _OldDis = 0;									// 敵発見前の目標までの距離
	D3DXVECTOR2 _OldVec = D3DXVECTOR2(0.0f, 0.0f);		// 敵発見前のベクトル

	D3DXVECTOR2 _KBVec = {0.0f,0.0f};
	LOOK _ProtoLook;
	bool _NowKB = false;

	int _AttackCnt = 0;

	int _AttackRange = 0;								// 攻撃の射程 にゃんこ大戦争みたいに射程内になったら攻撃開始

	int _AnimeCnt = 0;
	int _PatternCnt = 0;

	bool _CW;		// 時計回りに回るか反時計回りに回すか

	const bool& Movement(const bool& f = true);

	void Go(void);
	void Stay(void);
	void Back(void);

	void ShuttlRun(void);

	virtual void Attack(void) = 0;

	void Move(void);
	
	void SetTarget(const ENEMY_MOVE_MODE& emm, const D3DXVECTOR2& v, const float& l);	// ターゲット設定　マウスや探知範囲内に敵やオブジェクトが入ったら

	void DiviVec(const LOOK& d);

	LOOK _Direction = LOOK_DOWN;

	D3DXVECTOR2 _EUv = D3DXVECTOR2(0.0f, 0.0f);
	static const D3DXVECTOR2 _EUvW;

	void SetDirection(void);
	void SetDirection(const D3DXVECTOR2& vec);

	void SetUv(void);

	ENEMY_ID _Id = ENEMY_ID_MAX;

	int _MoveSquareX = 0;		// 横に何マス進むか
	int _MoveSquareY = 0;		// 縦に何マス進むか

	const D3DXVECTOR2& KnockBack(void);
	int _KBCnt = 0;

public:
	// moveXとmoveYはマス数
	Enemy(FieldObjectManager* myfom, const D3DXVECTOR2& p = { 0,0 }, const float& speed = 5, const LOOK& ed = LOOK_RIGHT, const int& moveX = 3, const int& moveY = 3, const bool& cw = false,
		const int& attackRenge = 0, const int& range = 500,const int& va = 90, const D3DXVECTOR2& s = { 72,102 }, const float& r = 50, const ENEMY_ID& id = ENEMY_ID_MAX);
	virtual ~Enemy() {
		_TargetP = nullptr;
	}


	bool GetHitTrigger(const OBJECT_DATA& od) override { return true; }			//当たった瞬間
	bool GetHitStay(const OBJECT_DATA& od) override { return true; }			//当たっている時

	void Hit(const OBJECT_DATA& od) override {}									//当たった時の処理


	void SetObjectMove(FieldObject* fop, const ENEMY_MOVE_MODE& emm = GO);

	void SetKnockBack(const D3DXVECTOR2& v);
	const int& GetLife(void) { return _Life; }
	void SetLife(const int& attack) {
		_Life -= attack;
		_Life = (_Life < 0 ? 0 : _Life);
	}

	const D3DXVECTOR2& GetMoveValue() override;
	void SetMoveValue(const D3DXVECTOR2& move) override;


	void UpdateStart(void)override;
	void Update(void)override {}
	void UpdateEnd(void)override;

	void Draw(const D3DXVECTOR2& decrement) const override { DrawSprite(TEXTURE_NUMBER[_Id], _ObjectData.pos - decrement, _ObjectData.size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), _EUv, _EUvW, 0.0f); }
};

#endif // !ENEMY_H

// 敵はもとのいちのもどる