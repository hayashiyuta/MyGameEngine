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
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//���ׂĂ̎q����UpdateSub���Ă�
	{
		(*itr)->UpdateSub();
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//���ׂĂ̎q����DrawSub���Ă�
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//���ׂĂ̎q����ReleaseSub���Ă�
	{
		(*itr)->ReleaseSub();
	}
}
