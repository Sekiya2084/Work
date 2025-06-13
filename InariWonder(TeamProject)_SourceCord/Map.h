// ===================================================
//	Map.h									マップクラス
//	武藤海人								2023/11/22
// ===================================================
#pragma once
#ifndef MAP_H
#define MAP_H


#include "main.h"
#include "FieldObject.h"
#include "texture.h"
#include <vector>

//マップのチップの大きさ、これはオブジェクトが参照するマップの大きさに影響する
#define BLOCK_SIZE_X	(50.0f)
#define BLOCK_SIZE_Y	(50.0f)

//描画範囲	画面内に横10縦8で描画したいなら WIDE 10  HIGHT 8　で入力
#define DRAW_WIDE		(40)
#define DRAW_HIGHT		(24)

//当たり判定が発生するブロックの最初の値？　0~9はすり抜け可能の装飾チップ　10~は当たり判定を求める障害チップ
#define COLLISION_BLOCK_BEGIN		(51)

class Map
{
public:
	Map(int* mapP,int mapX,int mapY);
	Map(int* mapP,int mapX,int mapY,TEXTURE_DATA td);		//Mapのテクスチャは16*16の256固定にしたい　でもバグがあるため変更も視野
	~Map();

	virtual void Update();

	virtual void Draw();

	virtual void SetCameraTarget(D3DXVECTOR2 target);	//カメラの中心点を指定するやつ Drawの前に予備だす

	void SetChangeChips(int* arry, int arrySize, int next);
	void SetChangeChips(const std::vector<int>& arry, int arrySize, int next);

	bool GetObjectColliderFlug(const OBJECT_DATA& od, const D3DXVECTOR2& move);		//あまりいじらないように

	D3DXVECTOR2 GetObjectMoveValue(OBJECT_DATA od, D3DXVECTOR2 move);		

	D3DXVECTOR2 GetDrawDecrement() { return _DrawDecrement; }

	int GetMapSizeX() { return _MapSizeX; }
	int GetMapSizeY() { return _MapSizeY; }

private:
	Map();		//ただのコンストラクタは使わせない

protected:

	virtual void SetFieldEvent() {};		//この中でEventのセットを行う、それをコンストラクタで呼び出す



	//変数

protected:
	//マップ自体の大きさ　MineCraftでいう１チャンク16*16みたいなもの
	int _MapSizeX,_MapSizeY;
	//ブロックの大きさ　MineCraftでいう１ブロック１メートルみたいな感じ
	float _BLOCK_SIZE_X = BLOCK_SIZE_X;
	float _BLOCK_SIZE_Y = BLOCK_SIZE_Y;

	//描画の中心
	D3DXVECTOR2 _DrawTarget;
	//画面スクロールに使う差分
	D3DXVECTOR2 _DrawDecrement;
	

	//描画幅
	int _DRAW_WIDE = DRAW_WIDE;
	int _DRAW_HIGHT = DRAW_HIGHT;

	int* _MapData = nullptr;

	TEXTURE_DATA* _MapTex = nullptr;

						//イベントを一括管理するためのやつ
};


#endif // !MAP_H