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



SCENE g_scene = SCENE_TITLE;	//�V�[���Ǘ��p
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
	//�V�[���̏I������
	switch (g_scene)
	{
	case SCENE_TITLE:
		t->InitTitle();
		break;
	case SCENE_GAME:
		//�Q�[���V�[���̏�����
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
		//�Q�[���V�[���̏�����
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
		//�Q�[���V�[���̏�����
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
	//�V�[���̏I������
	switch (g_scene)
	{
	case SCENE_TITLE:
		break;
	case SCENE_GAME:
		//�Q�[���V�[���̏�����
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
	//�V�[���̏I������
	switch (g_scene)
	{
	case SCENE_TITLE:

		break;
	case SCENE_GAME:
		//�Q�[���V�[���̏�����
		UninitPlay();
		break;
	case SCENE_RESULT:

		break;


	}
	//�V�[���̐؂�ւ�
	g_scene = scene;

	//�V�[���̏�����
	switch (g_scene)
	{
	case SCENE_TITLE:

		break;
	case SCENE_GAME:
		//�Q�[���V�[���̏�����
		InitPlay();
		break;
	case SCENE_RESULT:

		break;


	}
}

//===========================================
//���݂̃V�[�����擾
//===========================================
SCENE* GetScene(void)
{
	return &g_scene;
}