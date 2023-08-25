#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Fbx;

//■■シーンを管理するクラス
class Player_Child : public GameObject
{
	Fbx* pFbx;
	int hModel_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player_Child(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//何かに当たった
	//引数：pTarget 当たった相手
	void OnCollision(GameObject* pTarget) override;
};