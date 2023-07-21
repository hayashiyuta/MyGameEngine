#include "Player_Child.h"
#include"Engine/Fbx.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"
//�R���X�g���N�^
Player_Child::Player_Child(GameObject* parent)
	: GameObject(parent, "Player_Child"), pFbx(nullptr), hModel_(-1)
{
}

//������
void Player_Child::Initialize()
{
	
	hModel_ = Model::Load("Assets/oden.fbx");
	assert(hModel_ >= 0);
	this->transform_.scale_.x = 0.2;
	this->transform_.scale_.y = 0.2;
	this->transform_.scale_.z = 0.2;
	this->transform_.position_.x = 2;
	this->transform_.position_.y = 1;
	this->transform_.rotate_.x = 90;
	SphereCollider* col = new SphereCollider(1.0f);
	AddCollider(col);
}

//�X�V
void Player_Child::Update()
{
	transform_.rotate_.z += 15;
	transform_.position_.z += 0.5f;
	if (transform_.position_.z > 50)
	{
		KillMe();
	}
	//if (transform_.rotate_.y++ > 300)
		//KillMe();
}

//�`��
void Player_Child::Draw()
{
	Model::SetTransfome(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player_Child::Release()
{
	//pFbx->Release();
	//delete pFbx;
}
