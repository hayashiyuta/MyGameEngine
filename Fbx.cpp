#include "Fbx.h"

Fbx::Fbx():pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), polygonCount_(0)
{

}

HRESULT Fbx::Load(std::string fileName)
{
	//�}�l�[�W���𐶐�
	FbxManager* pFbxManager = FbxManager::Create();

	//�C���|�[�^�[�𐶐�
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//�V�[���I�u�W�F�N�g��FBX�t�@�C���̏��𗬂�����
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//���b�V�������擾
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//�e���̌����擾
	vertexCount_ = mesh->GetControlPointsCount();	//���_�̐�
	polygonCount_ = mesh->GetPolygonCount();	//�|���S���̐�
	materialCount_ = pNode->GetMaterialCount();

	//���݂̃J�����g�f�B���N�g�����o���Ă���
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	//������fileName����f�B���N�g���������擾
	char dir[MAX_PATH];
	_splitpath_s(fileName.c_str(), nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);
	

	//�J�����g�f�B���N�g���ύX
	SetCurrentDirectory(dir);


	InitVertex(mesh);		//���_�o�b�t�@����
	InitIndex(mesh);		//�C���f�b�N�X�o�b�t�@����
	IntConstantBuffer();	//�R���X�^���g�o�b�t�@����
	InitMaterial(pNode);

	//�J�����g�f�B���N�g�������ɖ߂�
	SetCurrentDirectory(defaultCurrentDir);

	//�}�l�[�W�����
	pFbxManager->Destroy();
	return S_OK;
}

//���_�o�b�t�@����
void Fbx::InitVertex(fbxsdk::FbxMesh* mesh)
{
	//���_��������z��
	VERTEX* vertices = new VERTEX[vertexCount_];
	
	//�S�|���S��
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3���_��
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//���ׂ钸�_�̔ԍ�
			int index = mesh->GetPolygonVertex(poly, vertex);

			//���_�̈ʒu
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			//���_��UV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			vertices[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);
		}
	}
	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;//sizeof(vertices[0]) * vertexCount_
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = &vertices[0];
	

	Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
}

//�C���f�b�N�X�o�b�t�@����
void Fbx::InitIndex(fbxsdk::FbxMesh* mesh)
{
	pIndexBuffer_ = new ID3D11Buffer * [materialCount_];

	int* index = new int[polygonCount_ * 3];

	for (int i = 0; i < materialCount_; i++)
	{
		int count = 0;

		//�S�|���S��
		for (DWORD poly = 0; poly < polygonCount_; poly++)
		{
			FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);

			if (mtlId == i)
			{
				//3���_��
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					index[count] = mesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}
		}

		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;//sizeof(index)
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;


		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = index;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
	}
}



void Fbx::IntConstantBuffer()
{
	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
}

void Fbx::InitMaterial(fbxsdk::FbxNode* pNode)
{
	pMaterialList_ = new MATERIAL[materialCount_];

	for (int i = 0; i < materialCount_; i++)
	{
		//i�Ԗڂ̃}�e���A�������擾
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//�e�N�X�`�����
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//�e�N�X�`���̐���
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//�e�N�X�`������
		if (fileTextureCount == true)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();

			//�t�@�C����+�g�������ɂ���
			char name[_MAX_FNAME];	//�t�@�C����
			char ext[_MAX_EXT];	//�g���q
			_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			wsprintf(name, "%s%s", name, ext);

			//�t�@�C������e�N�X�`���쐬
			pMaterialList_[i].pTexture = new Texture;
			pMaterialList_[i].pTexture->Load(name);
		}

		//�e�N�X�`������
		else
		{
			pMaterialList_[i].pTexture = nullptr;
		}
	}
}

void    Fbx::Draw(Transform& transform)
{
	Direct3D::SetShader(SHADER_3D);
	transform.Calclation();//�g�����X�t�H�[�����v�Z
	CONSTANT_BUFFER cb;
	D3D11_MAPPED_SUBRESOURCE pdata;
	cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(transform.GetWorldMatrix());

	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

	//ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	//Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	//ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	//Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);



	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ

	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	for (int i = 0; i < materialCount_; i++)
	{
		// �C���f�b�N�X�o�b�t�@�[���Z�b�g
		stride = sizeof(int);
		offset = 0;
		Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);

		//�R���X�^���g�o�b�t�@
		Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
		Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

		if (pMaterialList_[i].pTexture)
		{
			ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
			Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
			ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture->GetSRV();
			Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);
		}

		Direct3D::pContext_->DrawIndexed(polygonCount_ * 3, 0, 0);
	}
	
}

void    Fbx::Release()
{
	//SAFE_RELEASE(pConstantBuffer_);
	//SAFE_RELEASE(pIndexBuffer_);
	//SAFE_RELEASE(pVertexBuffer_);
}