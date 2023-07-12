#include "Player_Child.h"
#include"Engine/Fbx.h"
//コンストラクタ
Player_Child::Player_Child(GameObject* parent)
	: GameObject(parent, "Player_Child"), pFbx(nullptr)
{
}

//初期化
void Player_Child::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/oden.fbx");
	this->transform_.scale_.x = 0.2;
	this->transform_.scale_.y = 0.2;
	this->transform_.scale_.z = 0.2;
	this->transform_.position_.x = 2;
	this->transform_.position_.y = 1;
}

//更新
void Player_Child::Update()
{
	transform_.rotate_.y++;
	if (transform_.rotate_.y++ > 300)
		KillMe();
}

//描画
void Player_Child::Draw()
{
	pFbx->Draw(transform_);
}

//開放
void Player_Child::Release()
{
	//pFbx->Release();
	//delete pFbx;
}
