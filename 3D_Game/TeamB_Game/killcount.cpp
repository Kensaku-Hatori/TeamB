//==============================
//
//  スコア処理[KillCount.cpp]
//  Author:kaiti
//
//==============================
#include "killcount.h"
#include "player.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureKillCount = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKillCount = NULL;
LPDIRECT3DTEXTURE9 g_pTextureStrike = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStrike = NULL;

D3DXVECTOR3 g_posKillCount;
int g_nKillCount;
//=============
// 初期化処理
//=============
void InitKillCount(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number003.png", &g_pTextureKillCount); //1
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\strike00.png", &g_pTextureStrike); //1

	g_posKillCount = D3DXVECTOR3(50.0f,0.0f,0.0f);
	g_nKillCount = 0;

	//数値
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_KILLCOUNTER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffKillCount,
		NULL);

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKillCount->Lock(0, 0, (void**)&pVtx, 0);
	
	int nCnt,nData=0;
	for (nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posKillCount.x + (50 * nData), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posKillCount.x + (50 * (nData + 1)), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posKillCount.x + (50 * nData), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posKillCount.x + (50 * (nData + 1)), 100.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		nData++;
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffKillCount->Unlock();

	//ストライク
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStrike,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStrike->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(500.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(50.0f, 300.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(500.0f, 300.0f, 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffStrike->Unlock();
}
//===========
// 終了処理
//===========
void UninitKillCount(void)
{
	//テクスチャの破棄
	if (g_pTextureKillCount != NULL && g_pTextureStrike != NULL)
	{
		g_pTextureKillCount->Release();
		g_pTextureKillCount = NULL;
		g_pTextureStrike->Release();
		g_pTextureStrike = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffKillCount != NULL && g_pVtxBuffStrike != NULL)
	{
		g_pVtxBuffKillCount->Release();
		g_pVtxBuffKillCount = NULL;
		g_pVtxBuffStrike->Release();
		g_pVtxBuffStrike = NULL;
	}
}
//===========
// 更新処理
//===========
void UpdateKillCount(void)
{
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStrike->Lock(0, 0, (void**)&pVtx, 0);

	Player* pPlayer = GetPlayer();
	if (pPlayer->nCntPin >= PIN_CONDITION)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	}

	//if (g_nKillCount == PIN_CONDITION)
	//{
	//	SetKillCount(0);
	//}

	//頂点バッファをアンロック
	g_pVtxBuffStrike->Unlock();
}
//===========
// 描画処理
//===========
void DrawKillCount(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffKillCount, 0, sizeof(VERTEX_2D));
	
	for (int nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureKillCount);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStrike, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureStrike);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//================
// スコアの設定
//================
void SetKillCount(int nKillCount)
{
	int aPosTexU[MAX_KILLCOUNTER]; //桁数分	
	g_nKillCount = nKillCount;
	if (g_nKillCount <= 0)
	{
		g_nKillCount = 0;
	}

	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		aPosTexU[nCnt] = g_nKillCount % nData / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKillCount->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt <  MAX_KILLCOUNTER; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffKillCount->Unlock();
}
//===================
// スコアの加算処理
//===================
void AddKillCount(int nValue)
{
	int aPosTexU[MAX_KILLCOUNTER];
	g_nKillCount += nValue;
	if (g_nKillCount <= 0)
	{
		g_nKillCount = 0;
	}

	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		aPosTexU[nCnt] = g_nKillCount % nData / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKillCount->Lock(0, 0, (void**)&pVtx, 0);
	int nData3 = 0;
	for (nCnt = 0; nCnt < MAX_KILLCOUNTER; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nData3] / 10.0f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nData3] / 10.0f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nData3] / 10.0f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nData3] / 10.0f) + 0.1f, 1.0f);

		nData3++;
		pVtx += 4;;
	}
	//頂点バッファをアンロック
	g_pVtxBuffKillCount->Unlock();
}
//==============
// スコアの取得
//==============
int GetKillCount(void)
{
	return g_nKillCount;
}