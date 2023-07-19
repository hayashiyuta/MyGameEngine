#pragma once
#include "GameObject.h"

//�Q�[���̃V�[�����
enum SCENE_ID
{
	SCENE_ID_TEST = 0,
	SCENE_ID_PLAY,
	SCENE_ID_PLAYSCENE,
	
};

//�����V�[�����Ǘ�����N���X
class SceneManager : public GameObject
{
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SceneManager(GameObject* parent);
	~SceneManager();
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void ChangeScene(SCENE_ID _next);
};
