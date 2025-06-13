/////////////////////////////////////////////////////////
//  当たり判定管理.h						Collider.h
//		武藤海人						2024/01/13
/////////////////////////////////////////////////////////

#include "FieldObject.h"

#pragma once

//止まっているod1にod2がオールドとナウを使って当たってるか確認

bool BBTrriger(OBJECT_DATA od1, OBJECT_DATA od2);
bool BCTrriger(OBJECT_DATA od1, OBJECT_DATA od2);

bool BBHit(OBJECT_DATA od1, OBJECT_DATA od2);
bool BCHit(OBJECT_DATA od1, OBJECT_DATA od2);

bool BBRerese(OBJECT_DATA od1, OBJECT_DATA od2);
bool BCRerese(OBJECT_DATA od1, OBJECT_DATA od2);