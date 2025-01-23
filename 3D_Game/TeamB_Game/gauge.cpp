////==============================
////
////  タイマー処理[Gauge.cpp]
////  Author:kaiti
////
////==============================
//#include "gauge.h"
//#include "player.h"
////グローバル変数
//LPDIRECT3DTEXTURE9 g_pTextureGaugeBack = NULL;
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGaugeBack = NULL;
//
//LPDIRECT3DTEXTURE9 g_pTextureGauge[GAUGETYPE_MAX] = {};
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;
//
//Gauge g_gauge[GAUGETYPE_MAX];
////=============
//// 初期化処理
////=============
//void InitGauge(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	//デバイスの取得
//	pDevice = GetDevice();
//
//
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		g_gauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_gauge[nCnt].type = GAUGETYPE_HP;
//		g_gauge[nCnt].size = D3DXVECTOR2(100.0f, 50.0f);
//		g_gauge[nCnt].bUse = false;
//	}
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.png", &g_pTextureGaugeBack);	//枠
//
//	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.png", &g_pTextureGauge[GAUGETYPE_HP]);	//HP
//	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge02.jpeg", &g_pTextureGauge[GAUGETYPE_MP]); //MP
//	
//	//ゲージ
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGETYPE_MAX,
//		                        D3DUSAGE_WRITEONLY,
//		                        FVF_VERTEX_2D,
//		                        D3DPOOL_MANAGED,
//		                        &g_pVtxBuffGauge,
//		                        NULL);
//	//頂点バッファの生成・頂点情報の設定
//	VERTEX_2D* pVtx;
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		//頂点座標の設定
//		pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		//rhwの設定
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//		//頂点カラーの設定
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//		
//		pVtx += 4;
//	}
//	//頂点バッファをアンロック
//	g_pVtxBuffGauge->Unlock();
//
//
//	//枠
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGETYPE_MAX,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffGauge,
//		NULL);
//	//頂点バッファの生成・頂点情報の設定
//	VERTEX_2D* pVtx;
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		//頂点座標の設定
//		pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		//rhwの設定
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//		//頂点カラーの設定
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//	//頂点バッファをアンロック
//	g_pVtxBuffGauge->Unlock();
//
//}
////==========
//// 終了処理
////==========
//void UninitGauge(void)
//{
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		//テクスチャの破棄
//		if (g_pTextureGauge[nCnt] != NULL)
//		{
//			g_pTextureGauge[nCnt]->Release();
//			g_pTextureGauge[nCnt] = NULL;
//		}
//	}
//	//頂点バッファの破棄
//	if (g_pVtxBuffGauge != NULL)
//	{
//		g_pVtxBuffGauge->Release();
//		g_pVtxBuffGauge = NULL;
//	}
//}
////==========
//// 更新処理
////==========
//void UpdateGauge(void)
//{
//	Player* pPlayer = GetPlayer();
//
//	VERTEX_2D* pVtx;
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		//頂点座標の設定
//		pVtx[0].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y - g_gauge[nCnt].size.y, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_gauge[nCnt].pos.x + g_gauge[nCnt].size.x, g_gauge[nCnt].pos.y + g_gauge[nCnt].size.y, 0.0f);
//	}
//	//頂点バッファをアンロック
//	g_pVtxBuffGauge->Unlock();
//}
////===========
//// 描画処理
////===========
//void DrawGauge(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));
//	
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		if (g_gauge[nCnt].bUse == true)
//		{
//			//テクスチャの設定
//			pDevice->SetTexture(0, g_pTextureGauge[nCnt]);
//			//プレイヤーの描画
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
//		}
//	}
//}
////==================
//// ゲージの設定
////==================
//void SetGauge(GAUGETYPE type, D3DXVECTOR3 pos, D3DXVECTOR2 size)
//{
//	for (int nCnt = 0; nCnt < GAUGETYPE_MAX; nCnt++)
//	{
//		if (g_gauge[nCnt].bUse == false)
//		{
//			g_gauge[nCnt].type = type;
//			g_gauge[nCnt].pos = pos;
//			g_gauge[nCnt].size = size;
//			g_gauge[nCnt].bUse = true;
//		}
//	}
//}