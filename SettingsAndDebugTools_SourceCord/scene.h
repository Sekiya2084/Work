#pragma once

#include <list>
#include "gameobject.h"
//#include "meshField.h"



class Scene
{
protected:

	// GameObject* m_GameObject[MAX_GAMEOBJECT]{};
	std::list<GameObject*> m_GameObject[3];

public:
	virtual ~Scene() {} //デストラクタ

	virtual void Init() {
	}

	template <typename T>//テンプレート関数
	T* AddGameObject(int Layer) {

		T* gameObject = new T;
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;
	}

	template <typename T>//テンプレート関数
	T* GetGameObject() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)
					return ret;
			}
		}
		return nullptr;
	}
	

	template <typename T>//テンプレート関数
	std::vector <T*> GetGameObjects() {
		std::vector<T*> objectList;
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)
					objectList.push_back(ret);
			}
		}
		return objectList;
	}


	virtual void Uninit() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}
	virtual void Update() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Update();
			}
			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}
	}
	virtual void Draw() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Draw();
			}
		}
	}

};