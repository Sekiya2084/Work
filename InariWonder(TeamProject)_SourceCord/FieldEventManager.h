

#ifndef FIELD_EVENT_MANAGER_H
#define FIELD_EVENT_MANAGER_H

#pragma once

#include "FieldEventBath.h"
#include <list>

class FieldEventManager
{
public:
	FieldEventManager() {};
	~FieldEventManager();

	void AddFieldEvent(FieldEventBath* feb) { _FieldEventList.push_back(feb); }

	void Update();

private:
	std::list<FieldEventBath*> _FieldEventList;
};


#endif // !1