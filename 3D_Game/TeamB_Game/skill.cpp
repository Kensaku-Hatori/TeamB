//================================
//
// 弾処理[skill.cpp]
// Author:kaiti
//
//================================
#include "skill.h"
#include "shadow.h"
#include "explosion.h"
#include "player.h"
#include "effect.h"
#include "wall.h"
#include "particle.h"
#include "enemy.h"
#include "impact.h"
#include "boss.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkill = NULL;
LPDIRECT3DTEXTURE9 g_apTextureSkill = {};
Skill g_Skill[MAX_SKILL];

//=========================
// 弾の初期化処理
//=========================
void InitSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		g_Skill[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Skill[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Skill[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Skill[nCnt].nLife = SKILL_LIFE;
		g_Skill[nCnt].fPower = 0.0f;
		g_Skill[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_apTextureSkill); //1

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SKILL,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffSkill,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSkill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x - SKILL_SIZE, g_Skill[nCnt].pos.y + SKILL_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x + SKILL_SIZE, g_Skill[nCnt].pos.y + SKILL_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x - SKILL_SIZE, g_Skill[nCnt].pos.y - SKILL_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x + SKILL_SIZE, g_Skill[nCnt].pos.y - SKILL_SIZE, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffSkill->Unlock();
}
//=======================
// 弾の終了処理
//=======================
void UninitSkill(void)
{
	//テクスチャの破棄
	if (g_apTextureSkill != NULL)
	{
		g_apTextureSkill->Release();
		g_apTextureSkill = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSkill != NULL)
	{
		g_pVtxBuffSkill->Release();
		g_pVtxBuffSkill = NULL;
	}
}
//=======================
// 弾の更新処理
//=======================
void UpdateSkill(void)
{
	//プレイヤーの情報取得
	Player* pPlayer = GetPlayer();
	//影の情報取得
	Shadow* pShadow = GetShadow();
	
	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == true)
		{
			if (g_Skill[nCnt].ntype == SKILLTYPE_HORMING)
			{
				g_Skill[nCnt].nCounter++;
				UpdateHorming(nCnt);
			}
			// エフェクトの設定
			SetEffect(g_Skill[nCnt].pos,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				30,
				0,
				D3DXVECTOR3(2.0f, 2.0f, 2.0f),
				D3DXCOLOR(0.55f,0.75f,1.0f,1.0f),
				EFFECT_SKILL,
				nCnt,
				0.0f,
				D3DXVECTOR3(0.0f,0.0f,0.0f)
			);

			// エフェクトの設定
			SetEffect(g_Skill[nCnt].pos,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				30,
				0,
				D3DXVECTOR3(3.0f, 3.0f, 3.0f),
				D3DXCOLOR(0.05f, 0.25f, 1.0f, 1.0f),
				EFFECT_SKILL,
				nCnt,
				0.0f,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f)
			);

			if (g_Skill[nCnt].nLife > 0)
			{
				if ((g_Skill[nCnt].nLife % INTERVAL_IMPACT) == 0 && g_Skill[nCnt].ntype != SKILLTYPE_HORMING)
				{
					//衝撃波の設定
					SetImpact(IMPACTTYPE_SKILL,				// タイプ
						g_Skill[nCnt].pos,					// 場所
						D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f),	// 色
						30,									// 寿命
						5.0f,								// ないリンの大きさ
						10.0f,								// 外林の大きさ
						2,									// ２固定
						50,									// 分割数
						1.0f,								// 広がるスピード
						g_Skill[nCnt].rot.y);				// 向き
				}
			}

			if (g_Skill[nCnt].bHit == false && g_Skill[nCnt].ntype != SKILLTYPE_HORMING)
			{
				g_Skill[nCnt].move.x += sinf(g_Skill[nCnt].rot.y - D3DX_PI) * g_Skill[nCnt].Speed;
				g_Skill[nCnt].move.z += cosf(g_Skill[nCnt].rot.y - D3DX_PI) * g_Skill[nCnt].Speed;

				g_Skill[nCnt].pos += g_Skill[nCnt].move;
			}

			g_Skill[nCnt].nLife--;

			if (g_Skill[nCnt].nLife <= 0)
			{
				g_Skill[nCnt].bUse = false;
				DeleteEffect(EFFECT_SKILL, nCnt);
				if (g_Skill[nCnt].ntype != SKILLTYPE_HORMING)
				{
					SetSkillParticle(EFFECT_SKILL, nCnt, g_Skill[nCnt].StartPos, g_Skill[nCnt].pos, 100);
				}
				else
				{
					SetParticle(g_Skill[nCnt].pos,
						D3DXVECTOR3(628.0f, 628.0f, 628.0f),
						D3DXCOLOR(0.05f, 0.25f, 1.0f, 1.0f),
						PARTICLE_NONE,
						D3DXVECTOR3(1.0f, 1.0f, 1.0f),
						100,
						300,
						100.0f,
						100.0f,
						0.0f,
						EFFECT_NONE);
				}
				pShadow[g_Skill[nCnt].nIdxShadow].bUse = false;
				g_Skill[nCnt].AnimCounter = 0;
			}
		}
	}
}
void UpdateHorming(int Indx)
{
	//プレイヤーの情報取得
	Player* pPlayer = GetPlayer();
	ENEMY* pEnemy = GetEnemy();
	BOSS* pBoss = GetBoss();
	if (g_Skill[Indx].nCounter >= g_Skill[Indx].nCount && g_Skill[Indx].bHorming == false)
	{
		g_Skill[Indx].nCounter = 0;
		for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++,pEnemy++)
		{
			if (pEnemy->bUse == true)
			{
				if (SerchHormingEnemy(Indx, pEnemy->Object.Pos) == true)
				{
					g_Skill[Indx].nIndxHorming = EnemyCount;
					g_Skill[Indx].rot = pPlayer->rot;
					g_Skill[Indx].bHorming = true;
					if (pPlayer->bLockOn != true)
					{
						pEnemy += g_Skill[Indx].nIndxHorming;
					}
					else
					{
						pEnemy += pPlayer->nLockOnEnemy;
					}
					if (pEnemy->bUse == true)
					{
						D3DXVECTOR3 fMoveVec = pEnemy->Object.Pos - g_Skill[Indx].pos;
						D3DXVec3Normalize(&fMoveVec, &fMoveVec);
						g_Skill[Indx].moveDest = fMoveVec * 10.0f;
						//g_Skill[nCnt].move = fMoveVec;
					}
					else
					{
						g_Skill[Indx].moveDest = D3DXVECTOR3(0.0, 0.0f, 0.0f);
					}
					break;
				}
			}
		}
		if (pBoss->bUse == true)
		{
			if (SerchHormingEnemy(Indx, pBoss->Object.Pos) == true)
			{
				g_Skill[Indx].rot = pPlayer->rot;
				g_Skill[Indx].bHorming = true;
				D3DXVECTOR3 fMoveVec = pBoss->Object.Pos - g_Skill[Indx].pos;
				D3DXVec3Normalize(&fMoveVec, &fMoveVec);
				g_Skill[Indx].moveDest = fMoveVec * 10.0f;
			}
		}
	}
	if (g_Skill[Indx].bHorming == true && g_Skill[Indx].bHit == false)
	{
		D3DXVECTOR3 fMove;
		fMove.x = cosf(g_Skill[Indx].fRotRatio) * sinf(pPlayer->rot.y + D3DX_PI * 0.5f) * 1.0f;
		fMove.y = sinf(g_Skill[Indx].fRotRatio) * 1.0f;
		fMove.z = cosf(g_Skill[Indx].fRotRatio) * cosf(pPlayer->rot.y + D3DX_PI * 0.5f) * 1.0f;

		g_Skill[Indx].move = fMove;

		g_Skill[Indx].AnimCounter++;
		if (g_Skill[Indx].AnimCounter >= 30)
		{
			D3DXVECTOR3 moveDiff = g_Skill[Indx].moveDest - g_Skill[Indx].move;
			g_Skill[Indx].move = moveDiff / g_Skill[Indx].AnimCounter * 20.0f;
		}
		else if (g_Skill[Indx].AnimCounter >= 20)
		{
			PlaySound(SOUND_LABEL_MAGIC);
		}
		else
		{
			g_Skill[Indx].nLife = 100;
		}
		//if(g_Skill[nCnt].AnimCounter >= )
	}
	else
	{
		UpdateHormingPosition(Indx);
	}
	g_Skill[Indx].pos += g_Skill[Indx].move;
}
//=======================
// 弾の描画処理
//=======================
void DrawSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Skill[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_Skill[nCnt].mtxWorld._11 = mtxView._11;
			g_Skill[nCnt].mtxWorld._12 = mtxView._21;
			g_Skill[nCnt].mtxWorld._13 = mtxView._31;
			g_Skill[nCnt].mtxWorld._21 = mtxView._12;
			g_Skill[nCnt].mtxWorld._22 = mtxView._22;
			g_Skill[nCnt].mtxWorld._23 = mtxView._32;
			g_Skill[nCnt].mtxWorld._31 = mtxView._13;
			g_Skill[nCnt].mtxWorld._32 = mtxView._23;
			g_Skill[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Skill[nCnt].pos.x, g_Skill[nCnt].pos.y, g_Skill[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Skill[nCnt].mtxWorld, &g_Skill[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Skill[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffSkill, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureSkill);

			//ポリゴンを描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===================
// 弾の設定
//===================
void SetSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, SKILLTYPE ntype, float fRotRatio)
{
	//プレイヤーの情報取得
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == false)
		{
			g_Skill[nCnt].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);
			g_Skill[nCnt].StartPos = g_Skill[nCnt].pos;
			g_Skill[nCnt].move = move;
			g_Skill[nCnt].Speed = 0.5f;
			g_Skill[nCnt].rot = rot;
			g_Skill[nCnt].ntype = ntype;
			g_Skill[nCnt].nLife = SKILL_LIFE;

			// 通常魔法
			if (ntype == SKILLTYPE_NONE)
			{
				g_Skill[nCnt].fPower = pPlayer->Status.fPower;
			}
			// ホーミング魔法
			else if (ntype == SKILLTYPE_HORMING)
			{
				g_Skill[nCnt].fRotRatio = fRotRatio;
				g_Skill[nCnt].nCounter = 0;
				g_Skill[nCnt].nCount = 120;
				g_Skill[nCnt].nIndxHorming = 0;
				g_Skill[nCnt].bHorming = false;
				g_Skill[nCnt].move = D3DXVECTOR3(0.0f,0.0f,0.0f);
				g_Skill[nCnt].Speed = 0.0f;
				g_Skill[nCnt].fDistance = 0.0f;
				g_Skill[nCnt].nLife = 300;
				g_Skill[nCnt].AnimCounter = 0;
				g_Skill[nCnt].fPower = pPlayer->Status.fPower / 5;
			}
			// 爆発魔法
			else if (ntype == SKILLTYPE_EXPLOSION)
			{
				g_Skill[nCnt].fPower = pPlayer->Status.fPower * 1.25f;
			}
			g_Skill[nCnt].bHit = false;
			g_Skill[nCnt].bUse = true;
			break;
		}
	}
}
//***************************************
// ホーミング範囲に敵がいるか検索する関数
//***************************************
bool SerchHormingEnemy(int Indx, D3DXVECTOR3 Pos)
{
	Player* pPLayer = GetPlayer();
	D3DXVECTOR3 fDistance = pPLayer->pos - Pos;
	if (sqrtf((fDistance.x * fDistance.x) + (fDistance.y + fDistance.y) + (fDistance.z * fDistance.z)) <= DISTANCE_HORMING)
	{
		if (g_Skill[Indx].fDistance <= sqrtf((fDistance.x * fDistance.x) + (fDistance.y + fDistance.y) + (fDistance.z * fDistance.z)))
		{
			g_Skill[Indx].fDistance = sqrtf((fDistance.x * fDistance.x) + (fDistance.y + fDistance.y) + (fDistance.z * fDistance.z));
		}
		return true;
		g_Skill[Indx].nCount = INTERVAL_HORMING;
	}
	return false;
}
//***********************************
// ホーミングの球の位置を更新する関数
//***********************************
void UpdateHormingPosition(int Indx)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 fDistance;
	fDistance.x = cosf(g_Skill[Indx].fRotRatio) * sinf(pPlayer->rot.y + D3DX_PI * 0.5f) * 50.0f;
	fDistance.y = sinf(g_Skill[Indx].fRotRatio) * 50.0f;
	fDistance.z = cosf(g_Skill[Indx].fRotRatio) * cosf(pPlayer->rot.y + D3DX_PI * 0.5f) * 50.0f;

	g_Skill[Indx].pos = D3DXVECTOR3(pPlayer->PlayerMotion.aModel[1].mtxWorld._41,
		pPlayer->PlayerMotion.aModel[1].mtxWorld._42,
		pPlayer->PlayerMotion.aModel[1].mtxWorld._43) + fDistance;
	g_Skill[Indx].StartPos = g_Skill[Indx].pos;
}
void UpdateHormingAnim(int Indx)
{

}
//==============
// 魔法の取得
//==============
Skill* GetSkill()
{
	return &g_Skill[0];
}
//===============
// MPを減らす
//===============
void SubMP(SKILLTYPE type)
{
	Player* pPlayer = GetPlayer();

	switch (type)
	{
	case SKILLTYPE_NONE:
		pPlayer->Status.nMP -= 50;
		break;

	case SKILLTYPE_HORMING:
		pPlayer->Status.nMP -= 100;
		break;

	case SKILLTYPE_EXPLOSION:
		pPlayer->Status.nMP -= 10;
		break;
	default:
		break;
	}
}