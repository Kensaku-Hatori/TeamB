//================================
//
// エフェクト処理[Effect.cpp]
// Author:kaiti
//
//================================
#include "effect.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
LPDIRECT3DTEXTURE9 g_apTextureEffect[1] = {};
Effect g_Effect[MAX_EFFECT];
//=========================
// エフェクトの初期化処理
//=========================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		g_Effect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_Effect[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_apTextureEffect[0]); //1

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffEffect,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Effect[nCnt].pos.x - EFFECT_SIZE, g_Effect[nCnt].pos.y + EFFECT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Effect[nCnt].pos.x + EFFECT_SIZE, g_Effect[nCnt].pos.y + EFFECT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Effect[nCnt].pos.x - EFFECT_SIZE, g_Effect[nCnt].pos.y - EFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Effect[nCnt].pos.x + EFFECT_SIZE, g_Effect[nCnt].pos.y - EFFECT_SIZE, 0.0f);

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

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}
//=======================
// エフェクトの終了処理
//=======================
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_apTextureEffect[0] != NULL)
	{
		g_apTextureEffect[0]->Release();
		g_apTextureEffect[0] = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//=======================
// エフェクトの更新処理
//=======================
void UpdateEffect(void)
{
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse == true)
		{
			g_Effect[nCnt].pos += g_Effect[nCnt].move;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[1].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[2].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[3].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);

			g_Effect[nCnt].nLife -= 1;
			//エフェクトの寿命
			if (g_Effect[nCnt].nLife <= 0)
			{
				g_Effect[nCnt].bUse = false;
			}
			g_Effect[nCnt].fRadius -= 0.5f;
			//
			if (g_Effect[nCnt].fRadius <= 0)
			{
				g_Effect[nCnt].fRadius = 0;
			}
			g_Effect[nCnt].col.a -= 0.05f;
			if (g_Effect[nCnt].col.a <= 0.0f)
			{
				g_Effect[nCnt].col.a = 0.0f;
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}
//=======================
// エフェクトの描画処理
//=======================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Effect[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_Effect[nCnt].mtxWorld._11 = mtxView._11;
			g_Effect[nCnt].mtxWorld._12 = mtxView._21;
			g_Effect[nCnt].mtxWorld._13 = mtxView._31;
			g_Effect[nCnt].mtxWorld._21 = mtxView._12;
			g_Effect[nCnt].mtxWorld._22 = mtxView._22;
			g_Effect[nCnt].mtxWorld._23 = mtxView._32;
			g_Effect[nCnt].mtxWorld._31 = mtxView._13;
			g_Effect[nCnt].mtxWorld._32 = mtxView._23;
			g_Effect[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCnt].pos.x, g_Effect[nCnt].pos.y, g_Effect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCnt].mtxWorld, &g_Effect[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEffect[0]);

			//ポリゴンを描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//===================
// エフェクトの設定
//===================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR color, int nLife, float fRadius)
{
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt;
	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse == false)
		{
			g_Effect[nCnt].pos = D3DXVECTOR3(pos.x,pos.y,pos.z);
			g_Effect[nCnt].move = move;
			g_Effect[nCnt].nLife = nLife;
			g_Effect[nCnt].fRadius = fRadius;
			g_Effect[nCnt].col = color;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCnt].fRadius, g_Effect[nCnt].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCnt].fRadius, g_Effect[nCnt].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCnt].fRadius, -g_Effect[nCnt].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCnt].fRadius, -g_Effect[nCnt].fRadius, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[1].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[2].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);
			pVtx[3].col = D3DXCOLOR(g_Effect[nCnt].col.r, g_Effect[nCnt].col.g, g_Effect[nCnt].col.b, g_Effect[nCnt].col.a);

			g_Effect[nCnt].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}