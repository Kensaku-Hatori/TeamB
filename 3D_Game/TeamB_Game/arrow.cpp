//=======================================================
// 
// 矢印[arrow.cpp]
// Author:Rio Ohno
// 
//=======================================================

//インクルード
#include "arrow.h"

//グローバル変数宣言
Arrow g_Arrow[MAX_ARROW];

//===================
//矢印の初期化処理
//===================
void InitArrow()
{
	for (int nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		//各種初期化
		g_Arrow[nCnt].Destpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的位置
		g_Arrow[nCnt].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的への向き
		g_Arrow[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_Arrow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
		g_Arrow[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//色
		g_Arrow[nCnt].VtxBuff = { NULL };//頂点情報
		g_Arrow[nCnt].tex = { NULL };//テクスチャポインタ
		g_Arrow[nCnt].fHeight = 0.0;//ポリゴンの高さ
		g_Arrow[nCnt].fWidth = 0.0f;//ポリゴンの幅
		g_Arrow[nCnt].fRadius = 0.0f;//posからどれだけ離すか
		g_Arrow[nCnt].Index = 0;
		g_Arrow[nCnt].bUse = false;//使用していない状態にする
	}
}

//===================
//矢印の終了処理
//===================
void UninitArrow()
{
	for (int nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		//テクスチャの破棄
		if (g_Arrow[nCnt].tex != NULL)
		{
			g_Arrow[nCnt].tex->Release();
			g_Arrow[nCnt].tex = NULL;
		}

		//頂点バッファの破棄
		if (g_Arrow[nCnt].VtxBuff != NULL)
		{
			g_Arrow[nCnt].VtxBuff->Release();
			g_Arrow[nCnt].VtxBuff = NULL;
		}
	}
}

//===================
//矢印の更新処理
//===================
void UpdateArrow()
{
	for (int nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		if (g_Arrow[nCnt].bUse == true)
		{
			//目的地へのベクトル
			D3DXVECTOR3 vec = g_Arrow[nCnt].Destpos - g_Arrow[nCnt].pos;
			float fDistance = (vec.x) * (vec.x) + (vec.z) * (vec.z);			//距離
			float fAngle = 0.0f;												//角度
			float rotData = 0.0f;												//角度の差

			//距離の取得
			fDistance = sqrtf(fDistance);

			//角度の取得
			fAngle = (float)atan2(vec.x, vec.z);

			//目標の移動方向（角度）の補正
			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2.0f;
			}
			else if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2.0f;
			}

			//目的への向き設定
			g_Arrow[nCnt].Destrot.y = fAngle;

			rotData = g_Arrow[nCnt].Destrot.y - g_Arrow[nCnt].rot.y;

			// 角度の近道
			if (rotData >= D3DX_PI)
			{
				g_Arrow[nCnt].rot.y += D3DX_PI * 2.0f;
			}
			else if (rotData <= -D3DX_PI)
			{
				g_Arrow[nCnt].rot.y -= D3DX_PI * 2.0f;
			}

			//向きの反映
			g_Arrow[nCnt].rot.y += (g_Arrow[nCnt].Destrot.y - g_Arrow[nCnt].rot.y) * 0.1f;
		}
	}
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
	for (int nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		if (g_Arrow[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Arrow[nCnt].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Arrow[nCnt].rot.y, g_Arrow[nCnt].rot.x, g_Arrow[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Arrow[nCnt].mtxWorld, &g_Arrow[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Arrow[nCnt].pos.x, g_Arrow[nCnt].pos.y, g_Arrow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Arrow[nCnt].mtxWorld, &g_Arrow[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Arrow[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_Arrow[nCnt].VtxBuff, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_Arrow[nCnt].tex);

			//ポリゴンを描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

//===================
//矢印の設定処理
//===================
void SetArrow(D3DXVECTOR3 DestPos, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, float fRadius, bool bGradation, bool bAnim)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	HRESULT hresult;

	int nCnt = 0;
	for (nCnt = 0; nCnt < MAX_ARROW; nCnt++)
	{
		if (g_Arrow[nCnt].bUse == false)
		{
			//頂点バッファの生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_Arrow[nCnt].VtxBuff,
				NULL);

			//テクスチャの読込
			hresult = D3DXCreateTextureFromFile(pDevice,
				ARROW_TEX,
				&g_Arrow[nCnt].tex);

			if (FAILED(hresult))
			{
				return;
			}

			//各種設定
			g_Arrow[nCnt].Destpos = DestPos;
			g_Arrow[nCnt].pos = pos;
			g_Arrow[nCnt].col = col;
			g_Arrow[nCnt].fWidth = fWidth;
			g_Arrow[nCnt].fHeight = fHeight;
			g_Arrow[nCnt].fRadius = fRadius;
			g_Arrow[nCnt].bUse = true;

			//向きの設定------------------------------------------------------------
			D3DXVECTOR3 vec = g_Arrow[nCnt].Destpos - g_Arrow[nCnt].pos;
			float fAngle = 0.0f;										//角度格納用

			//角度の取得
			fAngle = (float)atan2(vec.x, vec.z);

			//目標の移動方向（角度）の補正
			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2.0f;
			}
			else if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2.0f;
			}

			//向き設定
			g_Arrow[nCnt].rot.y = fAngle;

			//-------------------------------------------------------------------------

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_Arrow[nCnt].VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(-g_Arrow[nCnt].fWidth * 0.5f, 1.0f, (g_Arrow[nCnt].fHeight + g_Arrow[nCnt].fRadius));
			pVtx[1].pos = D3DXVECTOR3(g_Arrow[nCnt].fWidth * 0.5f, 1.0f, (g_Arrow[nCnt].fHeight + g_Arrow[nCnt].fRadius));
			pVtx[2].pos = D3DXVECTOR3(-g_Arrow[nCnt].fWidth * 0.5f, 1.0f, g_Arrow[nCnt].fRadius);
			pVtx[3].pos = D3DXVECTOR3(g_Arrow[nCnt].fWidth * 0.5f, 1.0f, g_Arrow[nCnt].fRadius);

			//法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//色の設定
			pVtx[0].col = g_Arrow[nCnt].col;
			pVtx[1].col = g_Arrow[nCnt].col;
			pVtx[2].col = g_Arrow[nCnt].col;
			pVtx[3].col = g_Arrow[nCnt].col;

			if (bGradation == true)
			{
				D3DXCOLOR colBottom = D3DCOLOR_RGBA(255, 255, 50, 204);
				pVtx[2].col = colBottom;
				pVtx[3].col = colBottom;
			}

			//テクスチャの設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//頂点バッファをアンロック　
			g_Arrow[nCnt].VtxBuff->Unlock();

			break;
		}
	}
}
//===================
//矢印の位置の更新処理
//===================
void SetPositonArrow(int nIdex, D3DXVECTOR3 pos)
{
	g_Arrow[nIdex].pos = D3DXVECTOR3(pos.x, g_Arrow[nIdex].pos.y, pos.z);
}
