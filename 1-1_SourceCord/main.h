/*==============================================================================

   テクスチャの描画 [main.h]
                                                         Author : 関谷　勇人
                                                         Date   : 2023/06/26
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// ウインドウの幅
#define SCREEN_HEIGHT	(1080)				// ウインドウの高さ

//*****************************************************************************
// 列挙体定義
//*****************************************************************************
typedef enum {  //シーン管理用
    SCENE_TITLE = 0,
    SCENE_GAME,
    SCENE_RESULT,
    SCENE_GAMEOVER,
    SCENE_MAX //シーンの総数
}SCENE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetScene(SCENE scene);
SCENE* GetScene(void);
