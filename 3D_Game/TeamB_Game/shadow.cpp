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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		g_shadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);			//位置の初期化
		g_shadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向きの初期化
		g_shadow[nCnt].fRadius = 0.0f;								//半径の初期化
		g_shadow[nCnt].fTriangle = g_shadow[nCnt].fRadius;			//三角形の初期化

		g_shadow[nCnt].bUse = false;								//使用してしていない状態にする
	}

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\shadow000.jpg", &g_apTextureShadow); //1


	//VERTEX_3D* pVtx = NULL;

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	//{
	//	//頂点座標の設定
	//	pVtx[0].pos = D3DXVECTOR3(/*g_shadow[nCnt].pos.x*/ - g_shadow[nCnt].fRadius, g_shadow[nCnt].pos.y, /*g_shadow[nCnt].pos.z*/ + g_shadow[nCnt].fRadius);
	//	pVtx[1].pos = D3DXVECTOR3(/*g_shadow[nCnt].pos.x*/ + g_shadow[nCnt].fRadius, g_shadow[nCnt].pos.y, /*g_shadow[nCnt].pos.z*/ + g_shadow[nCnt].fRadius);
	//	pVtx[2].pos = D3DXVECTOR3(/*g_shadow[nCnt].pos.x*/ - g_shadow[nCnt].fRadius, g_shadow[nCnt].pos.y, /*g_shadow[nCnt].pos.z*/ - g_shadow[nCnt].fRadius);
	//	pVtx[3].pos = D3DXVECTOR3(/*g_shadow[nCnt].pos.x*/ + g_shadow[nCnt].fRadius, g_shadow[nCnt].pos.y, /*g_shadow[nCnt].pos.z*/ - g_shadow[nCnt].fRadius);

	//	//法線ベクトルの設定
	//	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//	//頂点カラーの設定
	//	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	//	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	//	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	//	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	pVtx += 4;
	//}
	////頂点バッファをアンロック
	//g_pVtxBuffShadow->Unlock();
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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		//使用している状態なら
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
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fRadius)
{
	int nCntShadow;
	VERTEX_3D* pVtx = NULL;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == false)
		{
			g_shadow[nCntShadow].pos = pos;											//位置
			g_shadow[nCntShadow].rot = rot;											//向き
			g_shadow[nCntShadow].fRadius = fRadius;									//半径
			//g_shadow[nCntShadow].fTriangle = g_shadow[nCntShadow].fRadius;		//三角形

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_shadow[nCntShadow].fRadius, g_shadow[nCntShadow].pos.y, +g_shadow[nCntShadow].fRadius);
			pVtx[1].pos = D3DXVECTOR3(+g_shadow[nCntShadow].fRadius, g_shadow[nCntShadow].pos.y, +g_shadow[nCntShadow].fRadius);
			pVtx[2].pos = D3DXVECTOR3(-g_shadow[nCntShadow].fRadius, g_shadow[nCntShadow].pos.y, -g_shadow[nCntShadow].fRadius);
			pVtx[3].pos = D3DXVECTOR3(+g_shadow[nCntShadow].fRadius, g_shadow[nCntShadow].pos.y, -g_shadow[nCntShadow].fRadius);

			//	//法線ベクトルの設定
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


			g_shadow[nCntShadow].bUse = true;				//使用している状態にする
			break;
		}

			pVtx += 4;

	}

	//頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();

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

//=====================
// 影のサイズの更新処理
//=====================
void SetSizeShadow(D3DXVECTOR3 pos, int nIndx, bool bjump)
{
	float posY = pos.y;//ユーザーの高さを格納
	VERTEX_3D* pVtx = NULL;

	if (bjump == true)
	{
		if (posY <= 0)
		{
			posY = 0.1f;
		}

		g_shadow[nIndx].fRadius = g_shadow[nIndx].fTriangle / (posY * 0.25f);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIndx;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_shadow[nIndx].pos.x - g_shadow[nIndx].fRadius, g_shadow[nIndx].pos.y, g_shadow[nIndx].pos.z + g_shadow[nIndx].fRadius);
		pVtx[1].pos = D3DXVECTOR3(g_shadow[nIndx].pos.x + g_shadow[nIndx].fRadius, g_shadow[nIndx].pos.y, g_shadow[nIndx].pos.z + g_shadow[nIndx].fRadius);
		pVtx[2].pos = D3DXVECTOR3(g_shadow[nIndx].pos.x - g_shadow[nIndx].fRadius, g_shadow[nIndx].pos.y, g_shadow[nIndx].pos.z - g_shadow[nIndx].fRadius);
		pVtx[3].pos = D3DXVECTOR3(g_shadow[nIndx].pos.x + g_shadow[nIndx].fRadius, g_shadow[nIndx].pos.y, g_shadow[nIndx].pos.z - g_shadow[nIndx].fRadius);

		//頂点バッファをアンロック
		g_pVtxBuffShadow->Unlock();

	}
}

//=====================
// 影のサイズの取得処理
//=====================
Shadow* GetShadow(void)
{
	return &g_shadow[0];
}
