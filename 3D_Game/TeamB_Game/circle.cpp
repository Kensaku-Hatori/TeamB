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
		//各種初期化
		g_Circle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 位置
		g_Circle[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
		g_Circle[nCnt].AddCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 色の変化量
		g_Circle[nCnt].pVtxBuff = { NULL };								// 頂点バッファ
		g_Circle[nCnt].IndxBuff = { NULL };								// インデックスバッファ
		g_Circle[nCnt].nDiviX = 0;										// Xの分割数
		g_Circle[nCnt].nDiviY = 0;										// Yの分割数
		g_Circle[nCnt].nMaxVtx = 0;										// 頂点数
		g_Circle[nCnt].nPolyNum = 0;									// ポリゴン数
		g_Circle[nCnt].nCntFrame = 0;									// フレームカウンター
		g_Circle[nCnt].fHeight = 0.0f;									// 高さ
		g_Circle[nCnt].fRadius = 0.0f;									// 半径
		g_Circle[nCnt].bGradation = false;								// グラデーションするかどうか
		g_Circle[nCnt].bAnime = false;									// 動きをつけるかどうか
		g_Circle[nCnt].bUse = false;									// 使用しているかどうか
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

		//テクスチャの破棄
		if (g_Circle[nCnt].tex != NULL)
		{
			g_Circle[nCnt].tex->Release();
			g_Circle[nCnt].tex = NULL;
		}

	}
}

//=========================
//サークルの更新処理
//=========================
void UpdateCircle()
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		int  i = 0;
		if (g_Circle[nCnt].bUse == true)
		{
			if (g_Circle[nCnt].bAnime == true && g_Circle[nCnt].frame >= 0)
			{
				int indx = 0;										//頂点インデックス

				//フレームカウント
				g_Circle[nCnt].nCntFrame++;

				//頂点バッファをロックし、頂点情報へのポインタを取得
				g_Circle[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				for (int nCntY = 0; nCntY <= g_Circle[nCnt].nDiviY; nCntY++)
				{
					for (int nCntX = 0; nCntX <= g_Circle[nCnt].nDiviX; nCntX++)
					{
						//頂点カラーの設定
						pVtx[indx].col = D3DXCOLOR((FLOAT)g_Circle[nCnt].col.r + (g_Circle[nCnt].AddCol.r * (g_Circle[nCnt].nCntFrame)),
							(FLOAT)g_Circle[nCnt].col.g + (g_Circle[nCnt].AddCol.g * (g_Circle[nCnt].nCntFrame)),
							(FLOAT)g_Circle[nCnt].col.b + (g_Circle[nCnt].AddCol.b * (g_Circle[nCnt].nCntFrame)),
							(FLOAT)g_Circle[nCnt].col.a + (g_Circle[nCnt].AddCol.a * (g_Circle[nCnt].nCntFrame)));

						//インデックスを進める
						indx++;
					}
				}

				//フレーム超えたら
				if (g_Circle[nCnt].nCntFrame >= g_Circle[nCnt].frame)
				{
					//g_Circle[nCnt].nCntFrame = 0;
					g_Circle[nCnt].bUse = false;
				}

				//頂点バッファをアンロック　
				g_Circle[nCnt].pVtxBuff->Unlock();
			}

		}
	}
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

	//ライトを切る
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//カリングを切る
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ALPHAテストの設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (g_Circle[nCnt].bUse == true)
		{
			if (g_Circle[nCnt].type == 1)
			{
				// 加算合成を設定する
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Circle[nCnt].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Circle[nCnt].rot.y, g_Circle[nCnt].rot.x, g_Circle[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Circle[nCnt].mtxWorld, &g_Circle[nCnt].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Circle[nCnt].pos.x, g_Circle[nCnt].pos.y, g_Circle[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Circle[nCnt].mtxWorld, &g_Circle[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Circle[nCnt].mtxWorld);

			// 頂点バッファをデバイスからデータストリームに設定
			pDevice->SetStreamSource(0, g_Circle[nCnt].pVtxBuff, 0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_Circle[nCnt].IndxBuff);

			// テクスチャの設定
			pDevice->SetTexture(0, g_Circle[nCnt].tex);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Circle[nCnt].nMaxVtx, 0, g_Circle[nCnt].nPolyNum);

		}
	}

	//加算合成を切る
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ライトをつける
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// アルファテストを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//カリングをつける
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
//サークルの設定処理
//=========================
int SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int DiviX, int DiviY, float fHeight, float fRadius, bool bGradation, bool bAnime, int type)
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
			g_Circle[nCnt].nCntFrame = 0;
			g_Circle[nCnt].fHeight = fHeight;
			g_Circle[nCnt].fRadius = fRadius;
			g_Circle[nCnt].bGradation = bGradation;	//グラデーションの有無
			g_Circle[nCnt].bAnime = bAnime;			//動きの有無
			if (type == 1)
			{
				//テクスチャの読込
				D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\haikei2.jpg", &g_Circle[nCnt].tex); //1
			}

			//アニメーションがtrueなら
			if (g_Circle[nCnt].bAnime == true)
			{
				D3DXCOLOR Col = (col);	//計算結果保存用

				//D3DCOLOR_RGBA対策
				if (col.r > 1.0f)
				{
					Col.r = (FLOAT)col.r / 255.0f;
				}
				if (col.g > 1.0f)
				{		
					Col.g = (FLOAT)col.g / 255.0f;
				}
				if (col.b > 1.0f)
				{
					Col.b = (FLOAT)col.b / 255.0f;
				}
				if (col.a > 1.0f)
				{
					Col.a = (FLOAT)col.a / 255.0f;
				}

				//色の変化量を設定
				g_Circle[nCnt].AddCol.r = (1.0f - Col.r);
				g_Circle[nCnt].AddCol.g = (1.0f - Col.g);
				g_Circle[nCnt].AddCol.b = (1.0f - Col.b);
				g_Circle[nCnt].AddCol.a = (1.0f - Col.a);
			}

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
					D3DXVECTOR3 vec = g_Circle[nCnt].pos - pVtx[indx].pos;

					//ベクトルの正規化,各頂点の法線の設定
					D3DXVec3Normalize(&pVtx[indx].nor, &vec);

					//頂点カラーの設定
					pVtx[indx].col = g_Circle[nCnt].col;

					//グラデーション有なら
					if (g_Circle[nCnt].bGradation == true)
					{
						pVtx[indx].col = D3DXCOLOR(g_Circle[nCnt].col.r, 
							g_Circle[nCnt].col.g, 
							g_Circle[nCnt].col.b, 
							(g_Circle[nCnt].col.a / (g_Circle[nCnt].nDiviY)) * (nCntY));
					}

					//テクスチャ座標の設定
					pVtx[indx].tex = D3DXVECTOR2(1.0f * nCntX,1.0f * nCntY);
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

//=========================
//サークルアニメーションの種類設定処理
//=========================
void SetAnime(int indx, ANIMETYPE type, int frame)
{
	if (g_Circle[indx].bUse == true && g_Circle[indx].bAnime == true)
	{
		g_Circle[indx].type = type;
		g_Circle[indx].frame = frame;
		g_Circle[indx].Anime.bHalf = false;
		g_Circle[indx].nCntFrame = 0;
	
		float a = 1.0f / g_Circle[indx].frame;

		//色の変化量の設定
		g_Circle[indx].AddCol.r = g_Circle[indx].AddCol.r * a;
		g_Circle[indx].AddCol.g = g_Circle[indx].AddCol.g * a;
		g_Circle[indx].AddCol.b = g_Circle[indx].AddCol.b * a;
		g_Circle[indx].AddCol.a = g_Circle[indx].AddCol.a * a;

	//	switch (g_Circle[indx].type)
	//	{
	//	case ANIMETYPE_0:

	//		g_Circle[indx].frame = g_Circle[indx].frame * (4 / 3);

	//		break;

	//	default:

	//		break;
	//	}
	}
}

//=========================
//サークルのアルファ値をを減らす処理
//=========================
void DefAlpha(int indx,int frame)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

}

//=========================
//サークルを消す処理
//=========================
void DeleteCircle(int indx)
{
	g_Circle[indx].bUse = false;
}