#include "Model.h"

namespace Model
{
	
	std::vector<ModelData*>modelList;
}

int Model::Load(std::string fileName)
	{
		ModelData* pData;
		pData = new ModelData;
		pData->fileName_ = fileName;
		pData->pFbx_ = nullptr;
		//filename�������Ȃ�ǂ܂Ȃ�
		for (auto& e : modelList)
		{
			if (e->fileName_ == fileName)
			{
				pData->pFbx_ = e->pFbx_;
				break;
			}
		}
		
		if (pData->pFbx_ == nullptr)
		{
			pData->pFbx_ = new Fbx;
			pData->pFbx_->Load(fileName);
		}
		modelList.push_back(pData);
		return(modelList.size() - 1);
		//�ǂ�ō��

	}

	void Model::SetTransform(int hModel, Transform transfome)
	{
		modelList[hModel]->transfome_ = transfome;
		//���f���ԍ���modekList�̃C���f�b�N�X
	}

	void Model::Draw(int hModel)
	{
		//���f���ԍ���modekList�̃C���f�b�N�X
		modelList[hModel]->pFbx_->Draw(modelList[hModel]->transfome_);
	}

	void Model::Release()
	{
		bool isReffered = false;
		for (int i = 0; i < modelList.size(); i++)
		{
			for (int j = i + 1; j < modelList.size(); j++)
			{
				if (modelList[i]->pFbx_ == modelList[j]->pFbx_)
				{
					isReffered = true;
					break;
				}
			}
			if (isReffered == false)
			{
				SAFE_DELETE(modelList[i]->pFbx_);
			}
			SAFE_DELETE(modelList[i]);
		}
		modelList.clear();
	}

	void Model::RayCast(int hModel_, RayCastData& rayData)
	{
		modelList[hModel_]->transfome_.Calclation();
		//�@���[���h�s��̋t�s��
		XMMATRIX wInv = XMMatrixInverse(nullptr, modelList[hModel_]->transfome_.GetWorldMatrix());
		//�A���C�̒ʉߓ_�����߂�
		XMVECTOR vpass{ rayData.start.x + rayData.dir.x,
					    rayData.start.y + rayData.dir.y,
					    rayData.start.z + rayData.dir.z,
					    rayData.start.w + rayData.dir.w };
		//�BrayData.start�����f����Ԃɕϊ�
		XMVECTOR vstart = XMLoadFloat4(&rayData.start);
		vstart = XMVector3TransformCoord(vstart,wInv);
		XMStoreFloat4(&rayData.start, vstart);
		//�C(�n�_��������x�N�g����L�΂�����)�ʉߓ_(�A)�ɇ@��������
		vpass = XMVector3TransformCoord(vpass, wInv);
		//�DrayData.dir���B����C�Ɍ������x�N�g��
		vpass = vpass - vstart;
		XMStoreFloat4(&rayData.dir, vpass);
	

		//�w�肳�ꂽ���f���ԍ���FBX�Ƀ��C�L���X�g
		modelList[hModel_]->pFbx_->RayCast(rayData);
	}

