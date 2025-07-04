/*==============================================================================

   ゲーム背景管理[gameBG.h]
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
struct GAMEBG {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		size;	//サイズ
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGameBG(void);
void UninitGameBG(void);
void UpdateGameBG(void);
void DrawGameBG(void);