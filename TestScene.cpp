#include "TestScene.h"
#include"Engine/Input.h"
#include"PlayScene.h"
#include "Engine/SceneManager.h"
//コンストラクタ
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
}

//更新
void TestScene::Update()
{
	GameObject* dbgTest = FindObject("SceneManager");
	if (Input::IsKeyUp(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}