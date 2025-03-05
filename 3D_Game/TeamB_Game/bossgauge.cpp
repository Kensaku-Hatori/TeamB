//==============================
//
//  ゲージ処理[BossGauge.cpp]
//  Author:kaiti
//
//==============================
#include "BossGauge.h"
#include "player.h"
#include "boss.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBossGaugeBack = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossGaugeBack = NULL;

LPDIRECT3DTEXTURE9 g_pTextureBossGauge = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossGauge = NULL;

LPDIRECT3DTEXTURE9 g_pTextureBossName = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossName = NULL;

D3DXVECTOR3 g_BossGauge;
D3DXVECTOR3 g_BossGaugeSize;
D3DXVECTOR3 g_BossName;

//=============
// 初期化処理
//=============
void InitBossGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossgage.png", &g_pTextureBossGaugeBack);	//HP 枠	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GUAGE.png", &g_pTextureBossGauge);	//
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossname.png", &g_pTextureBossName);	//

	g_BossGauge = D3DXVECTOR3(SCREEN_WIDTH / 6, SCREEN_HEIGHT - 100.0f, 0.0f);
	g_BossGaugeSize = D3DXVECTOR3(BOSSGAUGE_FRAME_X, BOSSGAUGE_FRAME_Y, 0.0f);
	g_BossName = D3DXVECTOR3(SCREEN_WIDTH / 6, SCREEN_HEIGHT - 150.0f, 0.0f);

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;

	//ゲージ
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBossGauge,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBossGauge->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_BossGauge.x, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_BossGauge.x, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(1, 127, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffBossGauge->Unlock();
	}

	//枠
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBossGaugeBack,
			NULL);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBossGaugeBack->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_BossGauge.x + 10.0f, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x - 15.0f, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_BossGauge.x + 10.0f, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x - 15.0f, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
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

		//頂点バッファをアンロック
		g_pVtxBuffBossGaugeBack->Unlock();
	}

	//名前
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBossName,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBossName->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_BossName.x - BOSSNAME_X, g_BossName.y - BOSSNAME_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_BossName.x + BOSSNAME_X, g_BossName.y - BOSSNAME_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_BossName.x - BOSSNAME_X, g_BossName.y + BOSSNAME_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_BossName.x + BOSSNAME_X, g_BossName.y + BOSSNAME_Y, 0.0f);
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

	//頂点バッファをアンロック
	g_pVtxBuffBossName->Unlock();

}
//==========
// 終了処理
//==========
void UninitBossGauge(void)
{
	//テクスチャの破棄
	if (g_pTextureBossGauge != NULL && g_pTextureBossGaugeBack != NULL && g_pTextureBossName != NULL)
	{
		g_pTextureBossGauge->Release();
		g_pTextureBossGauge = NULL;
		g_pTextureBossGaugeBack->Release();
		g_pTextureBossGaugeBack = NULL;
		g_pTextureBossName->Release();
		g_pTextureBossName = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBossGauge != NULL && g_pVtxBuffBossGaugeBack != NULL && g_pVtxBuffBossName != NULL)
	{
		g_pVtxBuffBossGauge->Release();
		g_pVtxBuffBossGauge = NULL;
		g_pVtxBuffBossGaugeBack->Release();
		g_pVtxBuffBossGaugeBack = NULL;
		g_pVtxBuffBossName->Release();
		g_pVtxBuffBossName = NULL;
	}
}
//==========
// 更新処理
//==========
void UpdateBossGauge(void)
{
	BOSS* pBoss = GetBoss();

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBossGauge->Lock(0, 0, (void**)&pVtx, 0);
	g_BossGaugeSize.x = pBoss->Status.fHP / BOSSGAUGE_DIVISION;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_BossGauge.x, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x, g_BossGauge.y - g_BossGaugeSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_BossGauge.x, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_BossGauge.x + g_BossGaugeSize.x, g_BossGauge.y + g_BossGaugeSize.y, 0.0f);

	if (pBoss->Status.fHP <= BOSS_HP / 5)
	{//赤
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 1, 1, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 1, 1, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 1, 1, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 1, 1, 255);
	}
	else if (pBoss->Status.fHP <= BOSS_HP / 1.5)
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
		
	//頂点バッファをアンロック
	g_pVtxBuffBossGauge->Unlock();
}
//===========
// 描画処理
//===========
void DrawBossGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ゲージ
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBossGauge, 0, sizeof(VERTEX_2D));
	
	pDevice->SetTexture(0, g_pTextureBossGauge);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	//枠
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBossGaugeBack, 0, sizeof(VERTEX_2D));
	
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBossGaugeBack);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//名前
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBossName, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, g_pTextureBossName);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}