//==============================
//
//  アイテム欄処理[ItemUI.cpp]
//  Author:kaiti
//
//==============================
#include "item.h"
#include "itemui.h"
#include "player.h"

//グローバル変数
//枠
LPDIRECT3DTEXTURE9 g_pTextureItemUIframe = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUIframe = NULL;

//アイテム名
LPDIRECT3DTEXTURE9 g_pTextureItemUI[NUM_ITEMTYPE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUI = NULL;

//数字
LPDIRECT3DTEXTURE9 g_pTextureItemUINo = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUINo = NULL;

D3DXVECTOR3 g_ItemUIframepos;
D3DXVECTOR3 g_ItemUIpos;
D3DXVECTOR3 g_ItemUINopos;

int g_nCntItemHP;
int g_nCntItemMP;
int g_nCntItemSpeed;

//=============
// 初期化処理
//=============
void InitItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UIfram.jpg", &g_pTextureItemUIframe);	//枠
	
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemUI2.png", &g_pTextureItemUI[0]);		//HP 
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemUI1.png", &g_pTextureItemUI[1]);		//MP 
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\itemUI3.png", &g_pTextureItemUI[2]);		//AT 

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number002.png", &g_pTextureItemUINo);		//No 

	g_ItemUIframepos = D3DXVECTOR3(975.0f, 470.0f, 0.0f);
	g_ItemUIpos = D3DXVECTOR3(990.0f, 490.0f, 0.0f);
	g_ItemUINopos = D3DXVECTOR3(ITEMUI_X + 990.0f, 490.0f, 0.0f);

	g_nCntItemHP = 0;
	g_nCntItemMP = 0;
	g_nCntItemSpeed = 0;

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;

	//枠
	{		
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItemUIframe,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffItemUIframe->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_ItemUIframepos.x, g_ItemUIframepos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ItemUIframepos.x + ITEMUIFRAME_X, g_ItemUIframepos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ItemUIframepos.x, g_ItemUIframepos.y + ITEMUIFRAME_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ItemUIframepos.x + ITEMUIFRAME_X, g_ItemUIframepos.y + ITEMUIFRAME_Y, 0.0f);
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
		g_pVtxBuffItemUIframe->Unlock();
	}

	//アイテム
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ITEMTYPE,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItemUI,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < NUM_ITEMTYPE; nCnt++)
		{
			//アイテム欄
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_ItemUIpos.x, g_ItemUIpos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUIpos.x + ITEMUI_X, g_ItemUIpos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUIpos.x, g_ItemUIpos.y + ITEMUI_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUIpos.x + ITEMUI_X, g_ItemUIpos.y + ITEMUI_Y, 0.0f);
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
			g_ItemUIpos.y += ITEMUI_Y + 20.0f;
		}
		//頂点バッファをアンロック
		g_pVtxBuffItemUI->Unlock();
	}

	//数字
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ITEMTYPE * MAX_ITEMGET,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItemUINo,
			NULL);
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffItemUINo->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < NUM_ITEMTYPE * MAX_ITEMGET; nCnt++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_ItemUINopos.x, g_ItemUINopos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemUINopos.x + ITEMUINO_SIZE, g_ItemUINopos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemUINopos.x, g_ItemUINopos.y + ITEMUINO_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemUINopos.x + ITEMUINO_SIZE, g_ItemUINopos.y + ITEMUINO_SIZE, 0.0f);
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

			g_ItemUINopos.x += ITEMUINO_SIZE;

			if (nCnt == MAX_ITEMGET - 1 || nCnt == MAX_ITEMGET * 2 - 1 || nCnt == MAX_ITEMGET * 3 - 1)
			{
				g_ItemUINopos.y += ITEMUI_Y + 20.0f;
				g_ItemUINopos.x = ITEMUI_X + 990.0f;
			}
		}
		//頂点バッファをアンロック
		g_pVtxBuffItemUINo->Unlock();
	}
}
//==========
// 終了処理
//==========
void UninitItemUI(void)
{
	//テクスチャの破棄
	if (g_pTextureItemUIframe != NULL && g_pTextureItemUINo != NULL)
	{
		g_pTextureItemUIframe->Release();
		g_pTextureItemUIframe = NULL;
		g_pTextureItemUINo->Release();
		g_pTextureItemUINo = NULL;

	}
	for (int nCnt = 0; nCnt < NUM_ITEMTYPE; nCnt++)
	{
		if (g_pTextureItemUI[nCnt] != NULL)
		{
			g_pTextureItemUI[nCnt]->Release();
			g_pTextureItemUI[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItemUIframe != NULL && g_pVtxBuffItemUI != NULL && g_pVtxBuffItemUINo != NULL)
	{
		g_pVtxBuffItemUIframe->Release();
		g_pVtxBuffItemUIframe = NULL;
		g_pVtxBuffItemUI->Release();
		g_pVtxBuffItemUI = NULL;
		g_pVtxBuffItemUINo->Release();
		g_pVtxBuffItemUINo = NULL;

	}
}
//==========
// 更新処理
//==========
void UpdateItemUI(void)
{

}
//===========
// 描画処理
//===========
void DrawItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//枠
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffItemUIframe, 0, sizeof(VERTEX_2D));
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureItemUIframe);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//アイテム欄
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffItemUI, 0, sizeof(VERTEX_2D));
		for (int nCnt = 0; nCnt < NUM_ITEMTYPE; nCnt++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItemUI[nCnt]);
			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//数字
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffItemUINo, 0, sizeof(VERTEX_2D));
		for (int nCnt = 0; nCnt < NUM_ITEMTYPE * MAX_ITEMGET; nCnt++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItemUINo);
			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

}
//=================
// アイテムUI設定
//=================
void SetItemUI(void)
{

}
//==================
// アイテム数加算
//==================
void AddItemUI(ITEMTYPE type)
{
	int aPosTexU[MAX_ITEMGET];
	int nItemType = 0;
	if (type == ITEMTYPE_HP)
	{
		g_nCntItemHP++;
		nItemType = g_nCntItemHP;
	}
	else if (type == ITEMTYPE_MP)
	{
		g_nCntItemMP++;
		nItemType = g_nCntItemMP;

	}
	else if (type == ITEMTYPE_SPEED)
	{
		g_nCntItemSpeed++;
		nItemType = g_nCntItemSpeed;
	}

	int nData = 100;
	int nData2 = 10;
	int nCnt;

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItemUINo->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * type * 2;

	for (nCnt = 0; nCnt < MAX_ITEMGET; nCnt++)
	{
		aPosTexU[nCnt] = (nItemType % nData) / nData2;
		nData /= 10;
		nData2 /= 10;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] * 0.1f) + 0.1f, 1.0f);
		
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffItemUINo->Unlock();
}