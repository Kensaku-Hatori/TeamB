//==============================================
//
// メッシュ円柱表示処理[MeshCylinder.cpp]
// Author:kaiti
//
//==============================================
#include "meshcylinder.h"
//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;
//インデックスバッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;

D3DXVECTOR3 g_posMeshCylinder;//位置
D3DXVECTOR3 g_rotMeshCylinder;//向き
D3DXMATRIX g_mtxWorldMeshCylinder;//ワールドマトリックス

//=================================
// メッシュ円柱の初期化処理
//=================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	g_posMeshCylinder = D3DXVECTOR3(0.0f, -500.0f, 0.0f);
	g_rotMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\kabe.jpg", &g_pTextureMeshCylinder);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAXCYLINDER_VTX,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffMeshCylinder,
		                        NULL);
	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * CYLINDERINDEX_NO,
							   D3DUSAGE_WRITEONLY,
							   D3DFMT_INDEX16,
							   D3DPOOL_MANAGED,
							   &g_pIdxBuffMeshCylinder,
							   NULL);

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//円柱
	int radius = 3000;
	int index = 0;
	float fAngle = (D3DX_PI * 2.0f) / MESHCYLINDERVTX_X;

	for (int nCntV = 0; nCntV < MESHCYLINDERVTX_Z + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < MESHCYLINDERVTX_X + 1; nCntH++)
		{
			//角度
			float Angle = fAngle * nCntH;

			//頂点座標の設定
			pVtx[index].pos = D3DXVECTOR3(sinf(Angle) * radius, 1000.0f *(MESHCYLINDERVTX_Z - nCntV), cosf(Angle) * radius);
			
			D3DXVECTOR3 nor;//位置
			nor = pVtx[index].pos - g_posMeshCylinder;
			//nor = g_posMeshCylinder - pVtx[index].pos;

			//法線ベクトル
			D3DXVec3Normalize(&pVtx[index].nor,&nor);

			//頂点カラーの設定
			pVtx[index].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			//テクスチャ座標の設定
			pVtx[index].tex = D3DXVECTOR2((1.0f / MESHCYLINDERVTX_X) * nCntH, (1.0f / MESHCYLINDERVTX_Z) * nCntV);

			index++;
		}
	}

	//頂点バッファをアンロック　
	g_pVtxBuffMeshCylinder->Unlock();

	//インデックスバッファをロック
	WORD* pIdx;
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);
	
	int nCntX;
	for (int nCntZ = 0; nCntZ < MESHCYLINDERVTX_Z; nCntZ++)
	{
		for (nCntX = 0; nCntX <= MESHCYLINDERVTX_X; nCntX++)
		{
			//インデックスの設定
			pIdx[0] = (MESHCYLINDERVTX_X + 1) * (nCntZ + 1) + nCntX;
			pIdx[1] = nCntX + (nCntZ * (MESHCYLINDERVTX_X + 1));

			pIdx += 2;
		}
		if (nCntZ < MESHCYLINDERVTX_Z - 1)
		{
			pIdx[0] = (nCntX - 1) + (nCntZ * (MESHCYLINDERVTX_X + 1));
			pIdx[1] = (nCntX - 1) + (nCntZ * (MESHCYLINDERVTX_X + 1)) + (MESHCYLINDERVTX_X + 2) * (nCntZ + 1);

			pIdx += 2;
		}
	}

	////インデックスの設定(円柱)
	//pIdx[0] = 9;
	//pIdx[1] = 0;
	//
	//pIdx[2] = 10;
	//pIdx[3] = 1;
	//
	//pIdx[4] = 11;
	//pIdx[5] = 2;
	//
	//pIdx[6] = 12;
	//pIdx[7] = 3;
	//
	//pIdx[8] = 13;
	//pIdx[9] = 4;
	//
	//pIdx[10] = 14;
	//pIdx[11] = 5;
	//
	//pIdx[12] = 15;
	//pIdx[13] = 6;
	//
	//pIdx[14] = 16;
	//pIdx[15] = 7;
	//
	//pIdx[16] = 9;
	//pIdx[17] = 0;

	//インデックスバッファのアンロック
	g_pIdxBuffMeshCylinder->Unlock();
}
//===============================
// メッシュ円柱の終了処理
//===============================
void UninitMeshCylinder(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}
	//インデックスバッファの破棄
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}
//===============================
// メッシュ円柱の更新処理
//===============================
void UpdateMeshCylinder(void)
{

}
//===============================
// メッシュ円柱の描画処理
//===============================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//メッシュ円柱を描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAXCYLINDER_VTX, 0, CYLINDERPOLYGON_NO);
}