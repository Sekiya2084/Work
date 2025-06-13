#include "Game.h"

#include "Title.h"
#include "Result.h"
#include "Play.h"
#include "GameOver.h"

#include "input.h"

#include "sound.h"

Title* t = new Title();
Result* r = new Result();
GameOver* g = new GameOver();



SCENE g_scene = SCENE_TITLE;	//シーン管理用
/*
static Player2* p;
static Fox* f;

void InitGame()
{
,p = new Player2;
,f = new Fox;
}

void UninitGame()
{
,delete p,f;
}

void UpdateGame()
{
,f->UpdateStartFox();
,p->PlayerMove(p);

,f->UpdateFox();

,f->UpdateEndFox();
}

void DrawGame()
{
,p->DrawPlayer();

,f->DrawFox();
}
*/


void InitGame() {
	//シーンの終了処理
	switch (g_scene)
	{
	case SCENE_TITLE:
		t->InitTitle();
		break;
	case SCENE_GAME:
		//ゲームシーンの初期化
		InitPlay();
		break;
	case SCENE_RESULT:
		r->InitResult();
	case SCENE_GO:
		g->InitGO();
		break;
	}
}

void UpdateGame() {
	switch (g_scene)
	{
	case SCENE_TITLE:
		t->UpdateTitle();
		break;
	case SCENE_GAME:
		//ゲームシーンの初期化
		UpdatePlay();
		break;
	case SCENE_RESULT:
		r->UpdateResult();
		break;
	case SCENE_GO:
		g->UpdateGO();
		break;
	}
	
	if (GetKeyboardTrigger(DIK_TAB))
	{
		StopSoundAll();
		SetScene(SCENE_RESULT);
	}
	
}

void DrawGame() {
	const unsigned int TEXTURE_NUMBER = LoadTexture((char*)"data/TEXTURE/title_image.png");
	const unsigned int TEXTURE_NUMBER2 = LoadTexture((char*)"data/TEXTURE/result.png"); 
	const unsigned int TEXTURE_NUMBER3 = LoadTexture((char*)"data/TEXTURE/kdoisk.png"); 
	switch (g_scene)
	{
	case SCENE_TITLE:
		t->DrawTitle(TEXTURE_NUMBER);
		break;
	case SCENE_GAME:
		//ゲームシーンの初期化
		DrawPlay();
		break;
	case SCENE_RESULT:
		r->DrawResult(TEXTURE_NUMBER2);
		break;
	case SCENE_GO:
		g->DrawGO(TEXTURE_NUMBER3);
		break;
	}
}

void UninitGame() {
	//シーンの終了処理
	switch (g_scene)
	{
	case SCENE_TITLE:
		break;
	case SCENE_GAME:
		//ゲームシーンの初期化
		UninitPlay();
		break;
	case SCENE_RESULT:
		r->UpdateResult();
		break;
	case SCENE_GO:
		break;
	}
}

void SetScene(SCENE scene)
{
	//シーンの終了処理
	switch (g_scene)
	{
	case SCENE_TITLE:

		break;
	case SCENE_GAME:
		//ゲームシーンの初期化
		UninitPlay();
		break;
	case SCENE_RESULT:

		break;


	}
	//シーンの切り替え
	g_scene = scene;

	//シーンの初期化
	switch (g_scene)
	{
	case SCENE_TITLE:

		break;
	case SCENE_GAME:
		//ゲームシーンの初期化
		InitPlay();
		break;
	case SCENE_RESULT:

		break;


	}
}

//===========================================
//現在のシーンを取得
//===========================================
SCENE* GetScene(void)
{
	return &g_scene;
}