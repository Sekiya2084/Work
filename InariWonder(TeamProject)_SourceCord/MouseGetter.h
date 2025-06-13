// ===================================================
// FieldObject.h					マウス差分取得クラス
//	武藤海人								2023/11/22
// ===================================================
#pragma once


#ifndef MOUSE_GETTER_H
#define MOUSE_GETTER_H

#include "main.h"
#include "Map.h"

///
///構造体
///

typedef struct {
	D3DXVECTOR2 sub;		//マウスの座標と対象の座標の差分　マウス（目的地）ー対象（現在地）
	D3DXVECTOR2 vel;		//マウスが対象からどの方向にあるかを記憶して単位円化したやつ
	float		length;		//三角関数で取得した対象とマウスの距離

}MOUSE_GETTER_DATA;

/// <summary>
/// クラス
/// </summary>
class MouseGetter
{
public:
	MouseGetter() {};
	~MouseGetter() {};

	static MOUSE_GETTER_DATA GetMouseGetterData(const D3DXVECTOR2& pos);
	static MOUSE_GETTER_DATA GetMouseGetterDataWorld(const D3DXVECTOR2& worldPos);

	bool GetWindowOverMousePosition();//ウィンドウ上にマウスがあるかどうか

	static void SetMapPointa(Map* m);

private:

protected:

public:
	static Map* s_MapP;

};


#endif // !MOUSE_GETTER_H