#include <Windows.h>
#include"Direct3D.h"
//#include"Quad.h"
//#include"Dice.h"
//#include"Spirete.h"
#include "Camera.h"
#include"Transform.h"
#include"Fbx.h"
#include"Input.h"
const char* WIN_GAME_NAME = "�T���v���Q�[��";
const char* WIN_CLASS_NAME = "SampleGame";  //�E�B���h�E�N���X��
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���
float R;
//�v���g�^�C�v�錾(�E�B���h�E�v���V�[�W��)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



//�G���g���[�|�C���g�@�v���O�����̃X�^�[�g�n�_
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow )
//HINSTANCE�@�C���X�^���X�n���h��
{
	HRESULT hr;
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); //�w�i�i���j
	RegisterClassEx(&wc);  //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);//FALSE ���j���[�̗L���@����ꍇtrue
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����


	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //�E�B���h�E�N���X��
		WIN_GAME_NAME,     //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,                 //�E�B���h�E��
		winH,                 //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);
	//Quad* pQuad = new Quad();
	//Dice* pDice = new Dice();
	//Spirete* pSpirete = new Spirete();
	
	//Direct3D������
	Direct3D::Initialize(winW, winH, hWnd);
	//DirectInput�̏�����
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
	

  //���b�Z�[�W���[�v�i�����N����̂�҂j
	Transform* pTransform = new Transform();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))//PeekMessage ���b�Z�[�W���W�߂�
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			Camera::Update();
			//�Q�[���̏���
			
			Direct3D::BeginDraw();
			//���͏��̍X�V
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

			//�`�揈��
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
//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //�E�B���h�E������ꂽ��v���O�����I�� ������Ȃ����ƃv���O�������I�����Ȃ�
		return 0;
	
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);//�E�B���h�E�̊g�k�Ȃǂ̃f�t�H���g�̓���
}
	
