#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Fbx;

//�����V�[�����Ǘ�����N���X
class Player_Child : public GameObject
{
	Fbx* pFbx;
	int hModel_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player_Child(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�����ɓ�������
	//�����FpTarget ������������
	void OnCollision(GameObject* pTarget) override;
};