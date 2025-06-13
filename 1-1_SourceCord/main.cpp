/*==============================================================================

   テクスチャの描画 [main.cpp]
                                                         Author : 関谷　勇人
                                                         Date   : 2023/06/29
--------------------------------------------------------------------------------

==============================================================================*/
#include <time.h>
#include "main.h"
#include "sound.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "gameover.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// ウインドウのクラス名
#define WINDOW_CAPTION		"Mmodoki"			// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************
SCENE g_scene = SCENE_TITLE;	//シーン管理用の関数

#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用

#endif

											//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//ランダムシードの初期化
	srand((unsigned int)time(NULL));

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウサイズの変更
	int window_width = 1920;
	int window_height = 1080;

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_CAPTION,
		WS_POPUP, //ウィンドウスタイルの変更
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		window_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// ウィンドウ横幅
		window_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= ((float)1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// 更新処理
				Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// サウンドの初期化
	InitSound(hWnd);

	// スプライトの初期化
	InitSprite();

	//フェードの初期化
	InitFade();

	//シーンの初期化
	switch (g_scene)
	{
	case SCENE_TITLE:
		//タイトルシーンの初期化
		InitTitle();
		break;
	case SCENE_GAME:
		//ゲームシーンの初期化
		InitGame();
		break;
	case SCENE_RESULT:
		//リザルトシーンの初期化
		InitResult();
		break;
	case SCENE_GAMEOVER:
		InitGameover();
		break;
	default:
		break;
	}

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	//フェードの終了処理
	UninitFade();

	//シーンの終了処理
	switch (g_scene)
	{
	case SCENE_TITLE:
		//タイトルシーンの終了処理
		UninitTitle();
		break;
	case SCENE_GAME:
		//ゲームシーンの終了処理
		UninitGame();
		break;
	case SCENE_RESULT:
		//リザルトシーンの終了処理
		UninitResult();
		break;
	case SCENE_GAMEOVER:
		UninitGameover();
		break;
	default:
		break;
	}

	// スプライトの終了処理
	UninitSprite();

	// サウンドの終了処理
	UninitSound();

	// テクスチャの全解放
	UninitTexture();

	// 入力処理の終了処理
	UninitInput();

	// レンダリングの終了処理
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力処理の更新処理
	UpdateInput();

	//フェードの更新処理
	UpdateFade();

	//シーンの更新処理
	switch (g_scene)
	{
	case SCENE_TITLE:
		//タイトルシーンの更新処理
		UpdateTitle();
		break;
	case SCENE_GAME:
		//ゲームシーンの更新処理
		UpdateGame();
		break;
	case SCENE_RESULT:
		//リザルトシーンの更新処理
		UpdateResult();
		break;
	case SCENE_GAMEOVER:
		UpdateGameover();
		break;
	default:
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	//シーンの描画処理
	switch (g_scene)
	{
	case SCENE_TITLE:
		//タイトルシーンの描画処理
		DrawTitle();
		break;
	case SCENE_GAME:
		//ゲームシーンの描画処理
		DrawGame();
		break;
	case SCENE_RESULT:
		//リザルトシーンの描画処理
		DrawResult();
		break;
	case SCENE_GAMEOVER:
		DrawGameover();
		break;
	default:
		break;
	}

	//フェードの描画
	DrawFade();

	// バックバッファ、フロントバッファ入れ替え
	Present();
}

// =======================================
// シーン切り替え
// =======================================
void SetScene(SCENE scene)
{
	//シーンの終了処理
	switch (g_scene)
	{
	case SCENE_TITLE:
		//タイトルシーンの終了処理
		UninitTitle();
		break;
	case SCENE_GAME:
		//ゲームシーンの終了処理
		UninitGame();
		break;
	case SCENE_RESULT:
		//リザルトシーンの終了処理
		UninitResult();
		break;
	case SCENE_GAMEOVER:
		UninitGameover();
		break;
	default:
		break;
	}

	//シーンの切り替え
	g_scene = scene;

	//シーンの初期化
	switch (g_scene)
	{
	case SCENE_TITLE:
		//タイトルシーンの初期化
		InitTitle();
		break;
	case SCENE_GAME:
		//ゲームシーンの初期化
		InitGame();
		break;
	case SCENE_RESULT:
		//リザルトシーンの初期化
		InitResult();
		break;
	case SCENE_GAMEOVER:
		InitGameover();
		break;
	default:
		break;
	}
}

SCENE* GetScene(void)
{
	return &g_scene;
}