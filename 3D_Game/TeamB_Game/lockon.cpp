//================================
//
// ロックオン処理[Lockon.cpp]
// Author:kaiti
//
//================================
#include "lockon.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "boss.h"
//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLockon = NULL;
LPDIRECT3DTEXTURE9 g_apTextureLockon[1] = {};

Lockon g_Lockon;
LockonEnemy g_LockonEnemy;

//=======================
// ポリゴンの初期化処理
//=======================
void InitLockon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	g_Lockon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Lockon.bUse = false;

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\lockon.png", &g_apTextureLockon[0]); //1

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffLockon,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLockon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Lockon.pos.x - LOCKON_SIZE, g_Lockon.pos.y + LOCKON_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Lockon.pos.x + LOCKON_SIZE, g_Lockon.pos.y + LOCKON_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Lockon.pos.x - LOCKON_SIZE, g_Lockon.pos.y - LOCKON_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Lockon.pos.x + LOCKON_SIZE, g_Lockon.pos.y - LOCKON_SIZE, 0.0f);
	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
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
	Camera* pCamera = GetCamera();				//カメラの情報取得
	Player* pPlayer = GetPlayer();
	ENEMY* pEnemy = GetEnemy();
	BOSS* pBoss = GetBoss();

	if (g_LockonEnemy.type == 0)
	{
		g_LockonEnemy.pos = pEnemy[pPlayer->nLockOnEnemy].Object.Pos;
	}
	else if(g_LockonEnemy.type == 1)
	{
		g_LockonEnemy.pos = pBoss->Object.Pos;
	}

	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLockon->Lock(0, 0, (void**)&pVtx, 0);

	g_Lockon.bUse = pPlayer->bLockOn;

	if (g_Lockon.bUse == true)
	{
		g_Lockon.pos = g_LockonEnemy.pos;
		g_Lockon.pos.y += 30.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//距離による解除
		float Dis = ((pPlayer->pos.x - g_Lockon.pos.x) * (pPlayer->pos.x - g_Lockon.pos.x))
				  + ((pPlayer->pos.y - g_Lockon.pos.y) * (pPlayer->pos.y - g_Lockon.pos.y))
				  + ((pPlayer->pos.z - g_Lockon.pos.z) * (pPlayer->pos.z - g_Lockon.pos.z));

		if (Dis >= pPlayer->fSightRange * pPlayer->fSightRange * 2)
		{
			pPlayer->bLockOn = false;
			pPlayer->bWantLockOn = false;
		}
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

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	if (g_Lockon.bUse == true)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Lockon.mtxWorld);

		D3DXMATRIX mtxView;
		//ビューマトリックス取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//カメラの逆行列を設定
		g_Lockon.mtxWorld._11 = mtxView._11;
		g_Lockon.mtxWorld._12 = mtxView._21;
		g_Lockon.mtxWorld._13 = mtxView._31;
		g_Lockon.mtxWorld._21 = mtxView._12;
		g_Lockon.mtxWorld._22 = mtxView._22;
		g_Lockon.mtxWorld._23 = mtxView._32;
		g_Lockon.mtxWorld._31 = mtxView._13;
		g_Lockon.mtxWorld._32 = mtxView._23;
		g_Lockon.mtxWorld._33 = mtxView._33;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Lockon.pos.x, g_Lockon.pos.y, g_Lockon.pos.z);
		D3DXMatrixMultiply(&g_Lockon.mtxWorld, &g_Lockon.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Lockon.mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffLockon, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureLockon[0]);

		//ポリゴンを描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//=====================================
// 敵が視界にいるかどうか(ロックオン)
//=====================================
bool IsEnemyInsight(D3DXVECTOR3 Pos, int type)
{
	Player* pPlayer = GetPlayer();

	D3DXVECTOR3 playerFront;

	playerFront.x = -sinf(pPlayer->rot.y);
	playerFront.y = 0.0f;
	playerFront.z = -cosf(pPlayer->rot.y);

	D3DXVECTOR3 toEnemy;

	bool bLock = false;

	toEnemy.x = Pos.x - pPlayer->pos.x;
	toEnemy.y = 0.0f;
	toEnemy.z = Pos.z - pPlayer->pos.z;

	D3DXVec3Normalize(&playerFront, &playerFront);

	D3DXVec3Normalize(&toEnemy, &toEnemy);

	float dotProduct = D3DXVec3Dot(&playerFront, &toEnemy);

	if (dotProduct > cosf(pPlayer->fSightAngle * 0.5f))
	{
		float distanceSquared =
			(pPlayer->pos.x - Pos.x) * (pPlayer->pos.x - Pos.x) +
			(pPlayer->pos.y - Pos.y) * (pPlayer->pos.y - Pos.y) +
			(pPlayer->pos.z - Pos.z) * (pPlayer->pos.z - Pos.z);

		if (distanceSquared <= pPlayer->fSightRange * pPlayer->fSightRange)
		{
			g_LockonEnemy.type = type;
			bLock = true;
		}
	}
	return bLock;
}

//===============================
// 一番近い敵を判別
//===============================
void EnemyDistanceSort(int EnemyCount)
{
	Player* pPlayer = GetPlayer();

	ENEMY* pEnemy = GetEnemy();

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
}
//
//
//
Lockon* GetLockOn(void)
{
	return &g_Lockon;
}