// ===================================================
//	FieldObjectManager.h					管理クラス
//	武藤海人								2023/11/22
// ===================================================
#pragma once
#include "list"
#include <vector>

#include "FieldObject.h"

class Map;

class FieldObjectManager
{
private:
	std::list<FieldObject*> _ObjectList;
public:
	FieldObjectManager();
	~FieldObjectManager();

	void SetFieldObject(FieldObject* fo);		
	         
	FieldObject* GetObject_SearchByTag(FIELD_OBJECT_KIND tag);

	void CleanList();							//プレイヤーと狐以外削除

	//void Update();

	void Draw(D3DXVECTOR2 decriment);



	template <typename T = FieldObject> T* GetObject_SearchByTag(const FIELD_OBJECT_KIND& tag) {
		for (auto object : _ObjectList)
			if (object->GetObjectData().kind == tag)
				if (T* t = dynamic_cast<T*>(object))
					return t;
		return nullptr;
	}

	template <typename T = FieldObject> std::vector<T*> GetObjectByTag(const FIELD_OBJECT_KIND& tag) {
		std::vector<T*> RT;
		for (auto p : _ObjectList) {
			if (p->GetObjectData().kind != tag)continue;
			if (T* t = dynamic_cast<T*>(p))
				RT.push_back(t);
		}
		return RT;
	}

	/*void UpdateStart(void) {
		for (auto object : _ObjectList)
			object->UpdateStart();
	}

	void Update(void) {
		for (auto object : _ObjectList)
			object->Update();
	}

	void UpdateEnd(void) {
		for (auto object : _ObjectList)
			object->UpdateEnd();
	}*/

	void Update(void);

	void Draw(const D3DXVECTOR2& decrement) const {
		for (auto object : _ObjectList)
			object->Draw(decrement);
	}

	void ObjectMove(Map* m);

private:
	void Delete();

	void Collider();
};

//class ObjectPlayer :public FieldObject{
//
//};
//
//class ObjectFox :public FieldObject {
//public:
//	ObjectFox(D3DXVECTOR2 p , D3DXVECTOR2 op , D3DXVECTOR2 s, float r , FIELD_OBJECT_KIND fok , Fox* fox)
//		:FieldObject(OBJECT_DATA(p, op, s, r, fok)), _Fox(fox) {};
//	ObjectFox(OBJECT_DATA od, Fox* fox)
//		:FieldObject(od), _Fox(fox) {};
//
//	void SetFoxPoint(Fox* fox) { _Fox = fox; };
//
//	bool GetHitTrigger(const OBJECT_DATA& od)override ;
//	bool GetHitStay(const OBJECT_DATA& od)override;
//
//	void Update() override { _Fox->UpdateFox(); };
//	void Draw() override { _Fox->DrawFox(); };
//
//protected:
//	bool GetHitSarchArea(const OBJECT_DATA& od);
//	bool GetHitActionArea(const OBJECT_DATA& od);
//
//protected:
//
//	FoxAbility* _AbilityArry;
//
//	Fox* _Fox = nullptr;
//
//	//した2つは能力によって変わる
//	float _SarchRange;		//柵的範囲
//	float _ActionRange;		//アクション範囲
//};
//
//class ObjectWood :public FieldObject {
//public:
//
//
//protected:
//
//
//};