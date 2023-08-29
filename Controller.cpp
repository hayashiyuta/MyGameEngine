#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Controller::Controller(GameObject* parent)
	: GameObject(parent, "Controller"), velocity_(XMVectorSet(0, 0, 0, 0))
{
}

void Controller::Initialize()
{
	
	transform_.position_ = XMFLOAT3(7, 1, 7);
	Camera::SetPosition(XMFLOAT3(7, 1, 1));

}

void Controller::Update()
{
	velocity_ = XMVectorSet(0, 0, 0, 0);
	XMFLOAT3 cameraPos = XMFLOAT3(0, 0, -6);

	if (Input::IsKey(DIK_W))
	{
		velocity_ += XMVectorSet(0, 0, 0.1, 0);
	}
	if (Input::IsKey(DIK_S))
	{
		velocity_ += XMVectorSet(0, 0, -0.1, 0);
	}
	if (Input::IsKey(DIK_A))
	{
		velocity_ += XMVectorSet(-0.1, 0, 0, 0);
	}
	if (Input::IsKey(DIK_D))
	{
		velocity_ += XMVectorSet(0.1, 0, 0.0, 0);
	}

	//rotate
	static int rotNum_y = 0;
	static int rotNum_x = 0;
	
	if (Input::IsKey(DIK_UP))
	{
		rotNum_x++;
		if (rotNum_x >= 89.0f)
		{
			rotNum_x = 89;
		}
	}
	if (Input::IsKey(DIK_DOWN))
	{
		rotNum_x--;
		if (rotNum_x <= 0.0f)
		{
			rotNum_x = 0.1f;
		}
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		rotNum_y++;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		rotNum_y--;
	}
	transform_.rotate_.y = rotNum_y;
	transform_.rotate_.x = rotNum_x;
	XMVECTOR cameraBase = XMLoadFloat3(&cameraPos);
	XMMATRIX xrot = XMMatrixRotationX(XMConvertToRadians(rotNum_x));
	//XMVECTOR CameraRotVec_x = XMVector3Transform(cameraBase, xrot);
	XMMATRIX yrot = XMMatrixRotationY(XMConvertToRadians(rotNum_y));
	//XMVECTOR CameraRotVec_y = XMVector3Transform(cameraBase, yrot);
	XMMATRIX rot = xrot * yrot;
	XMVECTOR CameraRotVec = XMVector3Transform(cameraBase, rot);
	/*XMFLOAT3 v;
	XMStoreFloat3(&v, CameraRotVec_x+ CameraRotVec_y);*/
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	Camera::SetPosition(vPos + CameraRotVec);
	Camera::SetTarget(XMFLOAT3(transform_.position_));

	velocity_ = XMVector3Transform(velocity_, yrot);

	transform_.position_ += velocity_;
	//回転行列
	/*XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//現在位置をベクトルに置く
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	//移動ベクトル
	XMVECTOR frontMove = XMVectorSet(0, 0, 0.1f, 0);
	frontMove = XMVector3TransformCoord((frontMove, mRotate));
	*/
	
	//カメラ
	//XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);//
	//Camera::SetPosition(vPos + vCam);
	//Camera::SetTarget(transform_.position_);
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
