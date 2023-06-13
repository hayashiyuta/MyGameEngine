#include "Dice.h"
#include "Camera.h"

Dice::Dice() :pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr)
{
}

Dice::~Dice()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

HRESULT Dice::Initialize()
{
	// 頂点情報
	VERTEX vertices[] =
	{
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（左上）(正面) 0
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（右上）1
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（右下）2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（左下）	3 1の面

		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },   //四角形の頂点（左上）(左面) 4
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },   //四角形の頂点（左下）(左面) 5
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（左上）(正面) 6(0)
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（左下）	7(3) 2の面

		{XMVectorSet(1.0f,  1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（右上）(右面)8(6)
		{XMVectorSet(1.0f,  -1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（右下）(右面)9(7)
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（右上）10(1)
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（右下）11(2) 3の面

		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（左上）(正面) 12(0)
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（右上）13(1)
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f) },   //四角形の頂点（左上）(左面) 14(4)
		{XMVectorSet(1.0f,  1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（右上）(右面)15(6) 4の面

		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（右下）16(2)
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（左下）	17(3)
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },   //四角形の頂点（左下）(左面) 18(5)
		{XMVectorSet(1.0f,  -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },	// 四角形の頂点（右下）(右面) 19(7) 5の面

		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),  XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },   //四角形の頂点（左上）(左面) 20(4)
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f) },   //四角形の頂点（左下）(左面) 21(5)
		{XMVectorSet(1.0f,  1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（右上）(右面) 22(6)
		{XMVectorSet(1.0f,  -1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },	// 四角形の頂点（右下）(右面) 23(7) 6の面

		//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	// 四角形の頂点
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	//インデックス情報    1              2               3                   4                   5                    6
	int index[] = { 0,2,3, 0,1,2,  6,7,4, 4,7,5,  10,8,11, 8,9,11,  12,14,13, 13,14,15,  16,19,17, 19,18,17,  20,21,22, 21,23,22 };
	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;

	}
	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;

	}

	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");

	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	//コンスタントバッファに渡す情報
	/*XMVECTOR position = {0, 3, -10, 0};	//カメラの位置
	XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列
	*/
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);



	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext_->DrawIndexed(36, 0, 0);
}

void Dice::Release()
{
	SAFE_DELETE(pTexture_);
	SAFE_RELEASE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);

	//pConstantBuffer_->Release();
	//pIndexBuffer_->Release();
	//pVertexBuffer_->Release();
}