#include "Ability.h"
#include "sprite.h"

//一端空で初期化
 FieldObjectManager* Ability::_FOManager = nullptr;

//NormalAbility::NormalAbility(FOX_ABILITY fa)
//{
//	//_TexNo=Load
//};

 Ability::~Ability()
 {
	 delete _TexData;
 }
