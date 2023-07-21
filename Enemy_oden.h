#pragma once
#include "Engine/GameObject.h"


//■■シーンを管理するクラス
class Enemy_oden : public GameObject
{
	int hModel_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy_oden(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
