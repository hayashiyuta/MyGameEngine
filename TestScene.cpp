#include "TestScene.h"
#include"Engine/Input.h"
#include"PlayScene.h"
#include "Engine/SceneManager.h"
//�R���X�g���N�^
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
}

//�X�V
void TestScene::Update()
{
	GameObject* dbgTest = FindObject("SceneManager");
	if (Input::IsKeyUp(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}