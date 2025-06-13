#include "FieldEventManager.h"

FieldEventManager::~FieldEventManager()
{
	for (auto& a : _FieldEventList) {
		delete a;
	}
	_FieldEventList.clear();
}

void FieldEventManager::Update()
{
	for (auto& a : _FieldEventList) {
		a->Update();
	}
}
