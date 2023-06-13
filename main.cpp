#include <Windows.h>
#include"Direct3D.h"
//#include"Quad.h"
#include"Dice.h"
#include "Camera.h"
const char* WIN_GAME_NAME = "サンプルゲーム";
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ
float R;
float R2;
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
	Dice* pDice = new Dice();
	//Direct3D初期化
	Direct3D::Initialize(winW, winH, hWnd);
	Camera::Initialize();
	Camera::SetTarget(XMFLOAT3(0,0, 0));
	
	/*if (FAILED(pQuad->Initialize()))
	{
		return 0;
	}*/

	if (FAILED(pDice->Initialize()))
	{
		return 0;
	}

  //メッセージループ（何か起きるのを待つ）
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
			
			//pQuad = new 

			//描画処理
			//XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(45));
			R += 0.04f;
			XMMATRIX mat = XMMatrixTranslation(0, 0, 0) * XMMatrixRotationX(XMConvertToRadians(-45 + R)) *XMMatrixRotationZ(XMConvertToRadians(-30 + R));
			//pQuad->Draw(mat);
			pDice->Draw(mat);
			Direct3D::EndDraw();
			
			

		}
	}
	//SAFE_DELETE(pQuad);
	SAFE_DELETE(pDice);
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
	
