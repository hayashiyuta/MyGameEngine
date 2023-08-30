#include "Stage.h"
#include "Engine/Model.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
	for (int i = 0; i < MODEL_NUM; i++)
	{
		hModel_[i] = -1;
	}
	//テーブルを初期化
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			SetBlock(x, z, DEFAULT);
			table_[x][z].HEGHT = 1;
		}
	}
}

//初期化
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
	//モデルデータのロード
	for (int i = 0; i < MODEL_NUM; i++)
	{
		hModel_[i] = Model::Load(name_base+ModelName[i]);
		assert(hModel_[i] >= 0);
	}
	
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			
			SetBlock(x,z, (BLOCKTYPE)(x % 5)) ;
		}
	}
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			for (int y = 0; y < table_[x][z].HEGHT+1; y++)
			{
				int type_ = table_[x][z].type;

				Transform trans;
				trans.position_.x = x;
				trans.position_.z = z;
				trans.position_.y = y;
				Model::SetTransform(hModel_[type_], trans);
				Model::Draw(hModel_[type_]);
			}
			
		}
	}
	
}

//開放
void Stage::Release()
{
}