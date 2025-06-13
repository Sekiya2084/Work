//=============================================================================
// 当たり判定処理 [collision.cpp]
// 
// Author : 関谷　勇人
//			2023/06/29
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "block.h"
#include "map.h"
#include "fade.h"
#include "score.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
bool CollisionBCSq(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
bool swc = true;

void InitCollision(void)
{
	swc = true;
}

//=============================================================================
// 当たり判定処理
//=============================================================================
void UpdateCollision(void)
{
	// ポインターの取得
	PLAYER* pPlayer = GetPlayer();
	BULLET* pBullet = GetBullet();
	ENEMY* pEnemy = GetEnemy();
	BLOCK* pBlock = GetBlock();
	SCENE* pScene = GetScene();
	
	
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY; enemyCnt++)
	{//ブロックの上限分チェック
		if ((pEnemy + enemyCnt)->use)
		{//使用してる敵だけチェック
			if (pPlayer->use)
			{//使用しているプレイヤーだけチェックする
				//oldを基にした四辺
				float OldPlayerTop = pPlayer->oldpos.y - pPlayer->size.y / 2;
				float OldPlayerBottom = pPlayer->oldpos.y + pPlayer->size.y / 2;
				float OldPlayerLeft = pPlayer->oldpos.x - pPlayer->size.x / 2;
				float OldPlayerRight = pPlayer->oldpos.x + pPlayer->size.x / 2;

				float EnemyTop = (pEnemy + enemyCnt)->pos.y - (pEnemy + enemyCnt)->size.y / 2;
				float EnemyBottom = (pEnemy + enemyCnt)->pos.y + (pEnemy + enemyCnt)->size.y / 2;
				float EnemyLeft = (pEnemy + enemyCnt)->pos.x - (pEnemy + enemyCnt)->size.x / 2;
				float EnemyRight = (pEnemy + enemyCnt)->pos.x + (pEnemy + enemyCnt)->size.x / 2;

				float PlayerTop = pPlayer->pos.y - pPlayer->size.y / 2;
				float PlayerBottom = pPlayer->pos.y + pPlayer->size.y / 2;
				float PlayerLeft = pPlayer->pos.x - pPlayer->size.x / 2;
				float PlayerRight = pPlayer->pos.x + pPlayer->size.x / 2;
				//BB
				if (EnemyBottom > PlayerTop &&
					EnemyRight > PlayerLeft &&
					EnemyLeft < PlayerRight &&
					EnemyTop < PlayerBottom)
				{
					bool hit = false;
					//エネミー下とプレイヤー上
					if (EnemyBottom >= PlayerTop &&
						EnemyBottom <= OldPlayerTop)
					{
						pPlayer->use = false;
						hit = true;
					}
					//エネミー上とプレイヤー下
					if (EnemyTop <= PlayerBottom &&
						EnemyTop >= OldPlayerBottom)
					{
						Setyadd(-7.0f);
						(pEnemy + enemyCnt)->use = false;
						AddScore(100);
					}
					//ブロック右とボール左
					if (EnemyRight >= PlayerLeft &&
						EnemyRight <= OldPlayerLeft)
					{
						pPlayer->use = false;
					}
					//ブロック左とボール右
					if (EnemyLeft <= PlayerRight &&
						EnemyLeft >= OldPlayerRight)
					{
						pPlayer->use = false;
					}
				}
			}
		}
	}


	for (int blockCnt = 0; blockCnt < MAX_BLOCK; blockCnt++)
	{//ブロックの上限分チェック
		if ((pBlock + blockCnt)->use)
		{//使用してる敵だけチェック
			if (pPlayer->use)
			{//使用しているプレイヤーだけチェックする
				//oldを基にした四辺
				float OldPlayerTop = pPlayer->oldpos.y - pPlayer->size.y / 2;
				float OldPlayerBottom = pPlayer->oldpos.y + pPlayer->size.y / 2;
				float OldPlayerLeft = pPlayer->oldpos.x - pPlayer->size.x / 2;
				float OldPlayerRight = pPlayer->oldpos.x + pPlayer->size.x / 2;

				float BlockTop = (pBlock + blockCnt)->pos.y - (pBlock + blockCnt)->size.y / 2;
				float BlockBottom = (pBlock + blockCnt)->pos.y + (pBlock + blockCnt)->size.y / 2;
				float BlockLeft = (pBlock + blockCnt)->pos.x - (pBlock + blockCnt)->size.x / 2;
				float BlockRight = (pBlock + blockCnt)->pos.x + (pBlock + blockCnt)->size.x / 2;

				float PlayerTop = pPlayer->pos.y - pPlayer->size.y / 2;
				float PlayerBottom = pPlayer->pos.y + pPlayer->size.y / 2;
				float PlayerLeft = pPlayer->pos.x - pPlayer->size.x / 2;
				float PlayerRight = pPlayer->pos.x + pPlayer->size.x / 2;
				//BB
				if (BlockBottom > PlayerTop &&
					BlockRight > PlayerLeft &&
					BlockLeft < PlayerRight &&
					BlockTop < PlayerBottom)
				{
					bool hit = false;
					//ブロック下とボール上
					if (BlockBottom >= PlayerTop &&
						BlockBottom <= OldPlayerTop)
					{
						Setyadd(0.0f);
						pPlayer->Jtrigger = true;
						pPlayer->pos.y = pPlayer->oldpos.y;
						hit = true;
					}
					//ブロック上とボール下
					if (BlockTop <= PlayerBottom &&
						BlockTop >= OldPlayerBottom)
					{
						Setyadd(0.0f);
						pPlayer->Jtrigger = true;
						pPlayer->pos.y = pPlayer->oldpos.y;
						hit = true;
					}
					//ブロック右とボール左
					if (BlockRight >= PlayerLeft &&
						BlockRight <= OldPlayerLeft)
					{
						pPlayer->pos.x = pPlayer->oldpos.x;
						hit = true;
					}
					//ブロック左とボール右
					if (BlockLeft <= PlayerRight &&
						BlockLeft >= OldPlayerRight)
					{
						pPlayer->pos.x = pPlayer->oldpos.x;
						hit = true;
					}
					//当たった時の共通処理
					if (hit)
					{
						if (swc)
						{
							if ((pBlock + blockCnt)->type == 1)
							{
								SetFade(FADE_OUT);
								swc = false;
							}
						}
					}
				}
			}
		}
	}
	
	//敵とブロック
	for (int enemyCnt = 0; enemyCnt < MAX_ENEMY; enemyCnt++)
	{//弾の総数分チェック
		if ((pEnemy + enemyCnt)->use)
		{//使用してる弾だけチェックする
			for (int blockCnt = 0; blockCnt < MAX_BLOCK; blockCnt++)
			{//敵の総数分チェック
				if ((pBlock + blockCnt)->use)
				{//使用している敵だけチェックする
					if (CollisionBCSq((pEnemy + enemyCnt)->pos, (pBlock + blockCnt)->pos, (pEnemy + enemyCnt)->size.x / 2, (pBlock + blockCnt)->size.x / 2))
					{
						(pEnemy + enemyCnt)->vel *= -1;
					}
				}
			}
		}
	}

	// 弾と敵
	//for (int bulletCnt = 0; bulletCnt < MAX_BULLET; bulletCnt++)
	//{//弾の総数分チェック
	//	if ((pBullet + bulletCnt)->use)
	//	{//使用してる弾だけチェックする
	//		for (int enemyCnt = 0; enemyCnt < MAX_ENEMY; enemyCnt++)
	//		{//敵の総数分チェック
	//			if ((pEnemy + enemyCnt)->use)
	//			{//使用している敵だけチェックする
	//				if (CollisionBCSq((pBullet + bulletCnt)->pos, (pEnemy + enemyCnt)->pos, (pBullet + bulletCnt)->size.x / 2, (pEnemy + enemyCnt)->size.x / 2))
	//				{
	//					//当たっているときの処理
	//					(pBullet + bulletCnt)->use = false; //弾消す
	//					(pEnemy + enemyCnt)->use = false; //敵消す
	//				}
	//			}
	//		}
	//	}
	//}

	//プレイヤーとブロック


	// ボスと弾

	// 自分と敵の弾

}

//=============================================================================
// BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, max1;
	D3DXVECTOR2 min2, max2;

	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//X軸の判定
	if (min1.x < max2.x && max1.x > min2.x)
	{
		//Y軸の判定
		if (min1.y < max2.y && max1.y > min2.y)
		{
			//全ての条件がTRUEならヒット判定
			return true;
		}
	}

	return false;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistanceのベクトル長を得る
	float length;
	length = D3DXVec2Length(&vDistance);

	//1と2の半径を足す
	float size = size1 + size2;

	//足した半径とベクトル長とで大きさを判定する
	//差分のベクトル長の方が小さければヒットしている
	if (length < size)
	{
		return true;
	}

	return false;
}

//=============================================================================
// BCによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBCSq(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//vDistanceのベクトル長の2乗の値を得る
	float length;
	length = D3DXVec2LengthSq(&vDistance);

	//1と2の半径を足して2乗する
	float size = (size1 + size2) * (size1 + size2);

	//足した半径とベクトル長とで大きさを判定する
	//差分のベクトル長の方が小さければヒットしている
	if (length < size)
	{
		return true;
	}

	return false;
}