#include "Player_Child.h"
#include"Engine/Fbx.h"
//コンストラクタ
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

//初期化
void Player_Child::Initialize()
{
}

//更新
void Player_Child::Update()
{
	transform_.rotate_.y++;
}

//描画
void Player_Child::Draw()
{
	pFbx->Draw(transform_);
}

//開放
void Player_Child::Release()
{
	pFbx->Release();
	delete pFbx;
}
