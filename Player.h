#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Fbx;

class Player : public GameObject
{
	Fbx* pFbx;
	int hModel_;//���f���ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	
};