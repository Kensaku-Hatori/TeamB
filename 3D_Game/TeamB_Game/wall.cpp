//================================
//
// ポリゴン表示処理[wall.cpp]
// Author:kaiti
//
//================================
#include "wall.h"
#include "player.h"
#include "polygon.h"
//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
LPDIRECT3DTEXTURE9 g_apTextureWall[1] = {};
Wall g_wall[MAX_WALL];

//=======================
// ポリゴンの初期化処理
//=======================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_wall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_wall[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\kabe.jpg", &g_apTextureWall[0]); //1

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffWall,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_wall[nCnt].pos.x - POLYGON_X, g_wall[nCnt].pos.y + WALL_HEIGHT, g_wall[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_wall[nCnt].pos.x + POLYGON_X, g_wall[nCnt].pos.y + WALL_HEIGHT, g_wall[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_wall[nCnt].pos.x - POLYGON_X, g_wall[nCnt].pos.y - WALL_HEIGHT, g_wall[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_wall[nCnt].pos.x + POLYGON_X, g_wall[nCnt].pos.y - WALL_HEIGHT, g_wall[nCnt].pos.z);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(4.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(4.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();
}
//======================
// ポリゴンの終了処理
//======================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_apTextureWall[0] != NULL)
	{
		g_apTextureWall[0]->Release();
		g_apTextureWall[0] = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}
//=====================
// ポリゴンの更新処理
//=====================
void UpdateWall(void)
{

}
//=====================
// ポリゴンの描画処理
//=====================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_wall[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_wall[nCnt].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[nCnt].rot.y, g_wall[nCnt].rot.x, g_wall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_wall[nCnt].mtxWorld, &g_wall[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_wall[nCnt].pos.x, g_wall[nCnt].pos.y, g_wall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_wall[nCnt].mtxWorld, &g_wall[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_wall[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureWall[0]);

			//ポリゴンを描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//=============
// 壁の設定
//=============
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float a)
{
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt;
	for (nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_wall[nCnt].bUse == false)
		{
			g_wall[nCnt].pos = pos;
			g_wall[nCnt].rot = rot;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, a);
			pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, a);
			pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, a);
			pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, a);

			g_wall[nCnt].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();
}
//====================
// 壁との当たり判定
//====================
void CollisionWall(void)
{
	D3DXVECTOR3 aPos[2];

	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;

	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_wall[nCnt].bUse == true)
		{
			aPos[0].x = g_wall[nCnt].pos.x - cosf(g_wall[nCnt].rot.y) * WALL_WIDTH;
			aPos[0].z = g_wall[nCnt].pos.z + sinf(g_wall[nCnt].rot.y) * WALL_WIDTH;

			aPos[1].x = g_wall[nCnt].pos.x + cosf(g_wall[nCnt].rot.y) * WALL_WIDTH;
			aPos[1].z = g_wall[nCnt].pos.z - sinf(g_wall[nCnt].rot.y) * WALL_WIDTH;

			//ベクトルA
			vecA = aPos[1] - aPos[0];
			//ベクトルB
			vecB = pPlayer->pos - aPos[0];

			float fvec = (vecA.z * vecB.x) - (vecA.x * vecB.z);

			if (fvec < 0)
			{
				pPlayer->pos = pPlayer->posOld;
			}
		}
	}
}
//============
// 壁の取得
//============
Wall* GetWall(void)
{
	return &g_wall[0];
}