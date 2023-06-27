#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include"Direct3D.h"
#include"Transform.h"
#include"Camera.h"
#include"Texture.h"


#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")
//class Texture;//�|�C���^�Ȃ炱���OK(�w�b�_���C���N���[�h���Ȃ��Ă���)
class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
	};
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    InitVertex(fbxsdk::FbxMesh* mesh);
	void    InitIndex(fbxsdk::FbxMesh* mesh);
	void    IntConstantBuffer();	//�R���X�^���g�o�b�t�@����
	void    InitMaterial(fbxsdk::FbxNode* pNode);
	void    Draw(Transform& transform);
	void    Release();
};
