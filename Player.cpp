#include "Player.h"
#include"Engine/Fbx.h"
#include"Engine/Input.h"
#include"Player_Child.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), pFbx(nullptr)
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	this->transform_.position_.z = -1;
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
}

//������
void Player::Initialize()
{
	Instantiate<Player_Child>(this);
}

//�X�V
void Player::Update()
{
	//this->transform_.rotate_.y += 0.1;
	transform_.rotate_.y++;
	if (Input::IsKey(DIK_SPACE))
	{
		//���炩�̏���
		this->KillMe();
	}
	
}

//�`��
void Player::Draw()
{
	pFbx->Draw(transform_);
}

//�J��
void Player::Release()
{
	pFbx->Release();
	delete pFbx;
}