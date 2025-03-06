//==============================
//
//  ミニマップ処理[ButtonUi.cpp]
//  Author:kaiti
//
//==============================
#include "ButtonUi.h"
#include "player.h"
//グローバル変数
//ミッション
LPDIRECT3DTEXTURE9 g_pTextureButtonUi[BUTTONUI_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffButtonUi = NULL;

ButtonUi g_ButtonUi[MAX_BUTTONUI];

//=============
// 初期化処理
//=============
void InitButtonUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ENTERkey.png", &g_pTextureButtonUi[BUTTONUI_WHEEL]);	//枠
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ESCkey.png", &g_pTextureButtonUi[BUTTONUI_SAYU]);	//枠

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BUTTONUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffButtonUi,
		NULL);
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffButtonUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		g_ButtonUi[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ButtonUi[nCnt].size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		g_ButtonUi[nCnt].ButtonUi = BUTTONUI_WHEEL;
		g_ButtonUi[nCnt].bUse = false;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x - g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y - g_ButtonUi[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x + g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y - g_ButtonUi[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x - g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y + g_ButtonUi[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x + g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y + g_ButtonUi[nCnt].size.y, 0.0f);
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
	}
	//頂点バッファをアンロック
	g_pVtxBuffButtonUi->Unlock();
}
//==========
// 終了処理
//==========
void UninitButtonUi(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_pTextureButtonUi[nCnt] != NULL)
		{
			g_pTextureButtonUi[nCnt]->Release();
			g_pTextureButtonUi[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffButtonUi != NULL)
	{
		g_pVtxBuffButtonUi->Release();
		g_pVtxBuffButtonUi = NULL;
	}
}
//==========
// 更新処理
//==========
void UpdateButtonUi(void)
{
}
//===========
// 描画処理
//===========
void DrawButtonUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//枠
	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUi[nCnt].bUse == true)
		{
			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffButtonUi, 0, sizeof(VERTEX_2D));
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureButtonUi[g_ButtonUi[nCnt].ButtonUi]);
			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//===========
// UIの設定
//===========
void SetButtonUi(BUTTONUI type, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffButtonUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUi[nCnt].bUse == false)
		{
			g_ButtonUi[nCnt].pos = pos;
			g_ButtonUi[nCnt].size = size;
			g_ButtonUi[nCnt].ButtonUi = type;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x - g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y - g_ButtonUi[nCnt].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x + g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y - g_ButtonUi[nCnt].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x - g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y + g_ButtonUi[nCnt].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ButtonUi[nCnt].pos.x + g_ButtonUi[nCnt].size.x, g_ButtonUi[nCnt].pos.y + g_ButtonUi[nCnt].size.y, 0.0f);
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


			g_ButtonUi[nCnt].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffButtonUi->Unlock();
}