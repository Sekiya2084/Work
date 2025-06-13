#pragma once

#include "FieldObject.h"

class Boss : public FieldObject
{
public:
	Boss(FieldObjectManager* myfom) :FieldObject(myfom){}
	~Boss() {}
};