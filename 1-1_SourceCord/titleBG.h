/*==============================================================================

   タイトル背景管理[titleBG.h]
														 Author :関谷勇人
														 Date   :2023/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
struct TITLEBG {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		size;	//サイズ
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTitleBG(void);
void UninitTitleBG(void);
void UpdateTitleBG(void);
void DrawTitleBG(void);