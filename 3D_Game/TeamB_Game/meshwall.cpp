//==============================================
//
// メッシュ壁表示処理[meshWall.cpp]
// Author:kaiti
//
//==============================================

#include "meshwall.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;					//頂点情報へのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshWall[MAX_TEX_WALL] = { NULL };		//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;					//インデックスバッファへのポインタ

MeshWall g_MeshWall[MAX_MESHWALL];									//ポリゴン(縦)の構造体
static char walltexName[MAX_TEX_WALL][32];							//テクスチャファイル名保存用
int wlmaxVtx = 0, wlpolyNum = 0, wlindexNum = 0;					//頂点数、ポリゴン数、インデックス数保存用

//=================================
// メッシュ壁の初期化処理
//=================================
void InitMeshWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		g_MeshWall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCnt].textype = 0;
		g_MeshWall[nCnt].nDiviX = 0;
		g_MeshWall[nCnt].nDiviY = 0;
		g_MeshWall[nCnt].nDiviZ = 0;
		g_MeshWall[nCnt].nWidth = 0;
		g_MeshWall[nCnt].nHeight = 0;
		g_MeshWall[nCnt].nIndex = 0;
		g_MeshWall[nCnt].bUse = false;

		//テクスチャの設定
		D3DXCreateTextureFromFile(pDevice,
								&walltexName[g_MeshWall[nCnt].textype][0],
								&g_pTextureMeshWall[g_MeshWall[nCnt].textype]);

		wlmaxVtx += (g_MeshWall[nCnt].nDiviX + 1) * (g_MeshWall[nCnt].nDiviZ + 1);										//頂点数
		wlpolyNum += (g_MeshWall[nCnt].nDiviZ * 2) * (g_MeshWall[nCnt].nDiviX + (g_MeshWall[nCnt].nDiviZ - 1) * 2);		//ポリゴン数
		wlindexNum += (g_MeshWall[nCnt].nDiviZ * 2) * (g_MeshWall[nCnt].nDiviX + (g_MeshWall[nCnt].nDiviZ * 2) - 1);		//インデックス

	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * wlmaxVtx,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffMeshWall,
		                        NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * wlindexNum,
							   D3DUSAGE_WRITEONLY,
							   D3DFMT_INDEX16,
							   D3DPOOL_MANAGED,
							   &g_pIdxBuffMeshWall,
							   NULL);
	WORD* pIdx = NULL;
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntY = 0; nCntY <= g_MeshWall[nCnt].nDiviY; nCntY++)
		{
			for (int nCntX = 0; nCntX <= g_MeshWall[nCnt].nDiviX; nCntX++)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(-g_MeshWall[nCnt].nWidth + (g_MeshWall[nCnt].nWidth * nCntX), g_MeshWall[nCnt].nHeight - (g_MeshWall[nCnt].nHeight * nCntY), g_MeshWall[nCnt].pos.z);

				//法線ベクトルの設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2((2.0f / g_MeshWall[nCnt].nDiviX) * nCntX, (2.0f / g_MeshWall[nCnt].nDiviY) * nCntY);

				pVtx++;
			}
		}

		//頂点バッファをアンロック　
		g_pVtxBuffMeshWall->Unlock();

		//インデックスバッファをロック
		g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

		int nCntX, nCntY;
		for (nCntY = 0; nCntY < g_MeshWall[nCnt].nDiviY; nCntY++)
		{
			for (nCntX = 0; nCntX <= g_MeshWall[nCnt].nDiviX; nCntX++)
			{
				//インデックスの設定
				pIdx[0] = (g_MeshWall[nCnt].nDiviX + 1) * (nCntY + 1) + nCntX;
				pIdx[1] = nCntX + (nCntY * (g_MeshWall[nCnt].nDiviX + 1));

				pIdx += 2;
			}
			if (nCntY <= g_MeshWall[nCnt].nDiviY - 1)
			{
				pIdx[0] = (nCntX - 1) + (nCntY * (g_MeshWall[nCnt].nDiviX + 1));
				pIdx[1] = (nCntX - 1) + (nCntY * (g_MeshWall[nCnt].nDiviX + 1)) + (g_MeshWall[nCnt].nDiviX + 2) * (nCntY + 1);

				pIdx += 2;
			}
		}
		//インデックスバッファのアンロック
		g_pIdxBuffMeshWall->Unlock();
	}
}

//===============================
// メッシュ壁の終了処理
//===============================
void UninitMeshWall(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX_WALL; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureMeshWall[nCnt] != NULL)
		{
			g_pTextureMeshWall[nCnt]->Release();
			g_pTextureMeshWall[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//===============================
// メッシュ壁の更新処理
//===============================
void UpdateMeshWall(void)
{

}

//===============================
// メッシュ壁の描画処理
//===============================
void DrawMeshWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_MeshWall[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_MeshWall[nCnt].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall[nCnt].rot.y, g_MeshWall[nCnt].rot.x, g_MeshWall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_MeshWall[nCnt].mtxWorld, &g_MeshWall[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_MeshWall[nCnt].pos.x, g_MeshWall[nCnt].pos.y, g_MeshWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_MeshWall[nCnt].mtxWorld, &g_MeshWall[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshWall[g_MeshWall[nCnt].textype]);

			//メッシュ壁を描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, wlmaxVtx, 0, wlpolyNum);
		}
	}
}

//===================
// メッシュ壁の設定
//===================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int textype, int nDiviX, int nDiviY, int nDiviZ, int nWidth, int nHeight)
{
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_MeshWall[nCnt].bUse == false)
		{
			g_MeshWall[nCnt].pos = pos;						//位置
			g_MeshWall[nCnt].rot = rot;						//向き
			g_MeshWall[nCnt].textype = textype;				//テクスチャタイプ
			g_MeshWall[nCnt].nDiviX = nDiviX;				//分割数x
			g_MeshWall[nCnt].nDiviY = nDiviY;				//分割数y
			g_MeshWall[nCnt].nDiviZ = nDiviZ;				//分割数z
			g_MeshWall[nCnt].nWidth = nWidth;				//幅
			g_MeshWall[nCnt].nHeight = nHeight;				//高さ
			g_MeshWall[nCnt].bUse = true;					//使用している状態にする

			break;
		}
	}
}

//===================
// メッシュ壁のテクスチャ設定
//===================
void SetwallTexture(char texfileName[32])
{
	for (int nCnt = 0; nCnt < MAX_TEX_WALL; nCnt++)
	{
		if (walltexName[nCnt][0] == NULL)
		{
			strcpy(&walltexName[nCnt][0], &texfileName[0]);
			break;
		}
	}

}