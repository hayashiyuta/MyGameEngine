#pragma once

#include <d3d11.h>
#include <assert.h>
//�����J Direct3D�̊e�@�\���g����悤�ɂȂ�
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Direct3D

{
	extern ID3D11Device* pDevice;		//�f�o�C�X
	extern ID3D11DeviceContext* pContext;		//�f�o�C�X�R���e�L�X�g

	//������
	void Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	void InitShader();

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

};