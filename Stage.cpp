#include "Stage.h"
#include "Engine/Model.h"
#include"resource.h"
//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),mode_(0),select_(0)
{
	for (int i = 0; i < MODEL_NUM; i++)
	{
		hModel_[i] = -1;
	}
	//�e�[�u����������
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			SetBlock(x, z, DEFAULT);
			table_[x][z].HEGHT = 1;
		}
	}
}

//������
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
	//���f���f�[�^�̃��[�h
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

//�X�V
void Stage::Update()
{
}

//�`��
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

//�J��
void Stage::Release()
{
}

//�U��(����������������TRUE�A�������Ȃ�������FALSE��Ԃ�)
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		//�_�C�A���O�ł���
	case WM_INITDIALOG:
		//���W�I�{�^���̏����l
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP),BM_SETCHECK,BST_CHECKED,0);
		//�R���{�{�^���̏����l
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"�f�t�H���g");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"�����K");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"�y");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"��");

		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);

		return TRUE;
	case WM_COMMAND:
		mode_ = LOWORD(wp) - IDC_RADIO_UP;
		select_ = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
	}
	return FALSE;
	//LOWORD(wp)
}