/*==============================================================================

   ゲーム管理 [game.cpp]
														 Author : 関谷　勇人
														 Date   : 2023/06/26
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "collision.h"
#include "input.h"
#include "sound.h"
#include "map.h"
#include "score.h"
#include "gameBG.h"

static int g_GameBGMNo = 0;
bool swg = true;

//=============================================================================
// 初期化処理
//=============================================================================
void InitGame(void)
{
	InitGameBG();
	//サウンドの読み込み
	g_GameBGMNo = LoadSound((char*)"data/BGM/mariost1.wav");

	//BGMを流す
	PlaySound(g_GameBGMNo, -1);

	//ボリューム調整
	SetVolume(g_GameBGMNo, 0.5f);

	InitCollision();
	// プレイヤー管理の初期化処理
	InitPlayer();

	// 弾管理の初期化処理
	InitBullet();

	// 敵管理の初期化処理
	InitEnemy();

	//マップの読み込み
	InitMap();

	//スコアの初期化処理
	InitScore();

	swg = true;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	UninitGameBG();

	// プレイヤー管理の終了処理
	UninitPlayer();

	// 弾管理の終了処理
	UninitBullet();

	// 敵管理の終了処理
	UninitEnemy();

	//マップの終了処理
	UninitMap();

	//スコアの終了処理
	UninitScore();

	//サウンドの停止
	StopSoundAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	UpdateGameBG();
	//当たり判定
	UpdateCollision();

	//マップデータ更新
	UpdateMap();

	// プレイヤー管理の更新処理
	UpdatePlayer();

	// 弾管理の更新処理
	UpdateBullet();

	// 敵管理の更新処理
	UpdateEnemy();

	// スコアの更新処理
	UpdateScore();

	PLAYER* pPlayer = GetPlayer();
	//死亡時ゲームオーバー画面へ遷移
	if (!pPlayer->use && swg)
	{
		swg = false;
		SetFade(FADE_SOUT);
		//SetScene(SCENE_GAMEOVER);
		//SetFade(FADE_IN);
	}
	////エンターキーで離脱できる用
	//else if	(GetKeyboardTrigger(DIK_RETURN))
	//{
	//	SetFade(FADE_OUT);
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	DrawGameBG();
	//マップ描画
	DrawMap();

	// プレイヤー管理の描画処理
	DrawPlayer();

	// 弾管理の描画処理
	DrawBullet();

	// 敵管理の描画処理
	DrawEnemy();

	//スコア描画
	DrawScore();
}
