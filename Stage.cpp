#include "Stage.h"
#include "Engine/Model.h"
#include"Engine/Input.h"
#include"Engine/Direct3D.h"
#include"resource.h"
#include"Engine/Fbx.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),mode_(0),select_(0)
{
	for (int i = 0; i < MODEL_NUM; i++)
	{
		hModel_[i] = -1;
	}
	//テーブルを初期化
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			SetBlock(x, z, (BLOCKTYPE)(0));
			//table_[x][z].HEGHT = 1;
			SetBlockHeght(x, z, 0);
		}
	}
}

//初期化
void Stage::Initialize()
{
	string ModelName[] = {
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};
	string name_base = "Assets\\";
	//モデルデータのロード
	for (int i = 0; i < MODEL_NUM; i++)
	{
		hModel_[i] = Model::Load(name_base+ModelName[i]);
		assert(hModel_[i] >= 0);
	}
	
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			
			SetBlock(x,z, (BLOCKTYPE)(x % 5)) ;
		}
	}
}

//更新
void Stage::Update()
{
	
	float w = (float)(Direct3D::scrWidth /2.0f);//画面幅の半分
	float h = (float)(Direct3D::scrHeight/2.0f);//画面高さの半分

	//0ffsetx,yは0
	//minZ =0 maxZ =1

	XMMATRIX vp =
	{
		 w,   0,  0, 0,
		 0,  -h,  0, 0,
		 0,   0,  1, 0,
		 w,   h,  0, 1
	};
	
	//ビューポート
	XMMATRIX invVP = XMMatrixInverse(nullptr,vp);
	//プロジェクション変換
	XMMATRIX invProj = XMMatrixInverse(nullptr,Camera::GetProjectionMatrix());
	//ビュー変換

	XMMATRIX invView = XMMatrixInverse(nullptr,Camera::GetViewMatrix());
	XMFLOAT3 mousePosFront = Input::GetMousePosition();//マウスポジゲット
	mousePosFront.z = 0.0f;
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	//�@　mousePosFrontをベクトルに変換
	XMVECTOR vMousePosF = XMLoadFloat3(&mousePosFront);
	//�A　�@にinvVP、invProj、invViewをかける
	vMousePosF = XMVector3TransformCoord(vMousePosF, invVP * invProj * invView);
	//�B　mousePosBackをベクトルに変換
	XMVECTOR vMousePosB = XMLoadFloat3(&mousePosBack);
	//�C　�BにinvVP、invProj、invViewをかける
	vMousePosB = XMVector3TransformCoord(vMousePosB, invVP * invProj * invView);

	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			for (int y = 0; y < table_[x][z].HEGHT + 1; y++)
			{
				//�D　�Aから�Cに向かってレイを打つ
				RayCastData data;
				XMStoreFloat4(&data.start, vMousePosF);
				XMStoreFloat4(&data.dir, vMousePosB - vMousePosF);
				Transform trans;
				trans.position_.x = x;
				trans.position_.y = y;
				trans.position_.z = z;
				Model::SetTransform(hModel_[0], trans);

				Model::RayCast(hModel_[0], data);
				//�E　レイが当たったらブレークポイントで止める
				
				
				if (data.hit)
				{
					table_[x][z].raydist = data.dist;

					if (table_[x][z].raydist < distmin)
					{
						if (Input::IsMouseButtonDown(0))
						{
							//何らかの処理
							table_[x][z].HEGHT++;
							break;

							return;
						}
						distmin = table_[x][z].raydist;
					}

					
				}
			}
		}
	}

	
	
}

//描画
void Stage::Draw()
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			for (int y = 0; y < table_[x][z].HEGHT+1; y++)
			{
				int type_ = table_[x][z].type;

				Transform trans;
				trans.position_.x = x;
				trans.position_.z = z;
				trans.position_.y = y;
				Model::SetTransform(hModel_[type_], trans);
				Model::Draw(hModel_[type_]);
			}
			
		}
	}
	
}

//開放
void Stage::Release()
{
}

//偽物(何か処理をしたらTRUE、何もしなかったらFALSEを返す)
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		//ダイアログできた
	case WM_INITDIALOG:
		//ラジオボタンの初期値
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP),BM_SETCHECK,BST_CHECKED,0);
		//コンボボタンの初期値
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"デフォルト");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"レンガ");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"草");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"土");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"水");

		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);

		return TRUE;
	case WM_COMMAND:
		mode_ = LOWORD(wp) - IDC_RADIO_UP;
		select_ = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
	}
	return FALSE;
	//LOWORD(wp)
}