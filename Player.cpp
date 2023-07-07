#include "Player.h"
#include"Engine/Fbx.h"
//コンストラクタ
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

//初期化
void Player::Initialize()
{
}

//更新
void Player::Update()
{
	this->transform_.rotate_.y += 0.1;
}

//描画
void Player::Draw()
{
	pFbx->Draw(transform_);
}

//開放
void Player::Release()
{
	pFbx->Release();
	delete pFbx;
}