#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(GameObject* parent, const std::string& name):childList_(0), pParent_(parent), objectName_(name)
{
	state_ = { 0, 1, 1, 0 };
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{

}
//削除するかどうか
bool GameObject::IsDead()
{
	return (state_.dead != 0);
}

//自分を削除する
void GameObject::KillMe()
{
	state_.dead = 1;
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//すべての子供のUpdateSubを呼ぶ
	{
		(*itr)->UpdateSub();
	}
	for (auto it = childList_.begin(); it != childList_.end();)
	{
		if ((*it)->IsDead() == true)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}
		else
		{
			it++;
		}
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
	
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//すべての子供のReleaseSubを呼ぶ
	{
		
		(*itr)->ReleaseSub();//*itrのリリースを呼ぶ
		SAFE_DELETE(*itr);//*itrを消す
	}
	Release();
}

void GameObject::SetPosition(XMFLOAT3 position_)
{
	transform_.position_ = position_;

}