//=========================================================
// 
// 敵のHPゲージ[HPgauge.cpp]
// Aothor:Rio Ohno
// 
//=========================================================

//インクルード
#include"HPgauge.h"

//グローバル変数宣言
HPgauge g_HPgauge[MAX_HPGAUGE];
LPDIRECT3DTEXTURE9 pTextureHPgauge[HPGAUGETYPE_MAX] = { NULL };
//LPDIRECT3DVERTEXBUFFER9 pVtxBuffHPgauge = {};

//====================
// 初期化処理
//====================
void InitHPgauge()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntTex = 0; nCntTex < MAX_POLY; nCntTex++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			HPGAUGETEX[nCntTex],
			&pTextureHPgauge[nCntTex]);
	}

	for (int nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		//構造体の初期化
		g_HPgauge[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置
		g_HPgauge[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き
		g_HPgauge[nCnt].fNowHP = 0.0f;											// 現在のHP
		g_HPgauge[nCnt].fMaxHP = 0.0f;											// 最大のHP
		g_HPgauge[nCnt].bUse = false;											// 使用していない状態にする
																				   
		g_HPgauge[nCnt].poly[0].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);		// 赤ゲージの色
		g_HPgauge[nCnt].poly[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);		// ゲージの色
		g_HPgauge[nCnt].poly[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// 枠の色

		g_HPgauge[nCnt].poly[0].type = HPGAUGETYPE_RED;
		g_HPgauge[nCnt].poly[1].type = HPGAUGETYPE_NORMAL;
		g_HPgauge[nCnt].poly[2].type = HPGAUGETYPE_NONE;
	}
}

//====================
//終了処理
//====================
void UninitHPgauge()
{
	for (int nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		//頂点バッファの破棄
		if (g_HPgauge[nCnt].pVtxBuff != NULL)
		{
			g_HPgauge[nCnt].pVtxBuff->Release();
			g_HPgauge[nCnt].pVtxBuff = NULL;
		}
	}

	//テクスチャの破棄
	for (int nCnt = 0; nCnt < HPGAUGETYPE_MAX; nCnt++)
	{
		if (pTextureHPgauge[nCnt] != NULL)
		{
			pTextureHPgauge[nCnt]->Release();
			pTextureHPgauge[nCnt] = NULL;
		}
	}
}

//====================
//更新処理
//====================
void UpdateHPgauge()
{

}

//====================
//描画処理
//====================
void DrawHPgauge()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////計算用マトリックス
	//D3DXMATRIX mtxRot, mtxTrans;

	//ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		if (g_HPgauge[nCnt].bUse == true)
		{
			for (int nCntPoly = 0; nCntPoly < MAX_POLY; nCntPoly++)
			{
				//計算用マトリックス
				D3DXMATRIX mtxRot, mtxTrans;
				D3DXMATRIX mtxView;

				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_HPgauge[nCnt].poly[nCntPoly].mtxWorld);

				//ビューマトリックス取得
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//カメラの逆行列を設定
				g_HPgauge[nCnt].poly[nCntPoly].mtxWorld._11 = mtxView._11;
				g_HPgauge[nCnt].poly[nCntPoly].mtxWorld._12 = mtxView._21;
				g_HPgauge[nCnt].poly[nCntPoly].mtxWorld._13 = mtxView._31;
				g_HPgauge[nCnt].poly[nCntPoly].mtxWorld._21 = mtxView._12;
				g_HPgauge[nCnt].poly[nCntPoly].mtxWorld._22 = mtxView._22;
				g_HPgauge[nCnt].poly[nCntPoly].mtxWorld._23 = mtxView._32;
				g_HPgauge[nCnt].poly[nCntPoly].mtxWorld._31 = mtxView._13;
				g_HPgauge[nCnt].poly[nCntPoly].mtxWorld._32 = mtxView._23;
				g_HPgauge[nCnt].poly[nCntPoly].mtxWorld._33 = mtxView._33;

				// 向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_HPgauge[nCnt].rot.y, g_HPgauge[nCnt].rot.x, g_HPgauge[nCnt].rot.z);
				D3DXMatrixMultiply(&g_HPgauge[nCnt].poly[nCntPoly].mtxWorld, &g_HPgauge[nCnt].poly[nCntPoly].mtxWorld, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_HPgauge[nCnt].pos.x, g_HPgauge[nCnt].pos.y, g_HPgauge[nCnt].pos.z);
				D3DXMatrixMultiply(&g_HPgauge[nCnt].poly[nCntPoly].mtxWorld, &g_HPgauge[nCnt].poly[nCntPoly].mtxWorld, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_HPgauge[nCnt].poly[nCntPoly].mtxWorld);

				//頂点バッファをデータストリームに設定
				pDevice->SetStreamSource(0, g_HPgauge[nCnt].pVtxBuff, 0, sizeof(VERTEX_3D));

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				//テクスチャの設定
				pDevice->SetTexture(0, pTextureHPgauge[g_HPgauge[nCnt].poly[nCntPoly].type]);

				//ポリゴンを描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPoly, 2);
			}
		}
	}

	//ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//====================
//設定処理
//====================
int SetHPgauge(D3DXVECTOR3 pos,D3DXVECTOR2 scale,float MaxHP)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;
	int nCnt = 0;

	for (nCnt = 0; nCnt < MAX_HPGAUGE; nCnt++)
	{
		if (g_HPgauge[nCnt].bUse == false)
		{
			//各種設定
			g_HPgauge[nCnt].pos = pos;								// 位置

			g_HPgauge[nCnt].fMaxHP = MaxHP;							// 最大HP

			//頂点バッファの生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_POLY,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_HPgauge[nCnt].pVtxBuff,
				NULL);


			//頂点バッファをロック
			g_HPgauge[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//頂点情報の設定
			for (int nCntPoly = 0; nCntPoly < MAX_POLY; nCntPoly++)
			{
				//真ん中を算出
				g_HPgauge[nCnt].poly[nCntPoly].center = D3DXVECTOR2((float)scale.x * 0.5f, scale.y * 0.5f);

				//各種設定
				g_HPgauge[nCnt].poly[nCntPoly].fWidth = (scale.x - g_HPgauge[nCnt].poly[nCntPoly].center.x);			// 右端
				g_HPgauge[nCnt].poly[nCntPoly].fMaxGauge = scale.x;														// 幅

				//頂点情報の設定
				pVtx[0].pos.x = -g_HPgauge[nCnt].poly[nCntPoly].center.x;
				pVtx[0].pos.y = scale.y;
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = (scale.x - g_HPgauge[nCnt].poly[nCntPoly].center.x);
				pVtx[1].pos.y = scale.y;
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = -g_HPgauge[nCnt].poly[nCntPoly].center.x;
				pVtx[2].pos.y = 0.0f;
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = (scale.x - g_HPgauge[nCnt].poly[nCntPoly].center.x);
				pVtx[3].pos.y = 0.0f;
				pVtx[3].pos.z = 0.0f;

				//法線ベクトルの設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				//カラーの設定
				pVtx[0].col = g_HPgauge[nCnt].poly[nCntPoly].col;
				pVtx[1].col = g_HPgauge[nCnt].poly[nCntPoly].col;
				pVtx[2].col = g_HPgauge[nCnt].poly[nCntPoly].col;
				pVtx[3].col = g_HPgauge[nCnt].poly[nCntPoly].col;

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

				pVtx += 4;
			}

			//頂点バッファをアンロック
			g_HPgauge[nCnt].pVtxBuff->Unlock();

			//使用している状態にする
			g_HPgauge[nCnt].bUse = true;
			break;
		}
	}
	//ゲージのインデクスを返す
	return nCnt;
}

//====================
//位置の設定処理
//====================
void SetPositionHPgauge(int Indx,D3DXVECTOR3 pos)
{
	g_HPgauge[Indx].pos = pos;
}

//====================
//ゲージの減少処理
//====================
void HPgaugeDeff(int Indx, float NowHP)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	if (g_HPgauge[Indx].bUse == true)
	{
		//比率を計算する
		float ratio = NowHP / g_HPgauge[Indx].fMaxHP;

		g_HPgauge[Indx].poly[1].fWidth = (g_HPgauge[Indx].poly[1].fMaxGauge * ratio - g_HPgauge[Indx].poly[1].center.x);

		//頂点バッファをロック
		g_HPgauge[Indx].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//ポインタを進める
		pVtx += 4;

		pVtx[1].pos.x = g_HPgauge[Indx].poly[1].fWidth;
		pVtx[3].pos.x = g_HPgauge[Indx].poly[1].fWidth;

		//頂点バッファをアンロック
		g_HPgauge[Indx].pVtxBuff->Unlock();
	}
}

//====================
//赤ゲージの減少処理
//====================
void RedgaugeDeff(int Indx, float NowHP)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//使用している状態なら
	if (g_HPgauge[Indx].bUse == true)
	{
		//比率を計算する
		float ratio = NowHP / g_HPgauge[Indx].fMaxHP;

		//目標の値を計算する
		float fWidth = (g_HPgauge[Indx].poly[0].fMaxGauge * ratio - g_HPgauge[Indx].poly[0].center.x);

		//差分を計算する
		float fDiff = g_HPgauge[Indx].poly[0].fWidth - fWidth;

		//徐々に減らす
		g_HPgauge[Indx].poly[0].fWidth -= fDiff * 0.01f;

		//頂点バッファをロック
		g_HPgauge[Indx].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[1].pos.x = g_HPgauge[Indx].poly[0].fWidth;
		pVtx[3].pos.x = g_HPgauge[Indx].poly[0].fWidth;

		//頂点バッファをアンロック
		g_HPgauge[Indx].pVtxBuff->Unlock();
	}
}

//====================
//HPゲージを消す
//====================
void DeleteHPGuage(int Indx)
{
	g_HPgauge[Indx].bUse = false;
}