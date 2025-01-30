//********************************************************
// 
// 衝撃波[impact.cpp]
// Author:Hatori
// 
//********************************************************

//*************
// インクルード
//*************
#include "impact.h"
#include "enemy.h"
#include "Player.h"

//*******************
// グローバル変数宣言
//*******************
RINGIMPACT g_Impact[MAX_IMPACT];

// ８とかのやつVERTICAL
// ２とかのやつHORIZON

//*******************
// 衝撃波の初期化処理
//*******************
void InitImpact(void)
{
	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		g_Impact[ImpactCount].Object.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Impact[ImpactCount].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Impact[ImpactCount].nLife = 0;
		g_Impact[ImpactCount].inringsize = 0;
		g_Impact[ImpactCount].outringsize = 0;
		g_Impact[ImpactCount].Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Impact[ImpactCount].AlphaDef = 0.0f;
		g_Impact[ImpactCount].bUse = false;
	}
}

//*****************
// 衝撃波の終了処理
//*****************
void UninitImpact(void)
{
	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		if (g_Impact[ImpactCount].pIdxBuffImpact != NULL)
		{
			g_Impact[ImpactCount].pIdxBuffImpact->Release();
			g_Impact[ImpactCount].pIdxBuffImpact = NULL;
		}
		if(g_Impact[ImpactCount].pVtxBuffImpact != NULL)
		{
			g_Impact[ImpactCount].pVtxBuffImpact->Release();
			g_Impact[ImpactCount].pVtxBuffImpact = NULL;
		}
		if (g_Impact[ImpactCount].pTextureImpact != NULL)
		{
			g_Impact[ImpactCount].pTextureImpact->Release();
			g_Impact[ImpactCount].pTextureImpact = NULL;
		}
	}
}
//*****************
// 衝撃波の更新処理
//*****************
void UpdateImpact(void)
{
	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		if (g_Impact[ImpactCount].bUse == true)
		{
			int nCnt = 0;

			//広げる処理
			g_Impact[ImpactCount].nLife--;
			g_Impact[ImpactCount].inringsize = g_Impact[ImpactCount].inringsize + g_Impact[ImpactCount].Speed;
			g_Impact[ImpactCount].outringsize = g_Impact[ImpactCount].outringsize + g_Impact[ImpactCount].Speed;

			VERTEX_3D* pVtx = NULL;
			// 頂点バッファをロック
			g_Impact[ImpactCount].pVtxBuffImpact->Lock(0, 0, (void**)&pVtx, 0);

			g_Impact[ImpactCount].col.a -= g_Impact[ImpactCount].AlphaDef;

			//内側
			for (int vertexcount = 0; vertexcount <= g_Impact[ImpactCount].Vertical; vertexcount++)
			{
				D3DXVECTOR3 MathNor;
				D3DXCOLOR localcol;
				localcol = g_Impact[ImpactCount].col;
				localcol.a -= g_Impact[ImpactCount].AlphaDef * 50;
				float ratioH = (-D3DX_PI * 2 / g_Impact[ImpactCount].Vertical) * vertexcount;
				pVtx[nCnt].tex = D3DXVECTOR2(0.5f * vertexcount, 0.5f);
				pVtx[nCnt].col = D3DXCOLOR(localcol);
				// 頂点座標の更新
				pVtx[nCnt].pos.x = 0.0f + sinf(ratioH) * g_Impact[ImpactCount].inringsize;
				pVtx[nCnt].pos.y = 0.0f;
				pVtx[nCnt].pos.z = 0.0f + cosf(ratioH) * g_Impact[ImpactCount].inringsize;
				MathNor = D3DXVECTOR3(pVtx[nCnt].pos.x - 0.0f, pVtx[nCnt].pos.y - 0.0f, pVtx[nCnt].pos.z - 0.0f);
				D3DXVec3Normalize(&pVtx[nCnt].nor, &MathNor);
				nCnt++;
			}

			//外側
			for (int vertexcount = 0; vertexcount <= g_Impact[ImpactCount].Vertical; vertexcount++)
			{
				D3DXVECTOR3 MathNor;
				float ratioH = (-D3DX_PI * 2 / g_Impact[ImpactCount].Vertical) * vertexcount;
				pVtx[nCnt].tex = D3DXVECTOR2(0.5f * vertexcount, 0.5f);
				pVtx[nCnt].col = D3DXCOLOR(g_Impact[ImpactCount].col);
				// 頂点座標の更新
				pVtx[nCnt].pos.x = 0.0f + sinf(ratioH) * g_Impact[ImpactCount].outringsize;
				pVtx[nCnt].pos.y = 0.0f;
				pVtx[nCnt].pos.z = 0.0f + cosf(ratioH) * g_Impact[ImpactCount].outringsize;

				//魔法なら
				if (g_Impact[ImpactCount].nType == IMPACTTYPE_SKILL)
				{
					pVtx[nCnt].pos.y = -PROFOUND;
				}

				MathNor = D3DXVECTOR3(pVtx[nCnt].pos.x - 0.0f, pVtx[nCnt].pos.y - 0.0f, pVtx[nCnt].pos.z - 0.0f);
				D3DXVec3Normalize(&pVtx[nCnt].nor, &MathNor);
				nCnt++;
			}

			// 頂点バッファをアンロック
			g_Impact[ImpactCount].pVtxBuffImpact->Unlock();

			//α値が0になったら使っていない状態にする
			if (g_Impact[ImpactCount].col.a < 0.0f)
			{
				g_Impact[ImpactCount].bUse = false;
			}

			//当たり判定
			switch (g_Impact[ImpactCount].nType)
			{
			case IMPACTTYPE_NORMAL:
				//collisionImpact(ImpactCount);
				break;

			case IMPACTTYPE_ENEMY:
				//collisionImpactPlayer(ImpactCount);
				break;

			}
		}
	}
}
//*****************
// 衝撃波の描画処理
//*****************
void DrawImpact(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		//魔法なら
		if (g_Impact[ImpactCount].nType == IMPACTTYPE_SKILL)
		{
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		}

		if (g_Impact[ImpactCount].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Impact[ImpactCount].Object.mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Impact[ImpactCount].Object.Rot.y, g_Impact[ImpactCount].Object.Rot.x, g_Impact[ImpactCount].Object.Rot.z);
			D3DXMatrixMultiply(&g_Impact[ImpactCount].Object.mtxWorld, &g_Impact[ImpactCount].Object.mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Impact[ImpactCount].Object.Pos.x, g_Impact[ImpactCount].Object.Pos.y, g_Impact[ImpactCount].Object.Pos.z);
			D3DXMatrixMultiply(&g_Impact[ImpactCount].Object.mtxWorld, &g_Impact[ImpactCount].Object.mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Impact[ImpactCount].Object.mtxWorld);
			// 頂点バッファをデバイスからデータストリームに設定
			pDevice->SetStreamSource(0, g_Impact[ImpactCount].pVtxBuffImpact, 0, sizeof(VERTEX_3D));
			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_Impact[ImpactCount].pIdxBuffImpact);
			// テクスチャの設定
			pDevice->SetTexture(0, g_Impact[ImpactCount].pTextureImpact);
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Impact[ImpactCount].Vertex, 0, g_Impact[ImpactCount].Polygone);
		}

		if (g_Impact[ImpactCount].nType == IMPACTTYPE_SKILL)
		{
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		}
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************
// 衝撃波の設定処理
//*****************
void SetImpact(IMPACTTYPE nType, D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float inringsize,float outringsize, int Horizon, int Vertical,float Speed, float RotY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得処理

	for (int ImpactCount = 0; ImpactCount < MAX_IMPACT; ImpactCount++)
	{
		if (g_Impact[ImpactCount].bUse == false)
		{
			g_Impact[ImpactCount].bUse = true;

			g_Impact[ImpactCount].nLife = nLife;
			g_Impact[ImpactCount].nType = nType;
			g_Impact[ImpactCount].Speed = Speed;
			g_Impact[ImpactCount].AlphaDef = 1.0f / nLife;
			g_Impact[ImpactCount].Object.Pos = pos;
			g_Impact[ImpactCount].Horizon = Horizon;
			g_Impact[ImpactCount].Vertical = Vertical;
			g_Impact[ImpactCount].Vertex = (Vertical + 1) * (Horizon);
			g_Impact[ImpactCount].Polygone = (Vertical) * 2;
			g_Impact[ImpactCount].IndxVertex = (Vertical + 1) * (Horizon);
			g_Impact[ImpactCount].inringsize = inringsize;
			g_Impact[ImpactCount].outringsize = outringsize;
			g_Impact[ImpactCount].col = col;
			g_Impact[ImpactCount].Object.Rot.y = RotY;

			// 魔法のとき角度を変える
			if (g_Impact[ImpactCount].nType == IMPACTTYPE_SKILL)
			{
				g_Impact[ImpactCount].Object.Rot.x = - D3DX_PI * 0.5f;
			}

			////テクスチャの読み込み
			//D3DXCreateTextureFromFile(pDevice,
			//	IMPACTTEX[0],
			//	&g_Impact[ImpactCount].pTextureImpact);

			// 頂点バッファの生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Impact[ImpactCount].Vertex,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,		// 頂点フォーマット
				D3DPOOL_MANAGED,
				&g_Impact[ImpactCount].pVtxBuffImpact, NULL);

			VERTEX_3D* pVtx = NULL;
			// 頂点バッファをロック
			g_Impact[ImpactCount].pVtxBuffImpact->Lock(0, 0, (void**)&pVtx, 0);

			int nCnt = 0;

			for (int vertexcount = 0; vertexcount <= g_Impact[ImpactCount].Vertical; vertexcount++)
			{
				D3DXVECTOR3 MathNor;
				float ratioH = (-D3DX_PI * 2 / g_Impact[ImpactCount].Vertical) * vertexcount;
				pVtx[nCnt].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[nCnt].col = D3DXCOLOR(col);
				// 頂点座標の更新
				pVtx[nCnt].pos.x = g_Impact[ImpactCount].Object.Pos.x + sinf(ratioH) * inringsize;
				pVtx[nCnt].pos.y = 0.0f;
				pVtx[nCnt].pos.z = g_Impact[ImpactCount].Object.Pos.z + cosf(ratioH) * inringsize;
				//MathNor = D3DXVECTOR3(pVtx[nCnt].pos.x - 0.0f, pVtx[nCnt].pos.y - 0.0f, pVtx[nCnt].pos.z - 0.0f);
				//D3DXVec3Normalize(&pVtx[nCnt].nor, &MathNor);
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				nCnt++;
			}
			for (int vertexcount = 0; vertexcount <= g_Impact[ImpactCount].Vertical; vertexcount++)
			{
				D3DXVECTOR3 MathNor;
				float ratioH = (-D3DX_PI * 2 / g_Impact[ImpactCount].Vertical) * vertexcount;
				pVtx[nCnt].tex = D3DXVECTOR2(1.0f,1.0f);
				pVtx[nCnt].col = D3DXCOLOR(col);
				// 頂点座標の更新
				pVtx[nCnt].pos.x = g_Impact[ImpactCount].Object.Pos.x + sinf(ratioH) * outringsize;
				pVtx[nCnt].pos.y = 0.0f;
				pVtx[nCnt].pos.z = g_Impact[ImpactCount].Object.Pos.z + cosf(ratioH) * outringsize;

				//MathNor = D3DXVECTOR3(pVtx[nCnt].pos.x - 0.0f, pVtx[nCnt].pos.y - 0.0f, pVtx[nCnt].pos.z - 0.0f);
				//D3DXVec3Normalize(&pVtx[nCnt].nor, &MathNor);
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				nCnt++;
			}

			// 頂点バッファをアンロック
			g_Impact[ImpactCount].pVtxBuffImpact->Unlock();

			// インデックスバッファの生成
			pDevice->CreateIndexBuffer(sizeof(WORD) * g_Impact[ImpactCount].IndxVertex,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_Impact[ImpactCount].pIdxBuffImpact,
				NULL);

			WORD* pIdx = NULL;
			// 頂点バッファをロック
			g_Impact[ImpactCount].pIdxBuffImpact->Lock(0, 0, (void**)&pIdx, 0);

			int Indx = Vertical + 1;	// スタート地点
			int Indx1 = 0;			// ゼロからスタートするやつ
			int Indx2 = 0;			// 配列

			for (int IndxCount1 = 0; IndxCount1 <= Vertical; IndxCount1++)
			{
				pIdx[Indx2] = Indx;

				pIdx[Indx2 + 1] = Indx1;

				// 配列ずらす
				Indx2 += 2;
				Indx++;
				Indx1++;
			}

			// 頂点バッファをアンロック
			g_Impact[ImpactCount].pIdxBuffImpact->Unlock();

			break;
		}
	}
}
//void collisionImpact(int Indx)
//{
//	ENEMY* pEnemy = GetEnemy();
//	Player* pPlayer = GetPlayer();
//	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++,pEnemy++)
//	{
//		if (pEnemy->bHit == false && pEnemy->bUse == true && pEnemy->Object.Pos.y - 1.0f <= g_Impact[Indx].Object.Pos.y)
//		{
//			float DistanceX = g_Impact[Indx].Object.mtxWorld._41 - pEnemy->Object.mtxWorld._41;
//			float DistanceZ = g_Impact[Indx].Object.mtxWorld._43 - pEnemy->Object.mtxWorld._43;
//			float Distance = (DistanceX * DistanceX) + (DistanceZ * DistanceZ);
//			float fInLength = g_Impact[Indx].inringsize + pEnemy->Radius;
//			fInLength = fInLength * fInLength;
//			float fOutLength = g_Impact[Indx].outringsize + pEnemy->Radius;
//			fOutLength = fOutLength * fOutLength;
//			float Atack = pPlayer->Status.Atack * 0.1f;
//			if (Distance > fInLength && Distance < fOutLength && pEnemy->state != ENEMYSTATE_KNOCKUP)
//			{
//				D3DXVECTOR3 VecKnock;
//				VecKnock = pEnemy->Object.Pos - g_Impact[Indx].Object.Pos;
//				D3DXVec3Normalize(&VecKnock, &VecKnock);
//				VecKnock.y = 0.0f;
//				pEnemy->move = VecKnock;
//				HitEnemy(Atack, EnemyCount);
//			}
//		}
//	}
//}
//void collisionImpactPlayer(int Indx)
//{
//	ENEMY* pEnemy = GetEnemy();
//	Player* pPlayer = GetPlayer();
//	if (pPlayer->state != PLAYERSTATE_KNOCKUP && pPlayer->pos.y - 0.5f <= g_Impact[Indx].Object.Pos.y)
//	{
//		float DistanceX = g_Impact[Indx].Object.mtxWorld._41 - pEnemy->Object.mtxWorld._41;
//		float DistanceZ = g_Impact[Indx].Object.mtxWorld._43 - pEnemy->Object.mtxWorld._43;
//		float Distance = (DistanceX * DistanceX) + (DistanceZ * DistanceZ);
//		float fInLength = g_Impact[Indx].inringsize + pPlayer->PlayerXRadius;
//		fInLength = fInLength * fInLength;
//		float fOutLength = g_Impact[Indx].outringsize + pPlayer->PlayerXRadius;
//		fOutLength = fOutLength * fOutLength;
//		if (Distance > fInLength && Distance < fOutLength)
//		{
//			D3DXVECTOR3 VecKnock;
//			VecKnock = pPlayer->pos - g_Impact[Indx].Object.Pos;
//			D3DXVec3Normalize(&VecKnock, &VecKnock);
//			VecKnock.y = 10.0f;
//			pPlayer->move = VecKnock;
//			pPlayer->state = PLAYERSTATE_KNOCKUP;
//			pPlayer->StateCount = 50;
//			pPlayer->Status.Hp -= 5.0f;
//		}
//	}
//}