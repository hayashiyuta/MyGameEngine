#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(GameObject* parent, const std::string& name):childList_(0), pParent_(parent), objectName_(name)
{

}

GameObject::~GameObject()
{

}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//すべての子供のUpdateSubを呼ぶ
	{
		(*itr)->UpdateSub();
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//すべての子供のDrawSubを呼ぶ
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//すべての子供のReleaseSubを呼ぶ
	{
		(*itr)->ReleaseSub();
	}
}
