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
float maxVtx = 0.0f, polyNum = 0.0f, indexNum = 0.0f;					

//ファイル格納
static const char* MESHFIELD_TEXTURE[] =
{
	NULL
};

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
		g_Meshfield[nCnt].textype = 0;									//テクスチャタイプ
		g_Meshfield[nCnt].nDiviX = 1;									//分割数x(0にしたらnullptr)
		g_Meshfield[nCnt].nDiviY = 0;									//分割数y
		g_Meshfield[nCnt].nDiviZ = 1;									//分割数z(0にしたらnullptr)
		g_Meshfield[nCnt].fWidth = 150;									//幅
		g_Meshfield[nCnt].fHeight = 150;								//高さ
		g_Meshfield[nCnt].bUse = false;									//使用していない状態にする

		//テクスチャの読込
		D3DXCreateTextureFromFile(pDevice,
			MESHFIELD_TEXTURE[g_Meshfield[nCnt].textype],
			&g_pTextureMeshfield[nCnt]);

		maxVtx += (g_Meshfield[nCnt].nDiviX + 1) * (g_Meshfield[nCnt].nDiviZ + 1);											//頂点数
		polyNum += (g_Meshfield[nCnt].nDiviZ * 2) * (g_Meshfield[nCnt].nDiviX + (g_Meshfield[nCnt].nDiviZ - 1) * 2);		//ポリゴン数
		indexNum += (g_Meshfield[nCnt].nDiviZ * 2) * (g_Meshfield[nCnt].nDiviX + (g_Meshfield[nCnt].nDiviZ * 2) - 1);		//インデックス
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * maxVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * indexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	VERTEX_3D* pVtx = NULL;
	WORD* pIdx = NULL;

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

		//頂点情報の設定
		for (int nCntZ = 0; nCntZ <= g_Meshfield[nCnt].nDiviZ; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= g_Meshfield[nCnt].nDiviX; nCntX++)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(-g_Meshfield[nCnt].fWidth + (g_Meshfield[nCnt].fWidth * nCntX), 0.0f, g_Meshfield[nCnt].fHeight - (g_Meshfield[nCnt].fHeight * nCntZ));

				//法線ベクトルの設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2((1.0f / g_Meshfield[nCnt].nDiviX) * nCntX, (1.0f / g_Meshfield[nCnt].nDiviZ) * nCntZ);

				pVtx++;
			}
		}

		//頂点バッファをアンロック　
		g_pVtxBuffMeshfield->Unlock();

		//インデックスバッファをロック
		g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

		int nCntX;
		for (int nCntZ = 0; nCntZ < g_Meshfield[nCnt].nDiviZ; nCntZ++)
		{
			for (nCntX = 0; nCntX <= g_Meshfield[nCnt].nDiviX; nCntX++)
			{
				//インデックスの設定
				pIdx[0] = (g_Meshfield[nCnt].nDiviX + 1) * (nCntZ + 1) + nCntX;
				pIdx[1] = nCntX + (nCntZ * (g_Meshfield[nCnt].nDiviX + 1));

				pIdx += 2;
			}

			if (nCntZ < g_Meshfield[nCnt].nDiviZ - 1)
			{
				pIdx[0] = (nCntX - 1) + (nCntZ * (g_Meshfield[nCnt].nDiviX + 1));
				pIdx[1] = (nCntX - 1) + (nCntZ * (g_Meshfield[nCnt].nDiviX + 1)) + (g_Meshfield[nCnt].nDiviX + 2) * (nCntZ + 1);

				pIdx += 2;
			}
		}

		//インデックスバッファのアンロック
		g_pIdxBuffMeshField->Unlock();
	}
}

//===============================
// メッシュ床の終了処理
//===============================
void UninitMeshfield(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
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
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, maxVtx, 0, polyNum);
		}
	}
}

//===============================
// メッシュ床の設定処理
//===============================
void SetMeshfield(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int textype, int nDiviX,int nDiviY, int nDiviZ, int fWidth, int fHeight)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MESH_NUM_MAX; nCnt++)
	{
		if (g_Meshfield[nCnt].bUse==false)
		{
			g_Meshfield[nCnt].pos = pos;						//位置
			g_Meshfield[nCnt].rot = rot;						//向き
			g_Meshfield[nCnt].textype = textype;				//テクスチャタイプ
			g_Meshfield[nCnt].nDiviX = nDiviX;					//分割数x
			g_Meshfield[nCnt].nDiviY = nDiviY;					//分割数y
			g_Meshfield[nCnt].nDiviZ = nDiviZ;					//分割数z
			g_Meshfield[nCnt].fWidth = fWidth;					//幅
			g_Meshfield[nCnt].fHeight = fHeight;				//高さ
			g_Meshfield[nCnt].bUse = true;						//使用している状態にする

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

			//頂点バッファをアンロック　
			g_pVtxBuffMeshfield->Unlock();

			break;
		}
	}
}