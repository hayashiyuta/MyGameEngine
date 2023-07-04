#include <Windows.h>
#include"Direct3D.h"
//#include"Quad.h"
//#include"Dice.h"
//#include"Spirete.h"
#include "Camera.h"
#include"Transform.h"
#include"Fbx.h"
#include"Input.h"
const char* WIN_GAME_NAME = "サンプルゲーム";
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ
float R;
//プロトタイプ宣言(ウィンドウプロシージャ)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



//エントリーポイント　プログラムのスタート地点
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow )
//HINSTANCE　インスタンスハンドル
{
	HRESULT hr;
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); //背景（白）
	RegisterClassEx(&wc);  //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);//FALSE メニューの有無　ある場合true
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ


	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		WIN_GAME_NAME,     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                 //ウィンドウ幅
		winH,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);
	//Quad* pQuad = new Quad();
	//Dice* pDice = new Dice();
	//Spirete* pSpirete = new Spirete();
	
	//Direct3D初期化
	Direct3D::Initialize(winW, winH, hWnd);
	//DirectInputの初期化
	Input::Initialize(hWnd);
	Camera::Initialize();
	Camera::SetTarget(XMFLOAT3(0,0, 0));

	Fbx* pFbx = new Fbx();
	pFbx->Load("Assets/ODEN.fbx");
	
	/*if (FAILED(pQuad->Initialize()))
	{
		return 0;
	}*/

	/*if (FAILED(pDice->Initialize()))
	{
		return 0;
	}

	if (FAILED(pSpirete->Initialize()))
	{
		return 0;
	}*/
	

  //メッセージループ（何か起きるのを待つ）
	Transform* pTransform = new Transform();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))//PeekMessage メッセージを集める
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			Camera::Update();
			//ゲームの処理
			
			Direct3D::BeginDraw();
			//入力情報の更新
			Input::Update();
			/*if (Input::IsKeyUp(DIK_ESCAPE))
			{
				static int cnt = 0;
				cnt++;
				if (cnt >= 3)
				{
					PostQuitMessage(0);
				}
				
			}*/
			
			//pQuad = new 

			//描画処理
			//XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(45));
			pTransform->Calclation();
			//XMMATRIX mat = pTransform->GetWorldMatrix();//XMMatrixRotationX(XMConvertToRadians(-30 + R)) * XMMatrixRotationZ(XMConvertToRadians(-45 + R)) * XMMatrixTranslation(-2, 0, 0); // ;//XMMatrixTranslation(0, 0, 0) * ;
			//pQuad->Draw(mat);
			static Transform DiceTransform;
			Transform FbxTransform;
			static float angle = 0;
			angle += 0.00f;
			//DiceTransform.position_.z = -1;
			//DiceTransform.rotate_.y = angle;
			//DiceTransform.rotate_.z = angle;
			//pDice->Draw(DiceTransform);
			//pFbx->Draw(DiceTransform);
			XMMATRIX matS = XMMatrixTranslation(0, 0, 0);
			//pSpirete->Draw(matS);
			if (Input::IsKey(DIK_RIGHT))
			{
				DiceTransform.position_.x += 0.01f;
				
			}
			if (Input::IsKey(DIK_LEFT))
			{
				DiceTransform.position_.x -= 0.01f;

			}
			pFbx->Draw(DiceTransform);
			Direct3D::EndDraw();
			
			

		}
	}
	//SAFE_DELETE(pQuad);
	//SAFE_DELETE(pDice);
	SAFE_DELETE(pFbx);
	Input::Release();
	//SAFE_DELETE(pSpirete);
	Direct3D::Release();
	//pQuad->Release();

	//delete pQuad;
	return 0;
}
//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //ウィンドウが閉じられたらプログラム終了 これをなくすとプログラムが終了しない
		return 0;
	
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);//ウィンドウの拡縮などのデフォルトの動き
}
	
