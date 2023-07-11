#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(GameObject* parent, const std::string& name):childList_(0), pParent_(parent), objectName_(name)
{
	state_ = { 0, 1, 1, 0 };
}

GameObject::~GameObject()
{

}
//íœ‚·‚é‚©‚Ç‚¤‚©
bool GameObject::IsDead()
{
	return (state_.dead != 0);
}

//Ž©•ª‚ðíœ‚·‚é
void GameObject::KillMe()
{
	state_.dead = 1;
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//‚·‚×‚Ä‚ÌŽq‹Ÿ‚ÌUpdateSub‚ðŒÄ‚Ô
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
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//‚·‚×‚Ä‚ÌŽq‹Ÿ‚ÌDrawSub‚ðŒÄ‚Ô
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//‚·‚×‚Ä‚ÌŽq‹Ÿ‚ÌReleaseSub‚ðŒÄ‚Ô
	{
		(*itr)->ReleaseSub();
	}
}

