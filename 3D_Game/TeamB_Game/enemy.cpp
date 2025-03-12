//*********************************************************
// 
// enemy[enemy.cpp]
// Author:Hatori
// 
//*********************************************************

//*************
// インクルード
///************
#include "enemy.h"
#include "camera.h"
#include "particle.h"
#include "wall.h"
#include "loadmotion.h"
#include "shadow.h"
#include "animation.h"
#include "player.h"
#include "item.h"
#include "skill.h"
#include "collision.h"
#include "lockon.h"
#include "model.h"
#include "collision.h"
#include "HPgauge.h"
#include "score.h"
#include "sound.h"
#include "arrow.h"
#include "minimap.h"

//*******************
// グローバル変数宣言
//*******************
ENEMY g_Enemy[MAX_ENEMY];
EnemyOrigin g_EnemyOrigin[ENEMYTYPE_MAX];
int g_nNumEnemy;
float g_fDistance[MAX_ENEMY];//デバックフォント用

//***************
// 敵の初期化処理
//***************
void InitEnemy(void)
{
	//敵の数の初期化
	g_nNumEnemy = 0;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_Enemy[i].state = ENEMYSTATE_NORMAL;								// 敵の状態
		g_Enemy[i].ActionType = ENEMYACTION_WELL;							// モーションの種類
		g_Enemy[i].Status.fPower = ENEMY_AP;								// 攻撃力
		g_Enemy[i].Status.fSpeed = ENEMY_SPEED;								// スピード
		g_Enemy[i].Status.fHP = ENEMY_HP;									// HP
		g_Enemy[i].EnemyMotion.motionType = MOTIONTYPE_NEUTRAL;				// モーションの種類
		g_Enemy[i].EnemyMotion.nKey = 0;									// モーションのキー
		g_Enemy[i].EnemyMotion.nNextKey = 1;									// モーションの次のキー
		g_Enemy[i].EnemyMotion.bBlendMotion = true;
		g_Enemy[i].Object.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);			// 位置
		g_Enemy[i].Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
		g_Enemy[i].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き(目標)
		g_Enemy[i].bUse = false;											// 使用しているかどうか
		g_Enemy[i].nActionCount = 0;										// アクションカウンター
		g_Enemy[i].nActionCounter = 0;										// アクションカウンター
		g_Enemy[i].Action = ENEMYACTION_WELL;								// 行動の種類
		g_Enemy[i].Radius = 4.4f;											// 半径

		g_Enemy[i].bLockOn = false;
		g_Enemy[i].fSightRange = 200.0f;									// 視界距離
		g_Enemy[i].fSightAngle = D3DXToRadian(110.0f);						// 視界の葉に
		g_Enemy[i].fDistance = g_Enemy[i].fSightRange / 2;

		g_fDistance[i] = 0.0f;
	}
}
//*************
// 敵の終了処理
//*************
void UninitEnemy(void)
{
	for (int OriginCount = 0; OriginCount < ENEMYTYPE_MAX; OriginCount++)
	{
		for (int PartsCount = 0; PartsCount < MAX_PARTS; PartsCount++)
		{
			//メッシュの破棄
			if (g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pMesh != NULL)
			{
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pMesh->Release();
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pMesh = NULL;
			}

			//マテリアルの破棄
			if (g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pBuffMat != NULL)
			{
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pBuffMat->Release();
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pBuffMat = NULL;
			}

			for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
			{
				//テクスチャの破棄
				if (g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pTexture[TexCount] != NULL)
				{
					g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pTexture[TexCount]->Release();
					g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pTexture[TexCount] = NULL;
				}
			}
		}
	}

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		for (int i1 = 0; i1 < MAX_ENEMYPARTS; i1++)
		{
			// メッシュの破棄
			if (g_Enemy[i].EnemyMotion.aModel[i1].pMesh != NULL)
			{
				g_Enemy[i].EnemyMotion.aModel[i1].pMesh = NULL;
			}

			// マテリアルの破棄
			if (g_Enemy[i].EnemyMotion.aModel[i1].pBuffMat != NULL)
			{
				g_Enemy[i].EnemyMotion.aModel[i1].pBuffMat = NULL;
			}

			for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
			{
				//テクスチャの破棄
				if (g_Enemy[i].EnemyMotion.aModel[i1].pTexture[TexCount] != NULL)
				{
					g_Enemy[i].EnemyMotion.aModel[i1].pTexture[TexCount] = NULL;
				}
			}
		}
	}
}

//*************
// 敵の更新処理
//*************
void UpdateEnemy(void)
{
	MODE nMode = GetMode();
	Player* pPlayer = GetPlayer();
	Skill* pSkill = GetSkill();


	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_Enemy[EnemyCount].bUse == true)
		{
			UpdateMiniMapEnemy(g_Enemy[EnemyCount].IndxMiniMap,g_Enemy[EnemyCount].Object.Pos);
			STAGEMODEL*pObb = GetModel();
			for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++, pObb++)
			{
				if (pObb->bUse == true)
				{
					OBB EnemyObb;
					EnemyObb.CenterPos = g_Enemy[EnemyCount].Object.Pos;

					EnemyObb.fLength[0] = 10.0f;
					EnemyObb.fLength[1] = 20.0f;
					EnemyObb.fLength[2] = 10.0f;

					EnemyObb.RotVec[0] = D3DXVECTOR3(1.0f,0.0f,0.0f);
					EnemyObb.RotVec[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
					EnemyObb.RotVec[2] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
					bool bCollision = collisionobb(EnemyObb, pObb->ObbModel, g_Enemy[EnemyCount].Object.Pos, pObb->pos);
					if (bCollision == true)
					{
						D3DXVECTOR3 VecMove = g_Enemy[EnemyCount].Object.OldPos - g_Enemy[EnemyCount].Object.Pos;
						D3DXVECTOR3 NorFace = collisionobbfacedot(pObb->ObbModel, D3DXVECTOR3(g_Enemy[EnemyCount].Object.Pos.x,
							g_Enemy[EnemyCount].Object.Pos.y + 10.0f, 
							g_Enemy[EnemyCount].Object.Pos.z), VecMove);
						PushPosition(&g_Enemy[EnemyCount].Object.Pos, VecMove, NorFace);
					}
				}
			}

			if (g_Enemy[EnemyCount].state != ENEMYSTATE_KNOCKUP)
			{
				// 行動の更新
				UpdateAction(EnemyCount);
			}

			// 魔法との当たり判定
			for (int SkillCount = 0; SkillCount < MAX_SKILL; SkillCount++)
			{
				if (pSkill[SkillCount].bUse == true)
				{
					// 当たり判定
					if (collisioncircle(g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].Radius, pSkill[SkillCount].pos, SKILL_SIZE) == true)
					{
						pSkill[SkillCount].nLife = 1;
						pSkill[SkillCount].bHit = true;
						HitEnemy(pSkill[SkillCount].fPower, EnemyCount);
					}
				}
			}

			// 攻撃時の当たり判定
			if (pPlayer->state != PLAYERSTATE_KNOCKUP)
			{
				if (g_Enemy[EnemyCount].EnemyMotion.motionType == MOTIONTYPE_ACTION)
				{
					CollisionEnemyAction(EnemyCount);
				}
			}

			// ロックオン
			if (pPlayer->bWantLockOn == true)
			{
				if (IsEnemyInsight(g_Enemy[EnemyCount].Object.Pos, 0) == true)
				{
					EnemyDistanceSort(EnemyCount);
					pPlayer->bLockOn = true;
				}
			}

			g_Enemy[EnemyCount].bLockOn = IsPlayerInsight(EnemyCount);

			// 角度の近道
			if (g_Enemy[EnemyCount].rotDest.y - g_Enemy[EnemyCount].Object.Rot.y >= D3DX_PI)
			{
				g_Enemy[EnemyCount].Object.Rot.y += D3DX_PI * 2.0f;
			}
			else if (g_Enemy[EnemyCount].rotDest.y - g_Enemy[EnemyCount].Object.Rot.y <= -D3DX_PI)
			{
				g_Enemy[EnemyCount].Object.Rot.y -= D3DX_PI * 2.0f;
			}

			if (g_Enemy[EnemyCount].statecount <= 0)
			{
				g_Enemy[EnemyCount].state = ENEMYSTATE_NORMAL;
				g_Enemy[EnemyCount].bHit = false;
				g_Enemy[EnemyCount].statecount = 0;
			}
			g_Enemy[EnemyCount].statecount--;

			//床判定
			if (g_Enemy[EnemyCount].Object.Pos.y < 0)
			{
				g_Enemy[EnemyCount].Object.Pos.y = 0;
			}

			//向きの更新
			g_Enemy[EnemyCount].Object.Rot.y += (g_Enemy[EnemyCount].rotDest.y - g_Enemy[EnemyCount].Object.Rot.y) * 0.05f;

			//前の位置の保存
			g_Enemy[EnemyCount].Object.OldPos = g_Enemy[EnemyCount].Object.Pos;

			//位置の更新
			g_Enemy[EnemyCount].Object.Pos += g_Enemy[EnemyCount].move;

			//影の更新
			SetPositionShadow(g_Enemy[EnemyCount].IndxShadow, g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].bUse);		// 位置
			SetSizeShadow(g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].IndxShadow);										// サイズの更新

			//HPゲージの更新
			float Y = 50.0f;
			if (g_Enemy[EnemyCount].type == ENEMYTYPE_MIDBOSS)
			{
				Y = 70.0f;
			}
			SetPositionHPgauge(g_Enemy[EnemyCount].IndxGuage, D3DXVECTOR3(g_Enemy[EnemyCount].Object.Pos.x, (float)g_Enemy[EnemyCount].Object.Pos.y + Y, g_Enemy[EnemyCount].Object.Pos.z));
			RedgaugeDeff(g_Enemy[EnemyCount].IndxGuage, g_Enemy[EnemyCount].Status.fHP);

			//モーションの更新
			UpdateMotion(&g_Enemy[EnemyCount].EnemyMotion);
		}
	}
}

//*************
// 敵の描画処理
//*************
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;		// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアルの保存用
	D3DXMATERIAL* pMat;							// マテリアルへのポインタ


	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_Enemy[EnemyCount].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[EnemyCount].Object.mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[EnemyCount].Object.Rot.y, g_Enemy[EnemyCount].Object.Rot.x, g_Enemy[EnemyCount].Object.Rot.z);
			D3DXMatrixMultiply(&g_Enemy[EnemyCount].Object.mtxWorld, &g_Enemy[EnemyCount].Object.mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[EnemyCount].Object.Pos.x, g_Enemy[EnemyCount].Object.Pos.y, g_Enemy[EnemyCount].Object.Pos.z);
			D3DXMatrixMultiply(&g_Enemy[EnemyCount].Object.mtxWorld, &g_Enemy[EnemyCount].Object.mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[EnemyCount].Object.mtxWorld);

			// 現在のマテリアルの取得
			pDevice->GetMaterial(&matDef);


			for (int EnemyPartsCount = 0; EnemyPartsCount < g_EnemyOrigin[g_Enemy[EnemyCount].nType].nNumParts; EnemyPartsCount++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;
				D3DXMATRIX mtxParent;
				D3DXMatrixIdentity(&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld);

				// 向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].rot.y, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].rot.x, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].rot.z);
				D3DXMatrixMultiply(&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld, &g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld, &mtxRotModel);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTransModel, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pos.x, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pos.y, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pos.z);
				D3DXMatrixMultiply(&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld, &g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld, &mtxTransModel);


				if (g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].Parent != -1)
				{
					mtxParent = g_Enemy[EnemyCount].EnemyMotion.aModel[g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].Parent].mtxWorld;
				}
				else
				{
					mtxParent = g_Enemy[EnemyCount].Object.mtxWorld;
				}
				D3DXMatrixMultiply(&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld,
					&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld,
					&mtxParent);

				pDevice->SetTransform(D3DTS_WORLD,
					&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld);

				// マテリアルデータへのポインタ
				pMat = (D3DXMATERIAL*)g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].dwNumMat; nCntMat++)
				{
					switch (g_Enemy[EnemyCount].state)
					{
					case ENEMYSTATE_NORMAL:
						// マテリアルの設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
						break;
					case ENEMYSTATE_KNOCKUP:
						D3DXMATERIAL Damage;
						Damage = pMat[nCntMat];

						Damage.MatD3D.Diffuse.r = 255;
						// マテリアルの設定
						pDevice->SetMaterial(&Damage.MatD3D);
						break;
					default:
						break;
					}
					// テクスチャの設定
					pDevice->SetTexture(0, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pTexture[nCntMat]);

					// モデル(パーツ)の描画
					g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pMesh->DrawSubset(nCntMat);
				}

				DrawPlayerShadow(g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld,
					g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pBuffMat,
					g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pMesh,
					(int)g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].dwNumMat,
					g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].rot,
					g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pos);

				if (EnemyPartsCount == g_Enemy[EnemyCount].CollModel)
				{
					EnemyMatrixWand(EnemyCount);
				}
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

//*************
// 敵の取得処理
//*************
ENEMY* GetEnemy()
{
	return &g_Enemy[0];
}

//***************
// 敵のヒット処理
//***************
void HitEnemy(float Atack,int Indx)
{
	Player* pPlayer = GetPlayer();

	g_Enemy[Indx].Status.fHP -= (int)Atack;

	g_Enemy[Indx].Action = ENEMYACTION_WELL;
	g_Enemy[Indx].state = ENEMYSTATE_KNOCKUP;
	g_Enemy[Indx].bHit = true;

	if (pPlayer->Skilltype == SKILLTYPE_EXPLOSION && g_Enemy[Indx].type != ENEMYTYPE_MIDBOSS)
	{
		float move = 1.5f;

		D3DXVECTOR3 Vec = g_Enemy[Indx].Object.Pos - pPlayer->pos;
		D3DXVec3Normalize(&Vec, &Vec);
		g_Enemy[Indx].move = Vec * move;
	}

	//HPゲージの更新
	HPgaugeDeff(g_Enemy[Indx].IndxGuage, g_Enemy[Indx].Status.fHP);

	if (Atack >= 10)
	{// ダメージが最小値以上なら
		//g_Enemy[Indx].statecount = (int)Atack * 3;
		g_Enemy[Indx].statecount = 30;
	}
	else
	{// ダメージが最小値以下なら
		g_Enemy[Indx].statecount = 30;
	}

	if (g_Enemy[Indx].Status.fHP <= 0.0f && g_Enemy[Indx].bUse == true)
	{// 使われていて体力が０以下なら
		DeadEnemy(Indx);
	}
}

//*************
// 敵の設定処理
//*************
void SetEnemy(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 rot)
{
	Player* pPlayer = GetPlayer();
	MODE nMode = GetMode();

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_Enemy[EnemyCount].bUse == false)
		{
			g_Enemy[EnemyCount].IndxMiniMap = SetMapEnemy(pos);
			g_nNumEnemy++;
			g_Enemy[EnemyCount].bUse = true;
			g_Enemy[EnemyCount].Object.Pos = pos;
			g_Enemy[EnemyCount].Object.Rot = rot;
			g_Enemy[EnemyCount].state = ENEMYSTATE_NORMAL;
			g_Enemy[EnemyCount].nType = nType;
			g_Enemy[EnemyCount].nNumModel = g_EnemyOrigin[nType].nNumParts;
			g_Enemy[EnemyCount].EnemyMotion.nNumModel = g_EnemyOrigin[nType].nNumParts;

			for (int PartsCount = 0; PartsCount < g_EnemyOrigin[nType].nNumParts; PartsCount++)
			{
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].nIndx = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].nIndx;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].Parent = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].Parent;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].pos = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pos;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].OffSetPos = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSetPos;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].rot = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].rot;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].OffSetRot = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSetRot;

				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].dwNumMat = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].dwNumMat;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].pBuffMat = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pBuffMat;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].pMesh = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pMesh;

				for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++)
				{
					g_Enemy[EnemyCount].EnemyMotion.aMotionInfo[MotionCount] = g_EnemyOrigin[nType].EnemyMotion.aMotionInfo[MotionCount];
				}
			}
			g_Enemy[EnemyCount].IndxShadow = SetShadow(g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].Object.Rot,20.0f);
			g_Enemy[EnemyCount].nActionCount = rand() % 180 + 120;

			if (nType == 0)
			{
				g_Enemy[EnemyCount].type = ENEMYTYPE_SKELETON;
				g_Enemy[EnemyCount].CollModel = 3;
				g_Enemy[EnemyCount].Status.fPower = ENEMY_AP;				// 攻撃力
				g_Enemy[EnemyCount].Status.fSpeed = HOMING_MOVE;			// スピード
				g_Enemy[EnemyCount].Status.fHP = ENEMY_HP;					// HP
				g_Enemy[EnemyCount].Status.Score = ENEMY_SCORE;				// スコア
			}
			else if(nType == 1)
			{
				g_Enemy[EnemyCount].type = ENEMYTYPE_ZOMBIE;
				g_Enemy[EnemyCount].CollModel = 1;
				g_Enemy[EnemyCount].Status.fPower = ENEMY_AP;				// 攻撃力
				g_Enemy[EnemyCount].Status.fSpeed = HOMING_MOVE * 0.25f;	// スピード
				g_Enemy[EnemyCount].Status.fHP = ENEMY_HP;					// HP
				g_Enemy[EnemyCount].Status.Score = ENEMY_SCORE;				// スコア
			}
			else if (nType == 2)
			{
				g_Enemy[EnemyCount].type = ENEMYTYPE_MIDBOSS;
				g_Enemy[EnemyCount].CollModel = 10;
				g_Enemy[EnemyCount].Status.fPower = ENEMY_AP * 1.5;			// 攻撃力
				g_Enemy[EnemyCount].Status.fSpeed = HOMING_MOVE * 0.5f;			// スピード
				g_Enemy[EnemyCount].Status.fHP = ENEMY_HP * 2;				// HP
				g_Enemy[EnemyCount].Status.Score = ENEMY_SCORE * 2;			// スコア
			}

			//HPゲージの設定処理
			g_Enemy[EnemyCount].IndxGuage = SetHPgauge(D3DXVECTOR3(g_Enemy[EnemyCount].Object.Pos.x, (float)g_Enemy[EnemyCount].Object.Pos.y + 50.0f, g_Enemy[EnemyCount].Object.Pos.z), D3DXVECTOR2(60.0f, 5.0f), g_Enemy[EnemyCount].Status.fHP);

			break;
		}
	}
}

//*************
// 敵の取得処理
//*************
int* GetNumEnemy(void)
{
	return &g_nNumEnemy;
}

//*************
// 敵の死亡処理
//*************
void DeadEnemy(int Indx)
{
	MODE nMode = GetMode();
	Player* pPlayer = GetPlayer();
	Camera* pCamera = GetCamera();
	int Drop = 0;			//ドロップ確率
	int Itemtype = 0;		//アイテムの種類

	g_Enemy[Indx].bUse = false;
	g_nNumEnemy--;
	SetPositionShadow(g_Enemy[Indx].IndxShadow,g_Enemy[Indx].Object.Pos,g_Enemy[Indx].bUse);

	//HPゲージを消す
	DeleteHPGuage(g_Enemy[Indx].IndxGuage);

	//アイテムドロップ
	Itemtype = rand() % 9;
	if (Itemtype == 1 || Itemtype == 2 || Itemtype == 3 || Itemtype == 4)
	{
		Itemtype = ITEMTYPE_HP;
	}
	else if (Itemtype == 5 || Itemtype == 6 || Itemtype == 7 || Itemtype == 8)
	{
		Itemtype = ITEMTYPE_MP;
	}
	else if (Itemtype == 9)
	{
		Itemtype = ITEMTYPE_POWER;
	}


	//アイテムの設定
	SetItem(g_Enemy[Indx].Object.Pos, (ITEMTYPE)Itemtype);

	SetParticle(g_Enemy[Indx].Object.Pos, 
		D3DXVECTOR3(100.0f, 100.0f, 100.0f), 
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		PARTICLE_NONE, 
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		100,
		50,
		2.0f,
		2.0f,
		1.0f,
		EFFECT_NONE);

	if (Indx == pPlayer->nLockOnEnemy)
	{
		g_Enemy[pPlayer->nLockOnEnemy].fDistance = 0;
		pPlayer->nLockOnEnemy = 0;
		pPlayer->bLockOn = false;
	}

	DeleteEnemyMiniMap(g_Enemy[Indx].IndxMiniMap);
	AddScore(g_Enemy[Indx].Status.Score);
}

//***************
// 敵の行動を更新
//***************
void UpdateAction(int nCount)
{
	Player* pPlayer = GetPlayer();				//プレイヤーの情報取得

	//敵とプレイヤーの距離計算
	D3DXVECTOR3 vec = pPlayer->pos - g_Enemy[nCount].Object.Pos;
	float fDistance = (vec.x) * (vec.x) + (vec.z) * (vec.z);
	float fAngle = 0.0f;

	fDistance = (float)sqrt(fDistance);				//敵とプレイヤーの距離
	g_fDistance[nCount] = fDistance;

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

	//攻撃
	if (fDistance <= ATTACK_DIST)
	{
		if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_ACTION)
		{
			//モーションの種類設定
			g_Enemy[nCount].ActionType = ENEMYACTION_ATTACK;
			SetMotion(MOTIONTYPE_ACTION, &g_Enemy[nCount].EnemyMotion,10);
		}
		g_Enemy[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//追いかける
	else if (fDistance <= HOMING_DIST)
	{
		if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_ACTION)
		{
			//モーションの種類設定
			g_Enemy[nCount].ActionType = ENEMYACTION_RUN;

			//移動量の設定
			g_Enemy[nCount].move.x = sinf(fAngle) * HOMING_MOVE;
			g_Enemy[nCount].move.z = cosf(fAngle) * HOMING_MOVE;

			//角度の目標設定
			g_Enemy[nCount].rotDest.y = fAngle + D3DX_PI;

			if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_MOVE)
			{
				SetMotion(MOTIONTYPE_MOVE, &g_Enemy[nCount].EnemyMotion,10);
			}
		}
	}
	//様子見
	else
	{
		g_Enemy[nCount].ActionType = ENEMYACTION_WELL;
		if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_NEUTRAL && g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_ACTION)
		{
			SetMotion(MOTIONTYPE_NEUTRAL, &g_Enemy[nCount].EnemyMotion,10);
		}
		g_Enemy[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//*****************
// 敵の状態遷移処理
//*****************
void EnemyState(int Indx)
{

}

//******************
// 敵のオフセット?
//******************
void SetEnemyPartsInfo(LoadInfo PartsInfo, int nType)
{
	nType -= 1;
	g_EnemyOrigin[nType].nNumParts = PartsInfo.nNumParts;
	g_EnemyOrigin[nType].EnemyMotion.nNumModel = PartsInfo.nNumParts;
	for (int PartsCount = 0; PartsCount < g_EnemyOrigin[nType].nNumParts; PartsCount++)
	{
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].nIndx = PartsInfo.PartsInfo[PartsCount].nIndx;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].Parent = PartsInfo.PartsInfo[PartsCount].Parent;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pos = PartsInfo.PartsInfo[PartsCount].pos;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSetPos = PartsInfo.PartsInfo[PartsCount].OffSetPos;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].rot = PartsInfo.PartsInfo[PartsCount].rot;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSetRot = PartsInfo.PartsInfo[PartsCount].OffSetRot;

		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		HRESULT hresult = D3DXLoadMeshFromX(PartsInfo.cPartsPath[PartsCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pBuffMat,
			NULL,
			&g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].dwNumMat,
			&g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pMesh);

		if (FAILED(hresult))
		{
			return;
		}

		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ

		//頂点数取得
		nNumVtx = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pMesh->GetNumVertices();
		//頂点フォーマットのサイズ取得
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pMesh->GetFVF());

		D3DXMATERIAL* pMat;//マテリアルへのポインタ
		pMat = (D3DXMATERIAL*)g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename, 
					&g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pTexture[nCntMat]); //1
			}
		}
	}
	for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++)
	{
		g_EnemyOrigin[nType].EnemyMotion.aMotionInfo[MotionCount] = PartsInfo.MotionInfo[MotionCount];
	}
}

//==============================
// 敵とプレイヤーの当たり判定
//==============================
void CollisionEnemy(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//敵との距離
			g_Enemy[nCntEnemy].fDistance = sqrtf(((g_Enemy[nCntEnemy].Object.Pos.x - pPlayer->pos.x) * (g_Enemy[nCntEnemy].Object.Pos.x - pPlayer->pos.x))
											   + ((g_Enemy[nCntEnemy].Object.Pos.y - pPlayer->pos.y) * (g_Enemy[nCntEnemy].Object.Pos.y - pPlayer->pos.y))
											   + ((g_Enemy[nCntEnemy].Object.Pos.z - pPlayer->pos.z) * (g_Enemy[nCntEnemy].Object.Pos.z - pPlayer->pos.z)));

			float RADIUS = ((PLAYER_RADIUS / 2) + g_Enemy[nCntEnemy].Radius) * ((PLAYER_RADIUS / 2) + g_Enemy[nCntEnemy].Radius);

			if (g_Enemy[nCntEnemy].fDistance <= RADIUS)
			{
				HitPlayer(g_Enemy[nCntEnemy].Status.fPower,g_Enemy[nCntEnemy].Object.Pos);
			}
		}
	}
}

//===================================
// 敵のアクション時の当たり判定処理
//===================================
void CollisionEnemyAction(int nCnt)
{
	Player* pPlayer = GetPlayer();

	float radius = g_Enemy[nCnt].Radius / 2; // 半径
	float division = 0.25;	// 分割数
	// 親モデル
	int Parent = g_Enemy[nCnt].EnemyMotion.aModel[g_Enemy[nCnt].CollModel].Parent;

	D3DXVECTOR3 Pos = D3DXVECTOR3(g_Enemy[nCnt].mtxWand._41, g_Enemy[nCnt].mtxWand._42, g_Enemy[nCnt].mtxWand._43);
	D3DXVECTOR3 Pos1 = D3DXVECTOR3(g_Enemy[nCnt].EnemyMotion.aModel[Parent].mtxWorld._41, g_Enemy[nCnt].EnemyMotion.aModel[Parent].mtxWorld._42, g_Enemy[nCnt].EnemyMotion.aModel[Parent].mtxWorld._43);

	D3DXVECTOR3 sabun = Pos1 - Pos;

	for (int n = 0; n < 4; n++)
	{
		D3DXVECTOR3 sabun1 = Pos1 - sabun * division * (FLOAT)n;
		D3DXVECTOR3 CollPos = sabun1 - sabun;

		if (collisioncircle(CollPos, radius, pPlayer->pos, PLAYER_RADIUS) == true)
		{
			HitPlayer(g_Enemy[nCnt].Status.fPower, g_Enemy[nCnt].Object.Pos);

			if (g_Enemy[nCnt].type == ENEMYTYPE_SKELETON)
			{
				PlaySound(SOUND_LABEL_SKELETON);
			}
			else if (g_Enemy[nCnt].type == ENEMYTYPE_ZOMBIE)
			{
				PlaySound(SOUND_LABEL_ZOMBI);
			}
			else if (g_Enemy[nCnt].type == ENEMYTYPE_MIDBOSS)
			{
				PlaySound(SOUND_LABEL_SLASH);
			}

			break;
		}
#ifdef _DEBUG
		// エフェクトの設定
		SetEffect(D3DXVECTOR3(CollPos.x, CollPos.y, CollPos.z),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			10,
			0,
			D3DXVECTOR3(radius, radius, radius),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			EFFECT_SKILL,
			0,
			0.0f,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
#endif
	}
}

//========================
// 距離の取得
//========================
float GetfDistance()
{
	return g_fDistance[0];
}

//=================================
// プレイヤーが視界にいるかどうか
//=================================
bool IsPlayerInsight(int Index)
{
	Player* pPlayer = GetPlayer();
	bool bLock = false;

	D3DXVECTOR3 EnemyFront;

	EnemyFront.x = -sinf(g_Enemy[Index].Object.Rot.y);
	EnemyFront.y = 0.0f;
	EnemyFront.z = -cosf(g_Enemy[Index].Object.Rot.y);

	D3DXVECTOR3 toPlayer;

	toPlayer.x = pPlayer->pos.x - g_Enemy[Index].Object.Pos.x;
	toPlayer.y = 0.0f;
	toPlayer.z = pPlayer->pos.z - g_Enemy[Index].Object.Pos.z;

	D3DXVec3Normalize(&EnemyFront, &EnemyFront);

	D3DXVec3Normalize(&toPlayer, &toPlayer);

	float dotProduct = D3DXVec3Dot(&EnemyFront, &toPlayer);

	if (dotProduct > cosf(g_Enemy[Index].fSightAngle * 0.5f))
	{
		float distanceSquared =
			(pPlayer->pos.x - g_Enemy[Index].Object.Pos.x) * (pPlayer->pos.x - g_Enemy[Index].Object.Pos.x) +
			(pPlayer->pos.x - g_Enemy[Index].Object.Pos.y) * (pPlayer->pos.x - g_Enemy[Index].Object.Pos.y) +
			(pPlayer->pos.x - g_Enemy[Index].Object.Pos.z) * (pPlayer->pos.x - g_Enemy[Index].Object.Pos.z);

		if (distanceSquared <= g_Enemy[Index].fSightRange * g_Enemy[Index].fSightRange)
		{
			bLock = true;
		}
	}

	return bLock;
}

//===============
// マトリックス
//===============
void EnemyMatrixWand(int Index)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRotEnemy, mtxTransEnemy;
	D3DXMATRIX mtxParent;
	D3DXMatrixIdentity(&g_Enemy[Index].mtxWand);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRotEnemy, g_Enemy[Index].EnemyMotion.aModel[g_Enemy[Index].CollModel].rot.y, g_Enemy[Index].EnemyMotion.aModel[g_Enemy[Index].CollModel].rot.x, g_Enemy[Index].EnemyMotion.aModel[g_Enemy[Index].CollModel].rot.z);
	D3DXMatrixMultiply(&g_Enemy[Index].mtxWand, &g_Enemy[Index].mtxWand, &mtxRotEnemy);

	// 位置を反映
	D3DXVECTOR3 pos;
	if (g_Enemy[Index].type == ENEMYTYPE_SKELETON)
	{
		pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	}
	else if (g_Enemy[Index].type == ENEMYTYPE_ZOMBIE)
	{
		pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	}
	else if (g_Enemy[Index].type == ENEMYTYPE_MIDBOSS)
	{
		pos = D3DXVECTOR3(0.0f, 0.0f, -20.0f);
	}
	D3DXMatrixTranslation(&mtxTransEnemy, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_Enemy[Index].mtxWand, &g_Enemy[Index].mtxWand, &mtxTransEnemy);

	mtxParent = g_Enemy[Index].EnemyMotion.aModel[g_Enemy[Index].CollModel].mtxWorld;

	D3DXMatrixMultiply(&g_Enemy[Index].mtxWand,
		&g_Enemy[Index].mtxWand,
		&mtxParent);

	pDevice->SetTransform(D3DTS_WORLD,
		&g_Enemy[Index].mtxWand);
}