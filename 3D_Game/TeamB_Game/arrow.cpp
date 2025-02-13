//=======================================================
// 
// 矢印[arrow.cpp]
// Author:Rio Ohno
// 
//=======================================================

//インクルード
#include "arrow.h"

//グローバル変数宣言
Arrow g_Arrow;

//===================
//矢印の初期化処理
//===================
void InitArrow()
{
	//各種初期化
	g_Arrow.Destpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的位置
	g_Arrow.Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的への向き
	g_Arrow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
	g_Arrow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
	g_Arrow.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//色
	g_Arrow.VtxBuff = { NULL };//頂点情報
	g_Arrow.tex = { NULL };//テクスチャポインタ
	g_Arrow.fHeight = 0.0;//ポリゴンの高さ
	g_Arrow.fWidth = 0.0f;//ポリゴンの幅
	g_Arrow.fRadius = 0.0f;//posからどれだけ離すか
	g_Arrow.bUse = false;//使用していない状態にする
}

//===================
//矢印の終了処理
//===================
void UninitArrow()
{
	//テクスチャの破棄
	if (g_Arrow.tex != NULL)
	{
		g_Arrow.tex->Release();
		g_Arrow.tex = NULL;
	}

	//頂点バッファの破棄
	if (g_Arrow.VtxBuff != NULL)
	{
		g_Arrow.VtxBuff->Release();
		g_Arrow.VtxBuff = NULL;
	}
}

//===================
//矢印の更新処理
//===================
void UpdateArrow()
{
		//目的地へのベクトル
		D3DXVECTOR3 vec = g_Arrow.Destpos - g_Arrow.pos;
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
		g_Arrow.Destrot.y = fAngle;

		rotData = g_Arrow.Destrot.y - g_Arrow.rot.y;

		// 角度の近道
		if (rotData >= D3DX_PI)
		{
			g_Arrow.rot.y += D3DX_PI * 2.0f;
		}
		else if (rotData <= -D3DX_PI)
		{
			g_Arrow.rot.y -= D3DX_PI * 2.0f;
		}

		//向きの反映
		g_Arrow.rot.y += (g_Arrow.Destrot.y - g_Arrow.rot.y) * 0.1f;
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

	if (g_Arrow.bUse == true)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Arrow.mtxWorld);

		//向きを反転
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Arrow.rot.y, g_Arrow.rot.x, g_Arrow.rot.z);
		D3DXMatrixMultiply(&g_Arrow.mtxWorld, &g_Arrow.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Arrow.pos.x, g_Arrow.pos.y, g_Arrow.pos.z);
		D3DXMatrixMultiply(&g_Arrow.mtxWorld, &g_Arrow.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Arrow.mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_Arrow.VtxBuff, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_Arrow.tex);

		//ポリゴンを描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//===================
//矢印の設定処理
//===================
void SetArrow(D3DXVECTOR3 DestPos, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, float fRadius)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	HRESULT hresult;

	if (g_Arrow.bUse == false)
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_Arrow.VtxBuff,
			NULL);

		//テクスチャの読込
		hresult = D3DXCreateTextureFromFile(pDevice,
			ARROW_TEX,
			&g_Arrow.tex);

		if (FAILED(hresult))
		{
			return;
		}

		//各種設定
		g_Arrow.Destpos = DestPos;
		g_Arrow.pos = pos;
		g_Arrow.col = col;
		g_Arrow.fWidth = fWidth;
		g_Arrow.fHeight = fHeight;
		g_Arrow.fRadius = fRadius;
		g_Arrow.bUse = true;

		//向きの設定------------------------------------------------------------
		D3DXVECTOR3 vec = g_Arrow.Destpos - g_Arrow.pos;
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
		g_Arrow.rot.y = fAngle;

		//-------------------------------------------------------------------------

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_Arrow.VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(- g_Arrow.fWidth * 0.5f, 1.0f, (g_Arrow.fHeight + g_Arrow.fRadius));
		pVtx[1].pos = D3DXVECTOR3(g_Arrow.fWidth * 0.5f, 1.0f, (g_Arrow.fHeight + g_Arrow.fRadius));
		pVtx[2].pos = D3DXVECTOR3(- g_Arrow.fWidth * 0.5f, 1.0f,  g_Arrow.fRadius);
		pVtx[3].pos = D3DXVECTOR3(g_Arrow.fWidth * 0.5f, 1.0f,  g_Arrow.fRadius);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//色の設定
		pVtx[0].col = g_Arrow.col;
		pVtx[1].col = g_Arrow.col;
		pVtx[2].col = g_Arrow.col;
		pVtx[3].col = g_Arrow.col;

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロック　
		g_Arrow.VtxBuff->Unlock();
	}
}

//===================
//矢印の位置の更新処理
//===================
void SetPositonArrow(D3DXVECTOR3 pos)
{
	g_Arrow.pos = D3DXVECTOR3(pos.x, g_Arrow.pos.y, pos.z);
}
