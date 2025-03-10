//==============================
//
//  ゲージ処理[Gauge.cpp]
//  Author:kaiti
//
//==============================
#include "gauge.h"
#include "player.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureGaugeBack[GAUGETYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGaugeBack = NULL;

LPDIRECT3DTEXTURE9 g_pTextureGauge = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;

Gauge g_gauge[GAUGETYPE_MAX];
//=============
// 初期化処理
//=============
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		g_gauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_gauge[nCnt].type = GAUGETYPE_HP;
		g_gauge[nCnt].size = D3DXVECTOR2(100.0f, 50.0f);
		g_gauge[nCnt].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\hpgauge.png", &g_pTextureGaugeBack[GAUGETYPE_HP]);	//HP 枠
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mpgauge.png", &g_pTextureGaugeBack[GAUGETYPE_MP]);	//MP 枠
	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge00.jpeg", &g_pTextureGauge);	//

	//ゲージ
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGETYPE_MAX,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffGauge,
		                        NULL);
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		if (nCnt == GAUGETYPE_HP)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(1, 255, 127, 255);
			pVtx[1].col = D3DCOLOR_RGBA(1, 255, 127, 255);
			pVtx[2].col = D3DCOLOR_RGBA(1, 255, 127, 255);
			pVtx[3].col = D3DCOLOR_RGBA(1, 255, 127, 255);
		}
		if (nCnt == GAUGETYPE_MP)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(1, 127, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(1, 127, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(1, 127, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffGauge->Unlock();


	//枠
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGETYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGaugeBack,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGaugeBack->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffGaugeBack->Unlock();

}
//==========
// 終了処理
//==========
void UninitGauge(void)
{
	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureGauge != NULL)
		{
			g_pTextureGauge->Release();
			g_pTextureGauge = NULL;
		}
		//テクスチャの破棄
		if (g_pTextureGaugeBack[nCnt] != NULL)
		{
			g_pTextureGaugeBack[nCnt]->Release();
			g_pTextureGaugeBack[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
	if (g_pVtxBuffGaugeBack != NULL)
	{
		g_pVtxBuffGaugeBack->Release();
		g_pVtxBuffGaugeBack = NULL;
	}
}
//==========
// 更新処理
//==========
void UpdateGauge(void)
{
	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		if (g_gauge[nCnt].bUse == true)
		{
			if (g_gauge[nCnt].type == GAUGETYPE_HP)
			{
				g_gauge[nCnt].size.x = pPlayer->Status.fHP / 2.85f;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);

				if (pPlayer->Status.fHP <= PLAYER_HP / 5)
				{//赤
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 1, 1, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 1, 1, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 1, 1, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 1, 1, 255);
				}
				else if (pPlayer->Status.fHP <= PLAYER_HP / 1.5)
				{//黄色
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 1, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 1, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 1, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 1, 255);
				}
				else
				{
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(1, 255, 127, 255);
					pVtx[1].col = D3DCOLOR_RGBA(1, 255, 127, 255);
					pVtx[2].col = D3DCOLOR_RGBA(1, 255, 127, 255);
					pVtx[3].col = D3DCOLOR_RGBA(1, 255, 127, 255);
				}
			}
			else if (g_gauge[nCnt].type == GAUGETYPE_MP)
			{
				g_gauge[nCnt].size.x = pPlayer->Status.nMP / 1.65f;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffGauge->Unlock();
}
//===========
// 描画処理
//===========
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ゲージ
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));
	
	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		if (g_gauge[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureGauge);
			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//枠
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGaugeBack, 0, sizeof(VERTEX_2D));
	
	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		if (g_gauge[nCnt].bUse == true)
		{
			//テクスチャの設定
			if (g_gauge[nCnt].type == GAUGETYPE_HP)
			{
				pDevice->SetTexture(0, g_pTextureGaugeBack[GAUGETYPE_HP]);
			}
			else if (g_gauge[nCnt].type == GAUGETYPE_MP)
			{
				pDevice->SetTexture(0, g_pTextureGaugeBack[GAUGETYPE_MP]);
			}
			pDevice->SetTexture(0, g_pTextureGaugeBack[nCnt]);
			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//==================
// ゲージの設定
//==================
void SetGauge(GAUGETYPE type, D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGaugeBack->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
	{
		if (g_gauge[nCnt].bUse == false)
		{
			VERTEX_2D* pVtx1;
			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx1, 0);

			g_gauge[nCnt].type = type;
			g_gauge[nCnt].pos = pos;

			if (g_gauge[nCnt].type == GAUGETYPE_HP)
			{
				g_gauge[nCnt].size = D3DXVECTOR2(size.x + PLAYER_HP / 10, size.y);
				//頂点座標の設定
				pVtx1[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx1[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx1[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
				pVtx1[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
			}
			else if (g_gauge[nCnt].type == GAUGETYPE_MP)
			{
				pVtx1 += 4;
				g_gauge[nCnt].size = D3DXVECTOR2(size.x + PLAYER_MP / 10, size.y);
				//頂点座標の設定
				pVtx1[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx1[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
				pVtx1[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
				pVtx1[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
			}
			g_gauge[nCnt].bUse = true;

			//頂点バッファをアンロック
			g_pVtxBuffGauge->Unlock();

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);

			//サイズ調整
			g_gauge[nCnt].pos.x += 45.f;
			g_gauge[nCnt].size.y -= 5.0f;

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffGaugeBack->Unlock();
}