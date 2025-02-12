//=======================================================
// 
// サークル[circle.cpp]
// Author:Rio Ohno
// 
//=======================================================

#include "circle.h"

//グローバル変数宣言
Circle g_Circle[MAX_CIRCLE];

//=========================
//サークルの初期化処理
//=========================
void InitCircle()
{
	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		g_Circle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Circle[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Circle[nCnt].pVtxBuff = { NULL };
		g_Circle[nCnt].IndxBuff = { NULL };
		g_Circle[nCnt].fRadius = 0.0f;
		g_Circle[nCnt].bAnime = false;
		g_Circle[nCnt].bUse = false;
	}
}

//=========================
//サークルの終了処理
//=========================
void UninitCircle()
{
	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		//バッファの破棄
		if (g_Circle[nCnt].pVtxBuff != NULL)
		{
			g_Circle[nCnt].pVtxBuff->Release();
			g_Circle[nCnt].pVtxBuff = NULL;
		}

		//インデックスバッファの破棄
		if (g_Circle[nCnt].IndxBuff != NULL)
		{
			g_Circle[nCnt].IndxBuff->Release();
			g_Circle[nCnt].IndxBuff = NULL;
		}
	}
}

//=========================
//サークルの更新処理
//=========================
void UpdateCircle()
{

}

//=========================
//サークルの描画処理
//=========================
void DrawCircle()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//カリングを切る
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (g_Circle[nCnt].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Circle[nCnt].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Circle[nCnt].rot.y, g_Circle[nCnt].rot.x, g_Circle[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Circle[nCnt].mtxWorld, &g_Circle[nCnt].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Circle[nCnt].pos.x, 0.0f, g_Circle[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Circle[nCnt].mtxWorld, &g_Circle[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Circle[nCnt].mtxWorld);

			// 頂点バッファをデバイスからデータストリームに設定
			pDevice->SetStreamSource(0, g_Circle[nCnt].pVtxBuff, 0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_Circle[nCnt].IndxBuff);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Circle[nCnt].nMaxVtx, 0, g_Circle[nCnt].nPolyNum);

		}
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//カリングをつける
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
//サークルの設定処理
//=========================
int SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int DiviX, int DiviY, float fHeight, float fRadius, bool bGradation, bool bAnime)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//インデックスへのポインタ
	WORD* pIdx = NULL;
	int nCnt = 0;

	for (nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (g_Circle[nCnt].bUse == false)
		{
			//各変数の設定
			g_Circle[nCnt].pos = pos;
			g_Circle[nCnt].rot = rot;
			g_Circle[nCnt].col = col;
			g_Circle[nCnt].nDiviX = DiviX;
			g_Circle[nCnt].nDiviY = DiviY + 1;
			g_Circle[nCnt].fHeight = fHeight;
			g_Circle[nCnt].fRadius = fRadius;
			g_Circle[nCnt].bGradation = bGradation;																						//グラデーションの有無
			g_Circle[nCnt].bAnime = bAnime;																								//動きの有無

			g_Circle[nCnt].nMaxVtx = (g_Circle[nCnt].nDiviX + 1) * (g_Circle[nCnt].nDiviY + 1);											//頂点数
			g_Circle[nCnt].nPolyNum = (2 * g_Circle[nCnt].nDiviX * g_Circle[nCnt].nDiviY + (g_Circle[nCnt].nDiviY - 1) * 4);			//ポリゴン数
			int flindexNum = (2 * (g_Circle[nCnt].nDiviY * (2 + g_Circle[nCnt].nDiviX) - 1));											//インデックス

			//頂点バッファの生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Circle[nCnt].nMaxVtx,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_Circle[nCnt].pVtxBuff,
				NULL);

			//インデックスカウンター
			int indx = 0;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_Circle[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			for (int nCntY = 0; nCntY <= g_Circle[nCnt].nDiviY; nCntY++)
			{
				for (int nCntX = 0; nCntX <= g_Circle[nCnt].nDiviX; nCntX++)
				{
					//角度格納
					float fAngle = ((D3DX_PI * 2 / g_Circle[nCnt].nDiviX) * nCntX);

					//高さの格納
					float fHeight = (g_Circle[nCnt].fHeight / g_Circle[nCnt].nDiviY) * (g_Circle[nCnt].nDiviY - nCntY);

					//頂点の設定
					pVtx[indx].pos = D3DXVECTOR3(g_Circle[nCnt].fRadius * sinf(fAngle), fHeight, g_Circle[nCnt].fRadius * cosf(fAngle));

					//中心へのベクトル
					D3DXVECTOR3 vec = pVtx[indx].pos - g_Circle[nCnt].pos;

					//ベクトルの正規化,各頂点の法線の設定
					D3DXVec3Normalize(&pVtx[indx].nor, &vec);

					//頂点カラーの設定
					pVtx[indx].col = g_Circle[nCnt].col;

					//グラデーション有なら
					if (g_Circle[nCnt].bGradation == true)
					{
						pVtx[indx].col = D3DXCOLOR(g_Circle[nCnt].col.r, g_Circle[nCnt].col.g, g_Circle[nCnt].col.b, (g_Circle[nCnt].col.a / (g_Circle[nCnt].nDiviY + 1)) * (nCntY + 1));
					}

					//テクスチャ座標の設定
					pVtx[indx].tex = D3DXVECTOR2((1.0f / g_Circle[nCnt].nDiviX) * nCntX, (1.0f / g_Circle[nCnt].nDiviY) * nCntY);

					indx++;
				}
			}

			//頂点バッファをアンロック　
			g_Circle[nCnt].pVtxBuff->Unlock();

			//インデックスバッファの生成
			pDevice->CreateIndexBuffer(sizeof(WORD) * flindexNum,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_Circle[nCnt].IndxBuff,
				NULL);

			//インデックスバッファをロック
			g_Circle[nCnt].IndxBuff->Lock(0, 0, (void**)&pIdx, 0);

			int nCntX = 0;
			for (int nCntY = 0; nCntY < g_Circle[nCnt].nDiviY; nCntY++)
			{
				for (nCntX = 0; nCntX <= g_Circle[nCnt].nDiviX; nCntX++)
				{
					//インデックスの設定
					pIdx[0] = (g_Circle[nCnt].nDiviX + 1) * (nCntY + 1) + nCntX;
					pIdx[1] = nCntX + (nCntY * (g_Circle[nCnt].nDiviX + 1));

					pIdx += 2;
				}

				//衰退ポリゴン分
				if (nCntY < g_Circle[nCnt].nDiviY - 1)
				{
					//インデックスの設定
					pIdx[0] = (nCntX - 1) + (nCntY * (g_Circle[nCnt].nDiviX + 1));
					pIdx[1] = nCntX + ((nCntY + 1) * (g_Circle[nCnt].nDiviX + 1));

					pIdx += 2;
				}
			}

			//インデックスバッファをアンロック
			g_Circle[nCnt].IndxBuff->Unlock();

			g_Circle[nCnt].bUse = true;

			break;
		}
	}
		return nCnt;
}

//=========================
//サークルの位置の更新処理
//=========================
void  SetPositionCircle(int indx, D3DXVECTOR3  pos, D3DXVECTOR3 rot)
{
	g_Circle[indx].pos = pos;
	g_Circle[indx].rot = rot;
}