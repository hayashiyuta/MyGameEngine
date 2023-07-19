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
//�폜���邩�ǂ���
bool GameObject::IsDead()
{
	return (state_.dead != 0);
}

//�������폜����
void GameObject::KillMe()
{
	state_.dead = 1;
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//���ׂĂ̎q����UpdateSub���Ă�
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
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//���ׂĂ̎q����DrawSub���Ă�
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//���ׂĂ̎q����ReleaseSub���Ă�
	{
		
		(*itr)->ReleaseSub();//*itr�̃����[�X���Ă�
		SAFE_DELETE(*itr);//*itr������
	}
	Release();
}

void GameObject::SetPosition(XMFLOAT3 position_)
{
	transform_.position_ = position_;

}

GameObject* GameObject::FindChildObject(std::string _objName)
{
	if (_objName == this->objectName_)
	{
		return(this);//������_objName�̃I�u�W�F�N�g�������玩���̃|�C���^��Ԃ�
	}
	else
	{
		for (auto e:childList_)
		{
			GameObject* obj = e->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}
/// <summary>
/// �ċN�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ��֐�
/// </summary>
/// <returns>�߂�l��RootJob�̃A�h���X(GameObject* �^)</returns>
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();

}

GameObject* GameObject::FindObject(std::string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}
