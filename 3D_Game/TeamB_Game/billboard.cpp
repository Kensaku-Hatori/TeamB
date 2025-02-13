//==================================
//
// ビルボード処理[Biillboard.cpp]
// Author:kaiti
//
//==================================

#include "billboard.h"
#include "meshfield.h"
#include "shadow.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureBiillboard[MAX_TEX_FIELD] = {	NULL };

Biillboard g_Biillboard[MAX_BILLBOARD];

//=========================
// ビルボードの初期化処理^^
//=========================
void InitBiillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_Biillboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Biillboard[nCnt].origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Biillboard[nCnt].textype = 0;
		g_Biillboard[nCnt].nWidth = 0;
		g_Biillboard[nCnt].nHeight = 0;
		g_Biillboard[nCnt].bUse = false;
	}
}

//=======================
// ビルボードの終了処理
//=======================
void UninitBiillboard(void)
{
	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		//テクスチャの破棄
		if (g_apTextureBiillboard[nCnt] != NULL)
		{
			g_apTextureBiillboard[nCnt]->Release();
			g_apTextureBiillboard[nCnt] = NULL;
		}

		//頂点バッファの破棄
		if (g_Biillboard[nCnt].pVtxBuffBiillboard != NULL)
		{
			g_Biillboard[nCnt].pVtxBuffBiillboard->Release();
			g_Biillboard[nCnt].pVtxBuffBiillboard = NULL;
		}
	}
}

//=======================
// ビルボードの更新処理
//=======================
void UpdateBiillboard(void)
{
}

//=======================
// ビルボードの描画処理
//=======================
void DrawBiillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Biillboard[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Biillboard[nCnt].mtxWorld);

			D3DXMATRIX mtxView;

			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_Biillboard[nCnt].mtxWorld._11 = mtxView._11;
			g_Biillboard[nCnt].mtxWorld._12 = mtxView._21;
			g_Biillboard[nCnt].mtxWorld._13 = mtxView._31;
			g_Biillboard[nCnt].mtxWorld._21 = mtxView._12;
			g_Biillboard[nCnt].mtxWorld._22 = mtxView._22;
			g_Biillboard[nCnt].mtxWorld._23 = mtxView._32;
			g_Biillboard[nCnt].mtxWorld._31 = mtxView._13;
			g_Biillboard[nCnt].mtxWorld._32 = mtxView._23;
			g_Biillboard[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Biillboard[nCnt].pos.x, g_Biillboard[nCnt].pos.y, g_Biillboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Biillboard[nCnt].mtxWorld, &g_Biillboard[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Biillboard[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_Biillboard[nCnt].pVtxBuffBiillboard, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBiillboard[nCnt]);

			//ポリゴンを描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===================
// ビルボードの設定
//===================
void SetBiillboard(D3DXVECTOR3 pos, int nWidth, int nHeigh)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Biillboard[nCnt].bUse == false)
		{
			//各設定
			g_Biillboard[nCnt].pos = pos;			//位置
			g_Biillboard[nCnt].nWidth = nWidth;		//幅
			g_Biillboard[nCnt].nHeight = nHeigh;	//高さ
			g_Biillboard[nCnt].bUse = true;			//使用している状態にする

			//頂点バッファの生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_Biillboard[nCnt].pVtxBuffBiillboard,
				NULL);

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_Biillboard[nCnt].pVtxBuffBiillboard->Lock(0, 0, (void**)&pVtx, 0);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3( -(float)g_Biillboard[nCnt].nWidth, (float)g_Biillboard[nCnt].nHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( +(float)g_Biillboard[nCnt].nWidth, (float)g_Biillboard[nCnt].nHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3( -(float)g_Biillboard[nCnt].nWidth, (float)g_Biillboard[nCnt].nHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( +(float)g_Biillboard[nCnt].nWidth, (float)g_Biillboard[nCnt].nHeight, 0.0f);

			//法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//頂点バッファをアンロック
			g_Biillboard[nCnt].pVtxBuffBiillboard->Unlock();

			break;
		}
	}
}

//===================
// メッシュ壁のテクスチャ設定
//===================
//void SetwallTexture()
//{
//	//テクスチャのポインタを取得
//	LPDIRECT3DTEXTURE9 pTexture = GetTexture2(TEX_WALL);
//
//	if (pTexture != NULL)
//	{
//		//g_pTextureMeshWall = pTexture;
//	}
//
//}