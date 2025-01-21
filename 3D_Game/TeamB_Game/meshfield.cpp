//==============================================
//
// メッシュ床表示処理[meshfield.cpp]
// Author:kaiti
//
//==============================================

#include "meshfield.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;						//頂点情報へのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshfield[MESH_NUM_MAX] = {};				//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;						//インデックスバッファへのポインタ

MeshField g_Meshfield[MESH_NUM_MAX];									//ポリゴン(横)の構造体

//=================================
// メッシュ床の初期化処理
//=================================
void InitMeshfield(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		//構造体の初期化
		g_Meshfield[nCnt].pos = D3DXVECTOR3(-900.0f, 0.0f, 900.0f);		//位置
		g_Meshfield[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
		g_Meshfield[nCnt].textype = MESH_TEX_NULL;						//テクスチャタイプ
		g_Meshfield[nCnt].DiviX = 0;									//分割数x
		g_Meshfield[nCnt].DiviZ = 0;									//分割数z
		g_Meshfield[nCnt].fWidth = 0.0f;								//幅
		g_Meshfield[nCnt].fHeight = 0.0f;								//高さ
		g_Meshfield[nCnt].bUse = false;									//使用していない状態にする

		//テクスチャの読込
		D3DXCreateTextureFromFile(pDevice,
			MESHFIELD_TEXTURE[g_Meshfield[nCnt].textype],
			&g_pTextureMeshfield[nCnt]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_NO,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

		VERTEX_3D* pVtx = NULL;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= MESHVTX_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MESHVTX_X; nCntX++)
		{
			//頂点座標の設定
			//pVtx[0].pos = D3DXVECTOR3(-MESH_SIZE + (MESH_SIZE * nCntX), 0.0f, MESH_SIZE - (MESH_SIZE * nCntZ));
			pVtx[0].pos = D3DXVECTOR3(-MESH_SIZE + (MESH_SIZE * nCntX), 0.0f, MESH_SIZE - (MESH_SIZE * nCntZ));

				//法線ベクトルの設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2((1.0f / MESHVTX_X) * nCntX, (1.0f / MESHVTX_Z) * nCntZ);

				pVtx++;
			}
		}

		////円柱
		//int radius = 150;
		//int index = 0;
		//float fAngle = (D3DX_PI * 2) / MESHVTX_X;
		//
		//for (int nCntV = 0; nCntV < MESHVTX_Z + 1; nCntV++)
		//{
		//	for (int nCntH = 0; nCntH < MESHVTX_X + 1; nCntH++)
		//	{
		//		//角度
		//		float Angle = fAngle * nCntH;
		//
		//		//頂点座標の設定
		//		pVtx[index].pos = D3DXVECTOR3(sinf(Angle) * radius, 50.0f * (nCntV + 1), cosf(Angle) * radius);
		//		
		//		D3DXVECTOR3 nor;//位置
		//		nor = pVtx[index].pos - g_posMeshfield;
		//		//法線ベクトル
		//		D3DXVec3Normalize(&pVtx[index].nor,&nor);
		//		
		//		//頂点カラーの設定
		//		pVtx[index].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		//		//テクスチャ座標の設定
		//		pVtx[index].tex = D3DXVECTOR2((1.0f / MESHVTX_X) * nCntH, (1.0f / MESHVTX_Z) * nCntV);
		//
		//		index++;
		//	}
		//}

		//頂点バッファをアンロック　
		g_pVtxBuffMeshfield->Unlock();

		WORD* pIdx;

		//インデックスバッファをロック
		g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

		int nCntX;
		for (int nCntZ = 0; nCntZ < MESHVTX_Z; nCntZ++)
		{
			for (nCntX = 0; nCntX <= MESHVTX_X; nCntX++)
			{
				//インデックスの設定
				pIdx[0] = (MESHVTX_X + 1) * (nCntZ + 1) + nCntX;
				pIdx[1] = nCntX + (nCntZ * (MESHVTX_X + 1));

				pIdx += 2;
			}
			if (nCntZ < MESHVTX_Z - 1)
			{
				pIdx[0] = (nCntX - 1) + (nCntZ * (MESHVTX_X + 1));
				pIdx[1] = (nCntX - 1) + (nCntZ * (MESHVTX_X + 1)) + (MESHVTX_X + 2) * (nCntZ + 1);

				pIdx += 2;
			}
		}

		////インデックスの設定(床)
		//pIdx[0] = 3;
		//pIdx[1] = 0;
		//
		//pIdx[2] = 4;
		//pIdx[3] = 1;
		//
		//pIdx[4] = 5;
		//pIdx[5] = 2;
		//
		//pIdx[6] = 2;
		//pIdx[7] = 6;
		//
		//pIdx[8] = 6;
		//pIdx[9] = 3;
		//
		//pIdx[10] = 7;
		//pIdx[11] = 4;
		//
		//pIdx[12] = 8;
		//pIdx[13] = 5;
		//
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
		g_pIdxBuffMeshField->Unlock();
	
}

//===============================
// メッシュ床の終了処理
//===============================
void UninitMeshfield(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MESH_TEX_MAX; nCnt++)
	{
		if (g_pTextureMeshfield[nCnt] != NULL)
		{
			g_pTextureMeshfield[nCnt]->Release();
			g_pTextureMeshfield[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//===============================
// メッシュ床の更新処理
//===============================
void UpdateMeshfield(void)
{

}

//===============================
// メッシュ床の描画処理
//===============================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		if (g_Meshfield[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Meshfield[nCnt].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Meshfield[nCnt].rot.y, g_Meshfield[nCnt].rot.x, g_Meshfield[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Meshfield[nCnt].mtxWorld, &g_Meshfield[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Meshfield[nCnt].pos.x, g_Meshfield[nCnt].pos.y, g_Meshfield[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Meshfield[nCnt].mtxWorld, &g_Meshfield[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Meshfield[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshField);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshfield[g_Meshfield[nCnt].textype]);

			//メッシュ床を描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VTX, 0, POLYGON_NO);
		}
	}
}