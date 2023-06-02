#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};


class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファのアドレスを入れる
	//メンバ変数を作ったらコンストラクタで初期化
	ID3D11Buffer* pIndexBuffer_;//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ


public:
	Quad();
	~Quad();
	//void
	HRESULT Initialize();
	void Draw();
	void Release();

};

