#pragma once
#include "Engine/GameObject.h"

namespace {
	const int MODEL_NUM{ 5 };
	const int XSIZE{ 15 };
	const int ZSIZE{ 15 };
	enum BLOCKTYPE
	{
		DEFAULT,BRICK,GRASS,SAND,WATER
	};
}

struct{
	BLOCKTYPE type;
	int HEGHT;
}table_[XSIZE][ZSIZE];

//�����V�[�����Ǘ�����N���X
class Stage : public GameObject
{
	int hModel_[MODEL_NUM];    //���f���ԍ�
	//int table_[XSIZE][ZSIZE];
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetBlock(int _x, int _z, BLOCKTYPE _type);
	void SetBlockHeght(int _x, int _z, int _height);
};
