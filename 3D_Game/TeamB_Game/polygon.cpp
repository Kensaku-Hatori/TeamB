//================================
//
// ポリゴン表示処理[polygon.cpp]
// Author:kaiti
//
//================================
#include "polygon.h"
#include "player.h"
//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;
LPDIRECT3DTEXTURE9 g_apTexturePolygon[1] = {};

D3DXVECTOR3 g_posPolygon;//位置
D3DXVECTOR3 g_rotPolygon;//向き
D3DXMATRIX g_mtxWorldPolygon;//ワールドマトリックス

//=======================
// ポリゴンの初期化処理
//=======================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	g_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yuka00.jpg", &g_apTexturePolygon[0]); //1

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffPolygon,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_X, g_posPolygon.y, g_posPolygon.z + POLYGON_Y);
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_X, g_posPolygon.y, g_posPolygon.z + POLYGON_Y);
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_X, g_posPolygon.y, g_posPolygon.z - POLYGON_Y);
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_X, g_posPolygon.y, g_posPolygon.z - POLYGON_Y);

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
	pVtx[1].tex = D3DXVECTOR2(3.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(3.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPolygon->Unlock();
}
//====================
// ポリゴンの終了処理
//====================
void UninitPolygon(void)
{
	//テクスチャの破棄
	if (g_apTexturePolygon[0] != NULL)
	{
		g_apTexturePolygon[0]->Release();
		g_apTexturePolygon[0] = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}
//=====================
// ポリゴンの更新処理
//=====================
void UpdatePolygon(void)
{

}
//====================
// ポリゴンの描画処理
//====================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTexturePolygon[0]);

	//ポリゴンを描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//================
// 当たり判定
//================
void CollisionPolygon(void)
{
	D3DXVECTOR3 aPos[2];

	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;

	Player* pPlayer = GetPlayer();

	aPos[0].x = g_posPolygon.x - cosf(g_rotPolygon.y) * POLYGON_X;
	aPos[0].z = g_posPolygon.z + sinf(g_rotPolygon.y) * POLYGON_X;

	aPos[1].x = g_posPolygon.x + cosf(g_rotPolygon.y) * POLYGON_X;
	aPos[1].z = g_posPolygon.z - sinf(g_rotPolygon.y) * POLYGON_X;

	//ベクトルA
	vecA = aPos[1] - aPos[0];
	//ベクトルB
	vecB = pPlayer->pos - aPos[0];

	float fvec = (vecA.z * vecB.x) - (vecA.x * vecB.z);

	if (fvec < 0)
	{
		pPlayer->pos = pPlayer->posOld;
	}
}