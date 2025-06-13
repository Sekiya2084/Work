#pragma once
#ifndef GAMEOVER_H_
#define GAMEOVER_H_
/*------------------------------------------------------------------------------

		ÉvÉåÉCÉÑÅ[ä«óù[title.h]

											Date:2023/12/01
											creator:åjå¥ ó§
------------------------------------------------------------------------------*/
#include "main.h"
#include "FieldObject.h"

#include "texture.h"

#include "sprite.h"
#include "input.h"

class GameOver
{
private:


public:
	GameOver() {}
	~GameOver() {}

	void InitGO() {
		//const unsigned int TEXTURE_NUMBER = LoadTexture((char*)"data/TEXTURE/image.png");
	};
	void UpdateGO(void) {
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_TITLE);
		}
	}

	void DrawGO(const unsigned int TT) { DrawSprite(TT, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(2000, 1200)); }
};
#endif // !GAMEOVER_H_

