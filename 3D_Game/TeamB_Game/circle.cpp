//=======================================================
// 
// サークル[circle.cpp]
// Author:Rio Ohno
// 
//=======================================================

#include "circle.h"

//グローバル変数宣言
Circle g_Circle[MAX_CIRCLE];

//=====================
//サークルの初期化処理
//=====================
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

//=====================
//サークルの終了処理
//=====================
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

//=====================
//サークルの更新処理
//=====================
void UpdateCircle()
{

}

//=====================
//サークルの描画処理
//=====================
void DrawCircle()
{

}

//=====================
//サークルの設定処理
//=====================
void SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY, float fRadius, bool bAnime, bool bUse)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (g_Circle[nCnt].bUse == false)
		{
			//各変数の設定
			g_Circle[nCnt].pos = pos;
			g_Circle[nCnt].rot = rot;
			g_Circle[nCnt].nDiviX = DiviX;
			g_Circle[nCnt].nDiviY = DiviY;
			g_Circle[nCnt].fRadius = fRadius;
			g_Circle[nCnt].bAnime = bAnime;

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
					float fAngle = (D3DX_PI * 2 / g_Circle[nCnt].nDiviX) * nCntX;

					//頂点の設定
					pVtx[indx].pos = D3DXVECTOR3(g_Circle[nCnt].fRadius * sinf(fAngle), 0.0f, g_Circle[nCnt].fRadius * cosf(fAngle));

					//中心へのベクトル
					D3DXVECTOR3 vec = pVtx[indx].pos - g_Circle[nCnt].pos;

					//ベクトルの正規化,各頂点の法線の設定
					D3DXVec3Normalize(&pVtx[indx].nor, &vec);

					//頂点カラーの設定
					pVtx[indx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//テクスチャ座標の設定
					pVtx[indx].tex = D3DXVECTOR2((1.0f / g_Circle[nCnt].nDiviX) * nCntX, (1.0f / g_Circle[nCnt].nDiviY) * nCntY);

					indx++;
				}
			}

			//頂点バッファをアンロック　
			g_Circle[nCnt].pVtxBuff->Unlock();

			g_Circle[nCnt].bUse = true;
			break;
		}
	}
}