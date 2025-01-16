//==============================
//
//  タイマー処理[Timer.cpp]
//  Author:kaiti
//
//==============================
#include "timer.h"
#include "player.h"
#include "result.h"
#include "fade.h"
#include "game.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;
D3DXVECTOR3 g_posTimer;
int g_nTimer = 0;
int g_nSeconds = 0;
//=============
//初期化処理
//=============
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number003.png", &g_pTextureTimer); //1

	g_posTimer = D3DXVECTOR3(550.0f,0.0f,0.0f);
	g_nTimer = 0;

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffTimer,
		                        NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTimer.x + (50 * nCnt), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTimer.x + (50 * (nCnt + 1)), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTimer.x + (50 * nCnt), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTimer.x + (50 * (nCnt + 1)), 100.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTimer->Unlock();
}
//==========
//終了処理
//==========
void UninitTimer(void)
{
	//テクスチャの破棄
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}
//==========
//更新処理
//==========
void UpdateTimer(void)
{
	GAMESTATE gamestate = GetGameSatate();

	g_nSeconds++;
	//一秒経過
	if (g_nSeconds >= 60)
	{
		AddTimer(1);
		g_nSeconds = 0;
	}
	
	//タイマーが０になった
	if (g_nTimer <= 0)
	{	
		if (gamestate == GAMESTATE_NORMAL)
		{
			SetGameState(GAMESTATE_TIMEOVER);
		}		
		
		g_nTimer = 0;
	}

}
//===========
//描画処理
//===========
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));
	
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTimer);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
//=================
//タイマーの設定
//=================
void SetTimer(int nTimer)
{
	int aPosTexU[MAX_TIMER]; //桁数分
	g_nTimer += nTimer;

	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		aPosTexU[nCnt] = (g_nTimer % nData) / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTimer->Unlock();
}
//==================
//タイマーの加算処理
//==================
void AddTimer(int nValue)
{
	int aPosTexU[MAX_TIMER];
	g_nTimer -= nValue;
	if (g_nTimer <= 0)
	{
		g_nTimer = 0;
	}
	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		aPosTexU[nCnt] = (g_nTimer % nData) / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
 	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTimer->Unlock();
}
//==============
//タイマーの取得
//==============
int GetTimer(void)
{
	return g_nTimer;
}