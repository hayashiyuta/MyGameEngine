#include "Player.h"
#include"Engine/Fbx.h"
#include"Engine/Input.h"
#include"Player_Child.h"
//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), pFbx(nullptr)
{
	
}

//初期化
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

//更新
void Player::Update()
{
	//this->transform_.rotate_.y += 0.1;
	transform_.rotate_.y++;
	
	/*if (Input::IsKey(DIK_SPACE))
	{
		//何らかの処理
		this->KillMe();
	}*/
	if (transform_.rotate_.y++ > 600)
		KillMe();
}

//描画
void Player::Draw()
{
	pFbx->Draw(transform_);
}

//開放
void Player::Release()
{
	//pFbx->Release();
	//delete pFbx;
}


