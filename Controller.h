#pragma once
#include "Engine/GameObject.h"


//■■シーンを管理するクラス
class Controller : public GameObject
{
	
	XMVECTOR velocity_;
	XMFLOAT3 cameraWheel = XMFLOAT3(0, 0, 0);
	XMFLOAT3 cameraWheelBase = XMFLOAT3(0, 0, 0);
	XMFLOAT3 cameraWheelPlas = XMFLOAT3(0, 0, 1);
	XMFLOAT3 cameraWheelLimit = XMFLOAT3(0, 0, 4);
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Controller(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
