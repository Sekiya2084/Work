#pragma once
#include "main.h"

typedef enum
{
    SCENE_TITLE = 0,
    SCENE_GAME,
    SCENE_RESULT,
    SCENE_GO,
    SCENE_MAX
}SCENE;

void InitGame();
void UninitGame();
void UpdateGame();
void DrawGame();


void SetScene(SCENE scene);
SCENE* GetScene(void);