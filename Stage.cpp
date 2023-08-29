#include "Stage.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
	for (int i = 0; i < MODEL_NUM; i++)
	{
		hModel_[i] = -1;
	}
	//�e�[�u����������
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			table_[x][z] = 0;
		}
	}
}

//������
void Stage::Initialize()
{
	string ModelName[] = {
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};
	string name_base = "Assets\\";
	//���f���f�[�^�̃��[�h
	for (int i = 0; i < MODEL_NUM; i++)
	{
		hModel_[i] = Model::Load(name_base+ModelName[i]);
		assert(hModel_[i] >= 0);
	}
	
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			table_[x][z] = x%5;
		}
	}
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{

			int type = table_[x][z];
			Transform trans;
			trans.position_.x = x;
			trans.position_.z = z;
			Model::SetTransform(hModel_[type], trans);
			Model::Draw(hModel_[type]);
		}
	}
	
}

//�J��
void Stage::Release()
{
}