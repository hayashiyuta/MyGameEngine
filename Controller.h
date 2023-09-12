#pragma once
#include "Engine/GameObject.h"


//�����V�[�����Ǘ�����N���X
class Controller : public GameObject
{
	
	XMVECTOR velocity_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Controller(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};