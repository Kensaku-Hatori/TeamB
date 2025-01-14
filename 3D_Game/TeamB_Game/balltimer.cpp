//==============================
//
//  タイマー処理[BallTimer.cpp]
//  Author:kaiti
//
//==============================
#include "balltimer.h"
#include "player.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBallTimer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallTimer = NULL;
D3DXVECTOR3 g_posBallTimer;
int g_nBallTimer = 0;
bool g_bPuls;
//=============
// 初期化処理
//=============
void InitBallTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number003.png", &g_pTextureBallTimer); //1

	g_posBallTimer = D3DXVECTOR3(30.0f, BALLTIMER_Y,0.0f);
	g_nBallTimer = 0;
	g_bPuls = false;

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BALLTIMER,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBallTimer,
		                        NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallTimer->Lock(0, 0, (void**)&pVtx, 0);
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posBallTimer.x + (50 * nCnt), g_posBallTimer.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posBallTimer.x + (50 * (nCnt + 1)), g_posBallTimer.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posBallTimer.x + (50 * nCnt), g_posBallTimer.y + 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posBallTimer.x + (50 * (nCnt + 1)), g_posBallTimer.y + 100.0f, 0.0f);
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

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBallTimer->Unlock();
}
//==========
// 終了処理
//==========
void UninitBallTimer(void)
{
	//テクスチャの破棄
	if (g_pTextureBallTimer != NULL)
	{
		g_pTextureBallTimer->Release();
		g_pTextureBallTimer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBallTimer != NULL)
	{
		g_pVtxBuffBallTimer->Release();
		g_pVtxBuffBallTimer = NULL;
	}
}
//==========
// 更新処理
//==========
void UpdateBallTimer(void)
{
	Player* pPlayer = GetPlayer();

	if (pPlayer->type == PLAYERTYPE_BALL || pPlayer->type == PLAYERTYPE_SUPERBALL)
	{
		if (g_nBallTimer > 0)
		{//タイマーが０より大きい場合
			AddBallTimer(-1);
		}
	}
	if (pPlayer->type == PLAYERTYPE_HITO)
	{//プレイヤーが人の時
		if (g_nBallTimer < MAX_BALLTIME && g_bPuls == true)
		{//タイマーが最大より小さい場合
			AddBallTimer(1);
		}
		else if (g_nBallTimer >= MAX_BALLTIME)
		{//タイマーが最大値までいったら
			g_nBallTimer = MAX_BALLTIME;
			g_bPuls = false;
			if (pPlayer->bBall == false)
			{
				pPlayer->bBall = true;
			}
		}
	}
	if (g_nBallTimer <= 0 && g_bPuls == false)
	{
		g_bPuls = true;
	}
	pPlayer->nBallTime = g_nBallTimer;
}
//===========
// 描画処理
//===========
void DrawBallTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBallTimer, 0, sizeof(VERTEX_2D));
	
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BALLTIME; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBallTimer);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
//=================
// タイマーの設定
//=================
void SetBallTimer(int nBallTimer)
{
	int aPosTexU[MAX_BALLTIMER]; //桁数分
	g_nBallTimer += nBallTimer;

	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		aPosTexU[nCnt] = (g_nBallTimer % nData) / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallTimer->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBallTimer->Unlock();
}
//==================
// タイマーの加算処理
//==================
void AddBallTimer(int nValue)
{
	int aPosTexU[MAX_BALLTIMER];
	g_nBallTimer += nValue;
	if (g_nBallTimer <= 0)
	{
		g_nBallTimer = 0;
	}
	int nData = 1000;
	int nData2 = 100;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		aPosTexU[nCnt] = (g_nBallTimer % nData) / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
 	g_pVtxBuffBallTimer->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_BALLTIMER; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBallTimer->Unlock();
}
//==============
// タイマーの取得
//==============
int GetBallTimer(void)
{
	return g_nBallTimer;
}