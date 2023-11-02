#pragma once
#include "Engine/GameObject.h"


//�����V�[�����Ǘ�����N���X
class Controller : public GameObject
{
	
	XMVECTOR velocity_;
	XMFLOAT3 cameraWheel = XMFLOAT3(0, 0, 0);
	XMFLOAT3 cameraWheelBase = XMFLOAT3(0, 0, 0);
	XMFLOAT3 cameraWheelPlas = XMFLOAT3(0, 0, 1);
	XMFLOAT3 cameraWheelLimit = XMFLOAT3(0, 0, 4);
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
