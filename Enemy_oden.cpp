#include "Enemy_oden.h"
#include"Engine/Model.h"

//�R���X�g���N�^
Enemy_oden::Enemy_oden(GameObject* parent)
	: GameObject(parent, "Enemy_oden"), hModel_(-1)
{
}

//������
void Enemy_oden::Initialize()
{
	hModel_ = Model::Load("Assets/oden.fbx");
	assert((hModel_ >= 0));
	this->transform_.position_.z = 10;
}

//�X�V
void Enemy_oden::Update()
{
}

//�`��
void Enemy_oden::Draw()
{
	Model::SetTransfome(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Enemy_oden::Release()
{
}