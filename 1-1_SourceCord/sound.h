/*==============================================================================

   サウンド処理 [sound.h]
														 Author : 関谷　勇人
														 Date   : 2023/06/29
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once	// インクルードガード

#include <windows.h>
#include "xaudio2.h"

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/
bool InitSound(HWND hWnd);
void UninitSound(void);

int LoadSound(char* pFilename);
void PlaySound(int index, int loopCount);
void StopSound(int index);
void StopSoundAll(void);
void SetVolume(int index, float vol);
