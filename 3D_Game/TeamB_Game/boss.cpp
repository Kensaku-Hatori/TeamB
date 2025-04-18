//*********************************************************
// 
// ボスに関する処理[boss.cpp]
// Author:Hatori
// 
//*********************************************************

//*************
// インクルード
///************
#include "boss.h"
#include "camera.h"
#include "particle.h"
#include "wall.h"
#include "loadmotion.h"
#include "shadow.h"
#include "animation.h"
#include "player.h"
#include "skill.h"
#include "collision.h"
#include "lockon.h"
#include "resultinfo.h"
#include "fade.h"
#include "score.h"
#include "game.h"
#include "sound.h"
#include "minimap.h"
#include "bossgauge.h"

//*******************
// グローバル変数宣言
//*******************
BOSS g_Boss;

//***************
// ボスの初期化処理
//***************
void InitBoss(void)
{
	g_Boss.state = BOSSSTATE_NORMAL;								// 敵の状態
	g_Boss.ActionType = BOSSACTION_WELL;							// モーションの種類
	g_Boss.Status.fPower = BOSS_AP;									// 攻撃力
	g_Boss.Status.fSpeed = BOSS_SPEED;								// スピード
	g_Boss.Status.fHP = BOSS_HP;									// HP
	g_Boss.Status.Score = BOSS_SCORE;								// スコア
	g_Boss.BossMotion.motionType = MOTIONTYPE_NEUTRAL;				// モーションの種類
	g_Boss.BossMotion.nKey = 0;										// モーションのキー
	g_Boss.BossMotion.NextKey = 1;									// モーションの次のキー
	g_Boss.BossMotion.bBlendMotion = true;							// モーションブレンドをするかどうか
	g_Boss.Object.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);			// 位置
	g_Boss.Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
	g_Boss.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き(目標)
	g_Boss.bUse = false;											// 使用しているかどうか
	g_Boss.nActionCount = 0;										// アクションカウンター
	g_Boss.nActionCounter = 0;										// アクションカウンター
	g_Boss.Action = BOSSACTION_WELL;								// 行動の種類
	g_Boss.Radius = 4.4f;											// 半径
	g_Boss.BossAi.primary[0] = 34.0f;
	g_Boss.BossAi.primary[1] = 33.0f;
	g_Boss.BossAi.primary[2] = 33.0f;
	g_Boss.CollModel = 12;
}
//*************
// ボスの終了処理
//*************
void UninitBoss(void)
{
	for (int PartsCount = 0; PartsCount < MAX_PARTS; PartsCount++)
	{
		UninitMesh(g_Boss.BossMotion.aModel[PartsCount].pMesh);
		UninitBuffMat(g_Boss.BossMotion.aModel[PartsCount].pBuffMat);

		for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
		{//テクスチャの破棄
			UninitTexture(g_Boss.BossMotion.aModel[PartsCount].pTexture[TexCount]);
		}
	}
}

//*************
// ボスの更新処理
//*************
void UpdateBoss(void)
{
	Player* pPlayer = GetPlayer();
	Skill* pSkill = GetSkill();
	MODE Mode = GetMode();

	if (g_Boss.bUse == true)
	{
		Routine();
		EndAction();
		UpdateMiniMapEnemy(g_Boss.MiniMapIndx, g_Boss.Object.Pos);
		if (g_Boss.BossAi.bFinishAction == true && Mode != MODE_BOSSMOVIE)
		{
			// 行動の更新
			UpdateBossAction();
		}
		UpdateBossActionMove();
		NormalizeBossRot();
		// 攻撃時の当たり判定
		if (pPlayer->state != PLAYERSTATE_KNOCKUP)
		{
			if (g_Boss.BossMotion.motionType == MOTIONTYPE_ACTION || g_Boss.BossMotion.motionType == MOTIONTYPE_DOWN)
			{
				CollisionBossAction();
			}
		}

		//ロックオン
		if (pPlayer->bWantLockOn == true)
		{
			if (IsEnemyInsight(g_Boss.Object.Pos, 1) == true)
			{
				pPlayer->bLockOn = true;
			}
			else
			{
				pPlayer->bWantLockOn = false;
			}
		}

		if (g_Boss.statecount <= 0)
		{
			g_Boss.state = BOSSSTATE_NORMAL;
			g_Boss.bHit = false;
			g_Boss.statecount = 0;
		}
		g_Boss.statecount--;

		g_Boss.Object.OldPos = g_Boss.Object.Pos;
		// 移動量の更新(減衰)
		g_Boss.move.x = (0.0f - g_Boss.move.x) * 0.1f;
		g_Boss.move.y = (0.0f - g_Boss.move.y) * 0.1f;
		g_Boss.move.z = (0.0f - g_Boss.move.z) * 0.1f;

		// 位置の更新
		g_Boss.Object.Pos += g_Boss.move;

		// 床判定
		if (g_Boss.Object.Pos.y < 0)
		{
			g_Boss.Object.Pos.y = 0;
		}

		g_Boss.Object.Rot.y += (g_Boss.rotDest.y - g_Boss.Object.Rot.y) * 0.05f;

		// 影の更新
		SetPositionShadow(g_Boss.IndxShadow, g_Boss.Object.Pos, g_Boss.bUse);
		SetSizeShadow(g_Boss.Object.Pos, g_Boss.IndxShadow);

		// モーションの更新
		UpdateMotion(&g_Boss.BossMotion);
		RedBossgaugeDeff();
		CollisionBosstoModel();
		CollisionBosstoSkill();
	}
}

//*************
// ボスの描画処理
//*************
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;		// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアルの保存用
	D3DXMATERIAL* pMat;							// マテリアルへのポインタ


	if (g_Boss.bUse == true)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Boss.Object.mtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Boss.Object.Rot.y, g_Boss.Object.Rot.x, g_Boss.Object.Rot.z);
		D3DXMatrixMultiply(&g_Boss.Object.mtxWorld, &g_Boss.Object.mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Boss.Object.Pos.x, g_Boss.Object.Pos.y, g_Boss.Object.Pos.z);
		D3DXMatrixMultiply(&g_Boss.Object.mtxWorld, &g_Boss.Object.mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Boss.Object.mtxWorld);

		// 現在のマテリアルの取得
		pDevice->GetMaterial(&matDef);


		for (int EnemyPartsCount = 0; EnemyPartsCount < g_Boss.BossMotion.nNumModel; EnemyPartsCount++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;
			D3DXMATRIX mtxParent;
			D3DXMatrixIdentity(&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Boss.BossMotion.aModel[EnemyPartsCount].rot.y, g_Boss.BossMotion.aModel[EnemyPartsCount].rot.x, g_Boss.BossMotion.aModel[EnemyPartsCount].rot.z);
			D3DXMatrixMultiply(&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld, &g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld, &mtxRotModel);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_Boss.BossMotion.aModel[EnemyPartsCount].pos.x, g_Boss.BossMotion.aModel[EnemyPartsCount].pos.y, g_Boss.BossMotion.aModel[EnemyPartsCount].pos.z);
			D3DXMatrixMultiply(&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld, &g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld, &mtxTransModel);


			if (g_Boss.BossMotion.aModel[EnemyPartsCount].Parent != -1)
			{
				mtxParent = g_Boss.BossMotion.aModel[g_Boss.BossMotion.aModel[EnemyPartsCount].Parent].mtxWorld;
			}
			else
			{
				mtxParent = g_Boss.Object.mtxWorld;
			}
			D3DXMatrixMultiply(&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld,
				&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld,
				&mtxParent);

			pDevice->SetTransform(D3DTS_WORLD,
				&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld);

			// マテリアルデータへのポインタ
			pMat = (D3DXMATERIAL*)g_Boss.BossMotion.aModel[EnemyPartsCount].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Boss.BossMotion.aModel[EnemyPartsCount].dwNumMat; nCntMat++)
			{
				switch (g_Boss.state)
				{
				case BOSSSTATE_NORMAL:
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					break;
				case BOSSSTATE_KNOCKUP:
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
				pDevice->SetTexture(0, g_Boss.BossMotion.aModel[EnemyPartsCount].pTexture[nCntMat]);

				// モデル(パーツ)の描画
				g_Boss.BossMotion.aModel[EnemyPartsCount].pMesh->DrawSubset(nCntMat);
			}

			DrawPlayerShadow(g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld,
				g_Boss.BossMotion.aModel[EnemyPartsCount].pBuffMat,
				g_Boss.BossMotion.aModel[EnemyPartsCount].pMesh,
				(int)g_Boss.BossMotion.aModel[EnemyPartsCount].dwNumMat,
				g_Boss.BossMotion.aModel[EnemyPartsCount].rot,
				g_Boss.BossMotion.aModel[EnemyPartsCount].pos);

			if (EnemyPartsCount == g_Boss.CollModel)
			{
				BossMatrixWand();
			}

		}
		pDevice->SetMaterial(&matDef);
	}
}

//*************
// ボスの取得処理
//*************
BOSS* GetBoss()
{
	return &g_Boss;
}

void NormalizeBossRot(void)
{
	// 角度の近道
	if (g_Boss.rotDest.y - g_Boss.Object.Rot.y >= D3DX_PI)
	{
		g_Boss.Object.Rot.y += D3DX_PI * 2.0f;
	}
	else if (g_Boss.rotDest.y - g_Boss.Object.Rot.y <= -D3DX_PI)
	{
		g_Boss.Object.Rot.y -= D3DX_PI * 2.0f;
	}
}
//***************
// ボスのヒット処理
//***************
void HitBoss(float Atack)
{
	Player* pPlayer = GetPlayer();
	Camera* pCamera = GetCamera();

	g_Boss.Status.fHP -= (int)Atack;

	g_Boss.Action = BOSSACTION_WELL;
	g_Boss.state = BOSSSTATE_KNOCKUP;
	g_Boss.bHit = true;

	if (pPlayer->Skilltype == SKILLTYPE_EXPLOSION)
	{
		float move = 1.5f;

		D3DXVECTOR3 Vec = g_Boss.Object.Pos - pPlayer->pos;
		D3DXVec3Normalize(&Vec, &Vec);
		g_Boss.move = Vec * move;
	}

	BossgaugeDeff();

	if (Atack >= 10)
	{// ダメージが最小値以上なら
		g_Boss.statecount = 30;
	}
	else
	{// ダメージが最小値以下なら
		g_Boss.statecount = 30;
	}

	if (g_Boss.Status.fHP <= 0.0f && g_Boss.bUse == true)
	{// 使われていて体力が０以下なら
		DeleteEnemyMiniMap(g_Boss.MiniMapIndx);
		DeadBoss();
	}
}

//*************
// ボスの設定処理
//*************
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	MODE nMode = GetMode();

	if (g_Boss.bUse == false)
	{
		g_Boss.bUse = true;
		g_Boss.Object.Pos = pos;
		g_Boss.Object.Rot = rot;
		g_Boss.state = BOSSSTATE_NORMAL;
		g_Boss.IndxShadow = SetShadow(g_Boss.Object.Pos, g_Boss.Object.Rot, 20.0f);
		g_Boss.nActionCount = rand() % 180 + 120;
		g_Boss.MiniMapIndx = SetMapEnemy(pos);

	}
}

//*************
// ボスの死亡処理
//*************
void DeadBoss()
{
	MODE nMode = GetMode();
	Player* pPlayer = GetPlayer();
	Camera* pCamera = GetCamera();

	g_Boss.bUse = false;
	SetPositionShadow(g_Boss.IndxShadow, g_Boss.Object.Pos, g_Boss.bUse);

	SetParticle(g_Boss.Object.Pos,
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

	//ロックオン解除
	if (pPlayer->bLockOn == true)
	{
		if (pPlayer->nLockOnEnemy == 0)
		{
			pPlayer->bLockOn = false;
		}
	}
	AddScore(g_Boss.Status.Score);

	SetGameState(GAMESTATE_CLEAR);
}

void HormingPlayerMove(float Speed)
{
	Player* pPlayer = GetPlayer();
	g_Boss.BossAi.ActionEndCounter++;
	// 敵とプレイヤーの距離計算
	D3DXVECTOR3 vec = pPlayer->pos - g_Boss.Object.Pos;
	float fDistance = (vec.x) * (vec.x) + (vec.z) * (vec.z);
	float fAngle = 0.0f;

	fDistance = (float)sqrt(fDistance);				// 敵とプレイヤーの距離

	// 角度の取得
	fAngle = (float)atan2(vec.x, vec.z);

	// 目標の移動方向（角度）の補正
	if (fAngle > D3DX_PI)
	{
		fAngle -= D3DX_PI * 2.0f;
	}
	else if (fAngle < -D3DX_PI)
	{
		fAngle += D3DX_PI * 2.0f;
	}
	// 移動量の設定
	g_Boss.move.x = sinf(fAngle) * Speed;
	g_Boss.move.z = cosf(fAngle) * Speed;

	// 角度の目標設定
	g_Boss.rotDest.y = fAngle + D3DX_PI;
}
void UpdateBossActionMove()
{
	Player* pPlayer = GetPlayer();
	if (g_Boss.BossMotion.motionType == MOTIONTYPE_MOVE)
	{
		HormingPlayerMove(BOSSHORMING_MOVE);
	}
	else if (g_Boss.BossMotion.motionType == MOTIONTYPE_LOCKON_F_MOVE)
	{
		HormingPlayerMove(BOSSHORMING_MOVE * 10.0f);
		float DistancePlayer = Distance(g_Boss.Object.Pos, pPlayer->pos);
		if (DistancePlayer < 100.0f)
		{
			if (g_Boss.BossMotion.motionType != MOTIONTYPE_DOWN)
			{// モーションの種類設定
				SetMotion(MOTIONTYPE_DOWN, &g_Boss.BossMotion);
			}
		}
	}
}
//***************
// ボスの行動を更新
//***************
void UpdateBossAction()
{
	Player* pPlayer = GetPlayer();					// プレイヤーの情報取得

	// 敵とプレイヤーの距離計算
	D3DXVECTOR3 vec = pPlayer->pos - g_Boss.Object.Pos;
	float fDistance = (vec.x) * (vec.x) + (vec.z) * (vec.z);
	float fAngle = 0.0f;

	fDistance = (float)sqrt(fDistance);				// 敵とプレイヤーの距離

	// 角度の取得
	fAngle = (float)atan2(vec.x, vec.z);

	// 目標の移動方向（角度）の補正
	if (fAngle > D3DX_PI)
	{
		fAngle -= D3DX_PI * 2.0f;
	}
	else if (fAngle < -D3DX_PI)
	{
		fAngle += D3DX_PI * 2.0f;
	}

	FLOAT primaryAction[BOSSACTION_MAX];
	int primaryAction1[BOSSACTION_MAX];
	for (int CopyCount = 0; CopyCount < BOSSACTION_MAX; CopyCount++)
	{
		primaryAction1[CopyCount] = CopyCount;
		primaryAction[CopyCount] = g_Boss.BossAi.primary[CopyCount];
	}
	for (int RankCount = 0; RankCount < BOSSACTION_MAX; RankCount++)
	{
		for (int SortCount = RankCount; SortCount < BOSSACTION_MAX; SortCount++)
		{
			if (primaryAction[RankCount] < primaryAction[SortCount])
			{
				int BackUp = (int)primaryAction[RankCount];
				primaryAction[RankCount] = primaryAction[SortCount];
				primaryAction[SortCount] = (FLOAT)BackUp;
				BackUp = primaryAction1[SortCount];
				primaryAction1[SortCount] = primaryAction1[RankCount];
				primaryAction1[RankCount] = BackUp;
			}
		}
	}
	int Ratio = rand() % 100 + 1;
	if (Ratio <= BOSSACTION_JUSTIS)
	{
		g_Boss.ActionType = (BOSSACTION)primaryAction1[0];
	}
	else
	{
		g_Boss.ActionType = (BOSSACTION)primaryAction1[1];
	}
	// 攻撃
	if (g_Boss.ActionType == BOSSACTION_ATTACK)
	{
		if (pPlayer->state != PLAYERSTATE_KNOCKUP)
		{
			float DistancePlayer = Distance(g_Boss.Object.Pos, pPlayer->pos);
			if (DistancePlayer > 100.0f)
			{
				if (g_Boss.BossMotion.motionType != MOTIONTYPE_LOCKON_F_MOVE)
				{// モーションの種類設定
					SetMotion(MOTIONTYPE_LOCKON_F_MOVE, &g_Boss.BossMotion);
				}
			}
			else if (DistancePlayer < 100.0f)
			{
				if (g_Boss.BossMotion.motionType != MOTIONTYPE_ACTION)
				{// モーションの種類設定
					g_Boss.move.x = 0.0f;
					g_Boss.move.z = 0.0f;
					SetMotion(MOTIONTYPE_ACTION, &g_Boss.BossMotion);
				}
			}
		}
	}
	// 追いかける
	else if (g_Boss.ActionType == BOSSACTION_RUN)
	{
		if (g_Boss.BossMotion.motionType != MOTIONTYPE_ACTION)
		{//モーションの種類設定
			if (g_Boss.BossMotion.motionType != MOTIONTYPE_MOVE)
			{
				g_Boss.BossAi.ActionEnd[g_Boss.BossMotion.motionType] = MOVEEND_FLAME;
				SetMotion(MOTIONTYPE_MOVE, &g_Boss.BossMotion);
			}
		}
	}
	// 様子見
	else
	{
		if (g_Boss.BossMotion.motionType != MOTIONTYPE_NEUTRAL && g_Boss.BossMotion.motionType != MOTIONTYPE_ACTION)
		{
			g_Boss.move.x = 0.0f;
			g_Boss.move.z = 0.0f;
			SetMotion(MOTIONTYPE_NEUTRAL, &g_Boss.BossMotion);
		}
	}
	g_Boss.BossAi.bFinishAction = false;
}

//*****************
// ボスの状態遷移処理
//*****************
void BossState(int Indx)
{

}

//******************
// 敵のオフセット?
//******************
void SetBossPartsInfo(LoadInfo PartsInfo)
{
	g_Boss.nNumModel = PartsInfo.nNumParts;
	g_Boss.BossMotion.nNumModel = PartsInfo.nNumParts;

	for (int PartsCount = 0; PartsCount < g_Boss.nNumModel; PartsCount++)
	{
		g_Boss.BossMotion.aModel[PartsCount].nIndx = PartsInfo.PartsInfo[PartsCount].nIndx;
		g_Boss.BossMotion.aModel[PartsCount].Parent = PartsInfo.PartsInfo[PartsCount].Parent;
		g_Boss.BossMotion.aModel[PartsCount].pos = PartsInfo.PartsInfo[PartsCount].pos;
		g_Boss.BossMotion.aModel[PartsCount].OffSetPos = PartsInfo.PartsInfo[PartsCount].OffSetPos;
		g_Boss.BossMotion.aModel[PartsCount].rot = PartsInfo.PartsInfo[PartsCount].rot;
		g_Boss.BossMotion.aModel[PartsCount].OffSetRot = PartsInfo.PartsInfo[PartsCount].OffSetRot;

		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		HRESULT hresult = D3DXLoadMeshFromX(PartsInfo.cPartsPath[PartsCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Boss.BossMotion.aModel[PartsCount].pBuffMat,
			NULL,
			&g_Boss.BossMotion.aModel[PartsCount].dwNumMat,
			&g_Boss.BossMotion.aModel[PartsCount].pMesh);

		if (FAILED(hresult))
		{
			return;
		}

		int nNumVtx;   // 頂点数
		DWORD sizeFVF; // 頂点フォーマットのサイズ

		// 頂点数取得
		nNumVtx = g_Boss.BossMotion.aModel[PartsCount].pMesh->GetNumVertices();
		// 頂点フォーマットのサイズ取得
		sizeFVF = D3DXGetFVFVertexSize(g_Boss.BossMotion.aModel[PartsCount].pMesh->GetFVF());

		D3DXMATERIAL* pMat;		// マテリアルへのポインタ
		pMat = (D3DXMATERIAL*)g_Boss.BossMotion.aModel[PartsCount].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Boss.BossMotion.aModel[PartsCount].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Boss.BossMotion.aModel[PartsCount].pTexture[nCntMat]); //1
			}
		}
	}
	for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++)
	{
		g_Boss.BossMotion.aMotionInfo[MotionCount] = PartsInfo.MotionInfo[MotionCount];
	}
}

void CollisionBosstoSkill(void)
{
	Skill* pSkill = GetSkill();
	// 魔法との当たり判定
	for (int SkillCount = 0; SkillCount < MAX_SKILL; SkillCount++)
	{
		if (pSkill[SkillCount].bUse == true)
		{
			// 当たり判定
			if (collisioncircle(g_Boss.Object.Pos, g_Boss.Radius, pSkill[SkillCount].pos, SKILL_SIZE) == true)
			{
				pSkill[SkillCount].nLife = 1;
				pSkill[SkillCount].bHit = true;
				HitBoss(pSkill[SkillCount].fPower);
			}
		}
	}
}
void CollisionBosstoModel(void)
{
	STAGEMODEL* pObb = GetModel();
	for (int ModelCount = 0; ModelCount < MAX_STAGEMODEL; ModelCount++, pObb++)
	{
		if (pObb->bUse == true)
		{
			OBB BossObb;
			BossObb.CenterPos = g_Boss.Object.Pos;

			BossObb.fLength[0] = 10.0f;
			BossObb.fLength[1] = 20.0f;
			BossObb.fLength[2] = 10.0f;

			BossObb.RotVec[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			BossObb.RotVec[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			BossObb.RotVec[2] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			bool bCollision = collisionobb(BossObb, pObb->ObbModel, g_Boss.Object.Pos, pObb->pos);
			if (bCollision == true)
			{
				D3DXVECTOR3 VecMove = g_Boss.Object.OldPos - g_Boss.Object.Pos;
				D3DXVECTOR3 NorFace = collisionobbfacedot(pObb->ObbModel, D3DXVECTOR3(g_Boss.Object.Pos.x,
					g_Boss.Object.Pos.y + 10.0f,
					g_Boss.Object.Pos.z), VecMove);
				PushPosition(&g_Boss.Object.Pos, VecMove, NorFace);
			}
		}
	}
}
//==============================
// ボスとプレイヤーの当たり判定
//==============================
void CollisionBoss(void)
{
	Player* pPlayer = GetPlayer();

	if (g_Boss.bUse == true)
	{
		//敵との距離
		g_Boss.fDistance = sqrtf(((g_Boss.Object.Pos.x - pPlayer->pos.x) * (g_Boss.Object.Pos.x - pPlayer->pos.x))
							   + ((g_Boss.Object.Pos.y - pPlayer->pos.y) * (g_Boss.Object.Pos.y - pPlayer->pos.y))
							   + ((g_Boss.Object.Pos.z - pPlayer->pos.z) * (g_Boss.Object.Pos.z - pPlayer->pos.z)));

		float RADIUS = ((PLAYER_RADIUS / 2) + g_Boss.Radius) * ((PLAYER_RADIUS / 2) + g_Boss.Radius);

		if (g_Boss.fDistance <= RADIUS)
		{
			HitPlayer(g_Boss.Status.fPower,g_Boss.Object.Pos);
		}
	}
}

//===================================
// 敵のアクション時の当たり判定処理
//===================================
void CollisionBossAction(void)
{
	Player* pPlayer = GetPlayer();

	float radius = g_Boss.Radius; // 半径
	float division = 0.05f;	// 分割数
	// 親モデル
	int Parent = g_Boss.BossMotion.aModel[g_Boss.CollModel].Parent;

	D3DXVECTOR3 Pos = D3DXVECTOR3(g_Boss.mtxWand._41, g_Boss.mtxWand._42, g_Boss.mtxWand._43);
	D3DXVECTOR3 Pos1 = D3DXVECTOR3(g_Boss.BossMotion.aModel[Parent].mtxWorld._41, g_Boss.BossMotion.aModel[Parent].mtxWorld._42, g_Boss.BossMotion.aModel[Parent].mtxWorld._43);

	D3DXVECTOR3 sabun = Pos1 - Pos;

	for (int n = 0; n < 20; n++)
	{
		D3DXVECTOR3 sabun1 = Pos1 - sabun * division * (float)n;
		D3DXVECTOR3 CollPos = sabun1 - sabun;

		if (collisioncircle(CollPos, radius, pPlayer->pos, PLAYER_RADIUS) == true)
		{
			HitPlayer(g_Boss.Status.fPower, g_Boss.Object.Pos);
			PlaySound(SOUND_LABEL_SLASH);

			break;
		}

#ifdef _DEBUG

#endif
	}
}

//===============
// マトリックス
//===============
void BossMatrixWand(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRotEnemy, mtxTransEnemy;
	D3DXMATRIX mtxParent;
	D3DXMatrixIdentity(&g_Boss.mtxWand);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRotEnemy, g_Boss.BossMotion.aModel[g_Boss.CollModel].rot.y, g_Boss.BossMotion.aModel[g_Boss.CollModel].rot.x, g_Boss.BossMotion.aModel[g_Boss.CollModel].rot.z);
	D3DXMatrixMultiply(&g_Boss.mtxWand, &g_Boss.mtxWand, &mtxRotEnemy);

	// 位置を反映
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 60.0f, 0.0f);

	D3DXMatrixTranslation(&mtxTransEnemy, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_Boss.mtxWand, &g_Boss.mtxWand, &mtxTransEnemy);

	mtxParent = g_Boss.BossMotion.aModel[g_Boss.CollModel].mtxWorld;

	D3DXMatrixMultiply(&g_Boss.mtxWand,
		&g_Boss.mtxWand,
		&mtxParent);

	pDevice->SetTransform(D3DTS_WORLD,
		&g_Boss.mtxWand);
}

float Distance(D3DXVECTOR3 Pos, D3DXVECTOR3 Pos1)
{
	FLOAT Length;
	D3DXVECTOR3 Distance = Pos - Pos1;
	Length = D3DXVec3Length(&Distance);
	return Length;
}
//===================================
//ボスの死亡フラグ取得処理
//===================================
bool DethBoss(void)
{
	return g_Boss.bUse;
}

//*************************
// ボスの行動優先順位を更新
//*************************
void Routine(void)
{
	Player* pPlayer = GetPlayer();

	if (g_Boss.bUse == true)
	{
		//敵との距離
		g_Boss.fDistance = sqrtf(((g_Boss.Object.Pos.x - pPlayer->pos.x) * (g_Boss.Object.Pos.x - pPlayer->pos.x))
			+ ((g_Boss.Object.Pos.y - pPlayer->pos.y) * (g_Boss.Object.Pos.y - pPlayer->pos.y))
			+ ((g_Boss.Object.Pos.z - pPlayer->pos.z) * (g_Boss.Object.Pos.z - pPlayer->pos.z)));

		float RADIUS = ((PLAYER_RADIUS / 2) + BOSSHORMING_DIST) * ((PLAYER_RADIUS / 2) + BOSSHORMING_DIST);

		if (g_Boss.fDistance <= RADIUS)
		{
			g_Boss.BossAi.primary[BOSSACTION_WELL] = 20.0f;
			g_Boss.BossAi.primary[BOSSACTION_RUN] = 50.0f;
			g_Boss.BossAi.primary[BOSSACTION_ATTACK] = 30.0f;
			if (pPlayer->bRolling == true)
			{
				g_Boss.BossAi.primary[BOSSACTION_WELL] = 0.0f;
				g_Boss.BossAi.primary[BOSSACTION_RUN] = 30.0f;
				g_Boss.BossAi.primary[BOSSACTION_ATTACK] = 70.0f;
			}
			if (pPlayer->PlayerMotion.motionType == MOTIONTYPE_ACTION
				|| pPlayer->PlayerMotion.motionType == MOTIONTYPE_ACTION_EXPLOSION
				|| pPlayer->PlayerMotion.motionType == MOTIONTYPE_ACTION_HORMING)
			{
				g_Boss.BossAi.primary[BOSSACTION_WELL] = 0.0f;
				g_Boss.BossAi.primary[BOSSACTION_RUN] = 60.0f;
				g_Boss.BossAi.primary[BOSSACTION_ATTACK] = 40.0f;
			}
		}
	}
}

void EndAction(void)
{
	Player* pPlayer = GetPlayer();
	if (g_Boss.BossMotion.motionType == MOTIONTYPE_ACTION
		&& g_Boss.BossMotion.bFinish == true)
	{
		g_Boss.BossAi.bFinishAction = true;
	}
	else if (g_Boss.BossMotion.motionType == MOTIONTYPE_MOVE)
	{
		//敵との距離
		g_Boss.fDistance = sqrtf(((g_Boss.Object.Pos.x - pPlayer->pos.x) * (g_Boss.Object.Pos.x - pPlayer->pos.x))
			+ ((g_Boss.Object.Pos.y - pPlayer->pos.y) * (g_Boss.Object.Pos.y - pPlayer->pos.y))
			+ ((g_Boss.Object.Pos.z - pPlayer->pos.z) * (g_Boss.Object.Pos.z - pPlayer->pos.z)));

		float RADIUS = ((PLAYER_RADIUS / 2) + BOSSATTACK_DIST) * ((PLAYER_RADIUS / 2) + BOSSATTACK_DIST);

		if (g_Boss.fDistance <= RADIUS || g_Boss.BossAi.ActionEnd[0] < g_Boss.BossAi.ActionEndCounter)
		{
			g_Boss.BossAi.ActionEndCounter = 0;
			g_Boss.BossAi.bFinishAction = true;
		}
	}
	else if (g_Boss.BossMotion.motionType == MOTIONTYPE_NEUTRAL)
	{
		g_Boss.BossAi.bFinishAction = true;
	}
}