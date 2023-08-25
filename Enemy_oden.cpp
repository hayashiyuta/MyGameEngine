#include "Enemy_oden.h"
#include"Engine/Model.h"
#include"Engine/SphereCollider.h"

//コンストラクタ
Enemy_oden::Enemy_oden(GameObject* parent)
	: GameObject(parent, "Enemy_oden"), hModel_(-1)
{
}

//初期化
void Enemy_oden::Initialize()
{
	hModel_ = Model::Load("Assets/oden.fbx");
	assert((hModel_ >= 0));
	this->transform_.position_.z = 10;
	SphereCollider* col = new SphereCollider(3.0f);
	AddCollider(col);
}

//更新
void Enemy_oden::Update()
{
}

//描画
void Enemy_oden::Draw()
{
	Model::SetTransfome(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Enemy_oden::Release()
{
}