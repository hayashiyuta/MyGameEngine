#pragma once

#include "Transform.h"
#include <string>
#include<list>

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

class GameObject
{
private:
	struct OBJECT_STATE
	{
		unsigned initilized : 1; //初期化済か
		unsigned entered : 1;    //更新するか
		unsigned visible : 1;    //描画するか
		unsigned dead : 1;       //削除するか
	};
	OBJECT_STATE state_;
protected:
	std::list<GameObject*> childList_;
	Transform	transform_;
	GameObject* pParent_;
	std::string	objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() =0;
	virtual void Update() =0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* p;
		p = new T(parent);
		p->Initialize();
		childList_.push_back(p);
		return p;
	}
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();
	bool IsDead();
	void KillMe();
	void SetPosition(XMFLOAT3 position_);
};
