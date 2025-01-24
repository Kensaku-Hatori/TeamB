//==============================
//
//  タイマー処理[ItemUI.cpp]
//  Author:kaiti
//
//==============================
#include "itemui.h"
#include "player.h"
//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureItemUI = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUI = NULL;

D3DXVECTOR3 g_ItemUIpos;
//=============
// 初期化処理
//=============
void InitItemUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UIfram.jpg", &g_pTextureItemUI);	//HP 枠
	
	g_ItemUIpos = D3DXVECTOR3(25.0f, 150.0f, 0.0f);

	//ゲージ
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffItemUI,
		                        NULL);
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

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
			
	//頂点バッファをアンロック
	g_pVtxBuffItemUI->Unlock();
}
//==========
// 終了処理
//==========
void UninitItemUI(void)
{
	//テクスチャの破棄
	if (g_pTextureItemUI != NULL)
	{
		g_pTextureItemUI->Release();
		g_pTextureItemUI = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItemUI != NULL)
	{
		g_pVtxBuffItemUI->Release();
		g_pVtxBuffItemUI = NULL;
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

	//ゲージ
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItemUI, 0, sizeof(VERTEX_2D));
	
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureItemUI);
	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}