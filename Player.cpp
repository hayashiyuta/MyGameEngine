#include "Player.h"
#include"Engine/Fbx.h"
#include"Engine/Input.h"
#include"Player_Child.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), pFbx(nullptr)
{
	
}

//������
void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	this->transform_.position_.z = -1;
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
	GameObject* pCO1 = Instantiate<Player_Child>(this);
	pCO1->SetPosition(XMFLOAT3(2, 1, 0));
	GameObject* pCO2 =  Instantiate<Player_Child>(this);
	pCO2->SetPosition(XMFLOAT3(-2,1,0));
}

//�X�V
void Player::Update()
{
	//this->transform_.rotate_.y += 0.1;
	transform_.rotate_.y++;
	
	/*if (Input::IsKey(DIK_SPACE))
	{
		//���炩�̏���
		this->KillMe();
	}*/
	if (transform_.rotate_.y++ > 600)
		KillMe();
}

//�`��
void Player::Draw()
{
	pFbx->Draw(transform_);
}

//�J��
void Player::Release()
{
	//pFbx->Release();
	//delete pFbx;
}


