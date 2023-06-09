#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Dice
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファのアドレスを入れる
	//メンバ変数を作ったらコンストラクタで初期化
	ID3D11Buffer* pIndexBuffer_;//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;

public:
	Dice();
	~Dice();
	//void
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();

};



