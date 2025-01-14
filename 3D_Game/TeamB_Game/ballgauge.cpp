//==============================
//
//  タイマー処理[BallGauge.cpp]
//  Author:kaiti
//
//==============================
#include "ballgauge.h"
#include "player.h"
#include "balltimer.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBallGauge[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBallGauge = NULL;
D3DXVECTOR3 g_posBallGauge;

int g_nBallTime;
//=============
// 初期化処理
//=============
void InitBallGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	g_nBallTime = GetBallTimer() / 2;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.png", &g_pTextureBallGauge[0]); //1
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.jpeg", &g_pTextureBallGauge[1]); //0
	
	g_posBallGauge = D3DXVECTOR3(20.0f, BALLTIMER_Y,0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBallGauge,
		                        NULL);
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (nCnt == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_posBallGauge.x - 10.0f, g_posBallGauge.y - 75.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime + 8.0f, g_posBallGauge.y - 75.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posBallGauge.x - 10.0f, g_posBallGauge.y + GAUGE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime + 8.0f, g_posBallGauge.y + GAUGE_Y, 0.0f);
		}
		else
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_posBallGauge.x - 10.0f, g_posBallGauge.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime + 8.0f, g_posBallGauge.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posBallGauge.x - 10.0f, g_posBallGauge.y + GAUGE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime + 8.0f, g_posBallGauge.y + GAUGE_Y, 0.0f);
		}
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		if (nCnt == 0)
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
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBallGauge->Unlock();
}
//==========
// 終了処理
//==========
void UninitBallGauge(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureBallGauge[nCnt] != NULL)
		{
			g_pTextureBallGauge[nCnt]->Release();
			g_pTextureBallGauge[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBallGauge != NULL)
	{
		g_pVtxBuffBallGauge->Release();
		g_pVtxBuffBallGauge = NULL;
	}
}
//==========
// 更新処理
//==========
void UpdateBallGauge(void)
{
	Player* pPlayer = GetPlayer();

	g_nBallTime = GetBallTimer() / 2;

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBallGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posBallGauge.x, g_posBallGauge.y + 8.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime, g_posBallGauge.y + 8.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posBallGauge.x, g_posBallGauge.y + GAUGE_Y - 15.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posBallGauge.x + GAUGE_X * g_nBallTime, g_posBallGauge.y + GAUGE_Y - 15.0f, 0.0f);

	//スーパーボールの時の色
	if (pPlayer->type == PLAYERTYPE_SUPERBALL)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(200, 0, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(200, 0, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(200, 0, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(200, 0, 255, 255);
	}
	//その他
	else if (pPlayer->bBall == false)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	else
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 200, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 200, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 200, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 200, 0, 255);
	}
	//頂点バッファをアンロック
	g_pVtxBuffBallGauge->Unlock();
}
//===========
// 描画処理
//===========
void DrawBallGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBallGauge, 0, sizeof(VERTEX_2D));
	
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBallGauge[nCnt]);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}