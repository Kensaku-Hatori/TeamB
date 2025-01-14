//================================
//
// 爆発処理[Explosion.cpp]
// Author:kaiti
//
//================================
#include "explosion.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
LPDIRECT3DTEXTURE9 g_apTextureExplosion[1] = {};
Explosion g_Explosion[MAX_EXPLOSION];
//=========================
// 爆発の初期化処理
//=========================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		g_Explosion[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCnt].nCounterAnim = 0;
		g_Explosion[nCnt].nPattemAnim = 0;
		g_Explosion[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion000.png", &g_apTextureExplosion[0]); //1

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffExplosion,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Explosion[nCnt].pos.x - 25.0f, g_Explosion[nCnt].pos.y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Explosion[nCnt].pos.x - 25.0f, g_Explosion[nCnt].pos.y + 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Explosion[nCnt].pos.x + 25.0f, g_Explosion[nCnt].pos.y - 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Explosion[nCnt].pos.x + 25.0f, g_Explosion[nCnt].pos.y + 25.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}
//=======================
// 爆発の終了処理
//=======================
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_apTextureExplosion[0] != NULL)
	{
		g_apTextureExplosion[0]->Release();
		g_apTextureExplosion[0] = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//=======================
// 爆発の更新処理
//=======================
void UpdateExplosion(void)
{
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == true)
		{
			g_Explosion[nCnt].nCounterAnim++;

			if ((g_Explosion[nCnt].nCounterAnim % 5) == 0)
			{//一定時間経過
				//パターンNoを更新
				g_Explosion[nCnt].nPattemAnim = (g_Explosion[nCnt].nPattemAnim + 1) % 8;

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2((g_Explosion[nCnt].nPattemAnim % 8) * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Explosion[nCnt].nPattemAnim % 8) * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_Explosion[nCnt].nPattemAnim % 8) * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Explosion[nCnt].nPattemAnim % 8) * 0.125f + 0.125f, 1.0f);
			}
			if (g_Explosion[nCnt].nCounterAnim >= 32)
			{
				g_Explosion[nCnt].bUse = false;
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}
//=======================
// 爆発の描画処理
//=======================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Explosion[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_Explosion[nCnt].mtxWorld._11 = mtxView._11;
			g_Explosion[nCnt].mtxWorld._12 = mtxView._21;
			g_Explosion[nCnt].mtxWorld._13 = mtxView._31;
			g_Explosion[nCnt].mtxWorld._21 = mtxView._12;
			g_Explosion[nCnt].mtxWorld._22 = mtxView._22;
			g_Explosion[nCnt].mtxWorld._23 = mtxView._32;
			g_Explosion[nCnt].mtxWorld._31 = mtxView._13;
			g_Explosion[nCnt].mtxWorld._32 = mtxView._23;
			g_Explosion[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Explosion[nCnt].pos.x, g_Explosion[nCnt].pos.y, g_Explosion[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Explosion[nCnt].mtxWorld, &g_Explosion[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureExplosion[0]);

			//ポリゴンを描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//===================
// 爆発の設定
//===================
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == false)
		{
			g_Explosion[nCnt].pos = D3DXVECTOR3(pos.x, pos.y + 30, pos.z);
			//g_Explosion[nCnt].rot = rot;
			g_Explosion[nCnt].nCounterAnim = 0;
			g_Explosion[nCnt].nPattemAnim = 0;

			g_Explosion[nCnt].bUse = true;
			break;
		}
	}
}