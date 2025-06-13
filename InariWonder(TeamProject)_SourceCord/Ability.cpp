#include "Ability.h"
#include "sprite.h"

//ˆê’[‹ó‚Å‰Šú‰»
 FieldObjectManager* Ability::_FOManager = nullptr;

//NormalAbility::NormalAbility(FOX_ABILITY fa)
//{
//	//_TexNo=Load
//};

 Ability::~Ability()
 {
	 delete _TexData;
 }
