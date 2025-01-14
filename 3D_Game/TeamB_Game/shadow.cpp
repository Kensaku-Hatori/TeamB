//================================
//
// 影表示処理[shadow.cpp]
// Author:kaiti
//
//================================
#include "shadow.h"
//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;
LPDIRECT3DTEXTURE9 g_apTextureShadow = NULL;
Shadow g_shadow[MAX_SHADOW];
//=======================
// 影の初期化処理
//=======================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		g_shadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		g_shadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\shadow000.jpg", &g_apTextureShadow); //1

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_shadow[nCnt].pos.x - 20.0f, g_shadow[nCnt].pos.y, g_shadow[nCnt].pos.z + 20.0f);
		pVtx[1].pos = D3DXVECTOR3(g_shadow[nCnt].pos.x + 20.0f, g_shadow[nCnt].pos.y, g_shadow[nCnt].pos.z + 20.0f);
		pVtx[2].pos = D3DXVECTOR3(g_shadow[nCnt].pos.x - 20.0f, g_shadow[nCnt].pos.y, g_shadow[nCnt].pos.z - 20.0f);
		pVtx[3].pos = D3DXVECTOR3(g_shadow[nCnt].pos.x + 20.0f, g_shadow[nCnt].pos.y, g_shadow[nCnt].pos.z - 20.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();
}
//====================
// 影の終了処理
//====================
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_apTextureShadow != NULL)
	{
		g_apTextureShadow->Release();
		g_apTextureShadow = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}
//=====================
// 影の更新処理
//=====================
void UpdateShadow(void)
{

}
//====================
// 影の描画処理
//====================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);


	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_shadow[nCnt].bUse == true)
		{
			//計算用マトリックス
			D3DXMATRIX mtxRot, mtxTrans;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_shadow[nCnt].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[nCnt].rot.y, g_shadow[nCnt].rot.x, g_shadow[nCnt].rot.z);
			D3DXMatrixMultiply(&g_shadow[nCnt].mtxWorld, &g_shadow[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_shadow[nCnt].pos.x, 0.1f, g_shadow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_shadow[nCnt].mtxWorld, &g_shadow[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureShadow);

			//ポリゴンを描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============
// 影の設定
//=============
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == false)
		{
			g_shadow[nCntShadow].pos = pos;
			g_shadow[nCntShadow].rot = rot;
			g_shadow[nCntShadow].bUse = true;
			break;
		}
	}
	return nCntShadow; //影の番号(index)を返す
}
//=====================
// 影の位置の更新処理
//=====================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos, bool bUse)
{
	//引数で指定された番号の影のposを設定
	g_shadow[nIdxShadow].pos = pos;
	g_shadow[nIdxShadow].bUse = bUse;
}
//
//
//
Shadow* GetShadow(void)
{
	return &g_shadow[0];
}
