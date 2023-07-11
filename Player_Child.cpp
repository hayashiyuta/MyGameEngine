#include "Player_Child.h"
#include"Engine/Fbx.h"
//�R���X�g���N�^
Player_Child::Player_Child(GameObject* parent)
	: GameObject(parent, "Player_Child"), pFbx(nullptr)
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	this->transform_.position_.z = -1;
	
	this->transform_.scale_.x = 0.2;
	this->transform_.scale_.y = 0.2;
	this->transform_.scale_.z = 0.2;
	this->transform_.position_.x = -2;
}

//������
void Player_Child::Initialize()
{
}

//�X�V
void Player_Child::Update()
{
	transform_.rotate_.y++;
}

//�`��
void Player_Child::Draw()
{
	pFbx->Draw(transform_);
}

//�J��
void Player_Child::Release()
{
	pFbx->Release();
	delete pFbx;
}
