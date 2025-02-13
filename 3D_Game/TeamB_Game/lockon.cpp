//================================
//
// ロックオン処理[Lockon.cpp]
// Author:kaiti
//
//================================
#include "lockon.h"
#include "player.h"
#include "enemy.h"
//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLockon = NULL;
LPDIRECT3DTEXTURE9 g_apTextureLockon[1] = {};

D3DXVECTOR3 g_posLockon;//位置

//=======================
// ポリゴンの初期化処理
//=======================
void InitLockon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	g_posLockon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yuka00.jpg", &g_apTextureLockon[0]); //1

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffLockon,
		                        NULL);
	VERTEX_2D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLockon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffLockon->Unlock();
}
//====================
// ポリゴンの終了処理
//====================
void UninitLockon(void)
{
	//テクスチャの破棄
	if (g_apTextureLockon[0] != NULL)
	{
		g_apTextureLockon[0]->Release();
		g_apTextureLockon[0] = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLockon != NULL)
	{
		g_pVtxBuffLockon->Release();
		g_pVtxBuffLockon = NULL;
	}
}
//=====================
// ポリゴンの更新処理
//=====================
void UpdateLockon(void)
{
	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLockon->Lock(0, 0, (void**)&pVtx, 0);

	if (pPlayer->bLockOn == true)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}
	else
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffLockon->Unlock();
}
//====================
// ポリゴンの描画処理
//====================
void DrawLockon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLockon, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureLockon[0]);

	//ポリゴンを描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=====================================
// 敵が視界にいるかどうか(ロックオン)
//=====================================
bool IsEnemyInsight(void)
{
	Player* pPlayer = GetPlayer();
	ENEMY* pEnemy = GetEnemy();

	D3DXVECTOR3 playerFront;

	playerFront.x = -sinf(pPlayer->rot.y);
	playerFront.y = 0.0f;
	playerFront.z = -cosf(pPlayer->rot.y);

	D3DXVECTOR3 toEnemy;

	bool bLock = false;

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (pEnemy[EnemyCount].bUse == true)
		{
			toEnemy.x = pEnemy[EnemyCount].Object.Pos.x - pPlayer->pos.x;
			toEnemy.y = 0.0f;
			toEnemy.z = pEnemy[EnemyCount].Object.Pos.z - pPlayer->pos.z;

			D3DXVec3Normalize(&playerFront, &playerFront);

			D3DXVec3Normalize(&toEnemy, &toEnemy);

			float dotProduct = D3DXVec3Dot(&playerFront, &toEnemy);

			if (dotProduct > cosf(pPlayer->fSightAngle * 0.5f))
			{
				float distanceSquared =
					(pPlayer->pos.x - pEnemy[EnemyCount].Object.Pos.x) * (pPlayer->pos.x - pEnemy[EnemyCount].Object.Pos.x) +
					(pPlayer->pos.y - pEnemy[EnemyCount].Object.Pos.y) * (pPlayer->pos.y - pEnemy[EnemyCount].Object.Pos.y) +
					(pPlayer->pos.z - pEnemy[EnemyCount].Object.Pos.z) * (pPlayer->pos.z - pEnemy[EnemyCount].Object.Pos.z);

				if (distanceSquared <= pPlayer->fSightRange * pPlayer->fSightRange)
				{
					bLock = EnemyDistanceSort(EnemyCount);
				}
			}
		}
	}
	return bLock;
}

//===============================
// 一番近い敵を判別
//===============================
bool EnemyDistanceSort(int EnemyCount)
{
	Player* pPlayer = GetPlayer();

	ENEMY* pEnemy = GetEnemy();

	bool bLock = true;
	//敵との距離
	pEnemy[EnemyCount].fDistance = sqrtf(((pEnemy[EnemyCount].Object.Pos.x - pPlayer->pos.x) * (pEnemy[EnemyCount].Object.Pos.x - pPlayer->pos.x))
									   + ((pEnemy[EnemyCount].Object.Pos.y - pPlayer->pos.y) * (pEnemy[EnemyCount].Object.Pos.y - pPlayer->pos.y))
									   + ((pEnemy[EnemyCount].Object.Pos.z - pPlayer->pos.z) * (pEnemy[EnemyCount].Object.Pos.z - pPlayer->pos.z)));

	pEnemy[pPlayer->nLockOnEnemy].fDistance = sqrtf(((pEnemy[pPlayer->nLockOnEnemy].Object.Pos.x - pPlayer->pos.x) * (pEnemy[pPlayer->nLockOnEnemy].Object.Pos.x - pPlayer->pos.x))
											  	  + ((pEnemy[pPlayer->nLockOnEnemy].Object.Pos.y - pPlayer->pos.y) * (pEnemy[pPlayer->nLockOnEnemy].Object.Pos.y - pPlayer->pos.y))
											  	  + ((pEnemy[pPlayer->nLockOnEnemy].Object.Pos.z - pPlayer->pos.z) * (pEnemy[pPlayer->nLockOnEnemy].Object.Pos.z - pPlayer->pos.z)));

	float RADIUS = (pPlayer->fDistance + pEnemy[EnemyCount].Radius) * (pPlayer->fDistance + pEnemy[EnemyCount].Radius);

	if (pEnemy[EnemyCount].fDistance <= RADIUS)
	{
		if (pEnemy[EnemyCount].fDistance <= pEnemy[pPlayer->nLockOnEnemy].fDistance)
		{
			pPlayer->nLockOnEnemy = EnemyCount;
		}
	}
	return bLock;
}
