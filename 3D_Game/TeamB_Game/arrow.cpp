//=======================================================
// 
// 矢印[arrow.cpp]
// Author:Rio Ohno
// 
//=======================================================

#include "arrow.h"

//グローバル変数宣言
Arrow g_Arrow;

//===================
//矢印の初期化処理
//===================
void InitArrow()
{
	g_Arrow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Arrow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Arrow.fHeight = 0.0;
	g_Arrow.fWidth = 0.0f;
	g_Arrow.bUse = false;

}

//===================
//矢印の終了処理
//===================
void UninitArrow()
{
	if (g_Arrow.VtxBuff != NULL)
	{
		g_Arrow.VtxBuff->Release();
		g_Arrow.VtxBuff = NULL;
	}
}

//===================
//矢印の更新処理
//===================
void UpdateArrow()
{

}

//===================
//矢印の描画処理
//===================
void DrawArrow()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	if (g_Arrow.bUse == true)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Arrow.mtxWorld);

		//向きを反転
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Arrow.rot.y, g_Arrow.rot.x, g_Arrow.rot.z);
		D3DXMatrixMultiply(&g_Arrow.mtxWorld, &g_Arrow.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Arrow.pos.x, g_Arrow.pos.y, g_Arrow.pos.z);
		D3DXMatrixMultiply(&g_Arrow.mtxWorld, &g_Arrow.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Arrow.mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_Arrow.VtxBuff, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//ポリゴンを描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//===================
//矢印の設定処理
//===================
void SetArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_Arrow.VtxBuff,
		NULL);

	//各種設定
	g_Arrow.pos = pos;
	g_Arrow.rot = rot;
	g_Arrow.fWidth = fWidth;
	g_Arrow.fHeight = fHeight;
	g_Arrow.bUse = true;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_Arrow.VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-g_Arrow.fWidth * 0.5f, 0.0f, g_Arrow.fHeight * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(g_Arrow.fWidth * 0.5f, 0.0f, g_Arrow.fHeight * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-g_Arrow.fWidth * 0.5f, 0.0f, -g_Arrow.fHeight * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(g_Arrow.fWidth * 0.5f, 0.0f, -g_Arrow.fHeight * 0.5f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//色の設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック　
	g_Arrow.VtxBuff->Unlock();
}