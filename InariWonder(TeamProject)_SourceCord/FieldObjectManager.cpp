// ===================================================
//	FieldObjectManager.cpp					ŠÇ—ƒNƒ‰ƒX
//	•“¡ŠCl								2023/11/22
// ===================================================
#include "FieldObjectManager.h"
#include "FieldObject.h"
#include "Map.h"

FieldObjectManager::FieldObjectManager()
{
}

FieldObjectManager::~FieldObjectManager()
{
	for (auto& p : _ObjectList) {
		delete p;
	}
	_ObjectList.clear();
 }

void FieldObjectManager::SetFieldObject(FieldObject* fo)
{
	_ObjectList.push_back(fo);
}


FieldObject* FieldObjectManager::GetObject_SearchByTag(FIELD_OBJECT_KIND tag)
{
	//_ObjectList.


	return nullptr;
}

void FieldObjectManager::CleanList()
{
	_ObjectList.remove_if([](FieldObject* fo) {
		if (fo->GetObjectData().kind == KIND_PLAYER ||
			fo->GetObjectData().kind == KIND_FOX)return false;
		else {
			if (fo->GetIsDead()) {
				delete fo;
				return true;
			}
		}
		return false;
		}
	);
}

void FieldObjectManager::ObjectMove(Map* m)
{
	for (FieldObject* fo : _ObjectList) {
		D3DXVECTOR2 move = fo->GetMoveValue();
		if (m->GetObjectColliderFlug(fo->GetObjectData(), move))
			fo->SetMoveValue(m->GetObjectMoveValue(fo->GetObjectData(), move));
	}

}

void FieldObjectManager::Update()
{
	for (auto& p : _ObjectList)
	{
		p->UpdateStart();
	}
	for (auto& p : _ObjectList)
	{
		p->Update();
	}
	for (auto& p : _ObjectList)
	{
		p->UpdateEnd();
	}
}

void FieldObjectManager::Draw(D3DXVECTOR2 decriment)
{
	for (auto& p : _ObjectList)
	{
		p->Draw(decriment);
	}
}

void FieldObjectManager::Delete()
{
	_ObjectList.remove_if([](FieldObject* fo)
		{
			if (fo->GetIsDead()) {
				delete fo;
				return true;
			}
			return false;

		}
	);
}

void FieldObjectManager::Collider()
{
	for (auto it = _ObjectList.begin(); it != _ObjectList.end(); it++)
	{
		for (auto it2 = it; it2 != _ObjectList.end(); it2++)
		{
			FieldObject* fo1 = *it;
			FieldObject* fo2 = *it2;

			if (fo1->GetHitTrigger(fo2->GetObjectData())) {
				fo1->Hit(fo2->GetObjectData());
				fo2->Hit(fo1->GetObjectData());
			}
		}
	}
}
