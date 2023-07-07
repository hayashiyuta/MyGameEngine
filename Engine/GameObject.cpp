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
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//‚·‚×‚Ä‚ÌŽq‹Ÿ‚ÌUpdateSub‚ðŒÄ‚Ô
	{
		(*itr)->UpdateSub();
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
