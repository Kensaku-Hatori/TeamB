//*********************************************************
// 
// boss[boss.cpp]
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
}
//*************
// ボスの終了処理
//*************
void UninitBoss(void)
{
	for (int PartsCount = 0; PartsCount < MAX_PARTS; PartsCount++)
	{ 
		// メッシュの破棄
		if (g_Boss.BossMotion.aModel[PartsCount].pMesh != NULL)
		{
			g_Boss.BossMotion.aModel[PartsCount].pMesh->Release();
			g_Boss.BossMotion.aModel[PartsCount].pMesh = NULL;
		}

		// マテリアルの破棄
		if (g_Boss.BossMotion.aModel[PartsCount].pBuffMat != NULL)
		{
			g_Boss.BossMotion.aModel[PartsCount].pBuffMat->Release();
			g_Boss.BossMotion.aModel[PartsCount].pBuffMat = NULL;
		}

		for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
		{//テクスチャの破棄
			if (g_Boss.BossMotion.aModel[PartsCount].pTexture[TexCount] != NULL)
			{
				g_Boss.BossMotion.aModel[PartsCount].pTexture[TexCount]->Release();
				g_Boss.BossMotion.aModel[PartsCount].pTexture[TexCount] = NULL;
			}
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

	if (g_Boss.bUse == true)
	{
		// 行動の更新
		UpdateBossAction();

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
					HitBoss(pPlayer->Status.fPower);
				}
			}
		}

		if (g_Boss.BossMotion.motionType == MOTIONTYPE_ACTION)
		{
			CollisionBossAction();
		}

		//ロックオン
		if (pPlayer->bWantLockOn == true)
		{
			if (IsEnemyInsight(g_Boss.Object.Pos, 1) == true)
			{
				pPlayer->bLockOn = true;
			}
		}

		// 角度の近道
		if (g_Boss.rotDest.y - g_Boss.Object.Rot.y >= D3DX_PI)
		{
			g_Boss.Object.Rot.y += D3DX_PI * 2.0f;
		}
		else if (g_Boss.rotDest.y - g_Boss.Object.Rot.y <= -D3DX_PI)
		{
			g_Boss.Object.Rot.y -= D3DX_PI * 2.0f;
		}

		if (g_Boss.statecount <= 0)
		{
			g_Boss.state = BOSSSTATE_NORMAL;
			g_Boss.statecount = 0;
		}
		g_Boss.statecount--;

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

//***************
// ボスのヒット処理
//***************
void HitBoss(float Atack)
{
	Camera* pCamera = GetCamera();

	g_Boss.Status.fHP -= (int)Atack;

	g_Boss.Action = BOSSACTION_WELL;
	g_Boss.state = BOSSSTATE_KNOCKUP;

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

	SetFade(MODE_RESULT);
	SetResult(RESULT_CLEAR);
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

	// 攻撃
	if (fDistance <= BOSSATTACK_DIST)
	{
		if (pPlayer->state != PLAYERSTATE_KNOCKUP)
		{
			if (g_Boss.BossMotion.motionType != MOTIONTYPE_ACTION)
			{// モーションの種類設定
				g_Boss.ActionType = BOSSACTION_ATTACK;
				//g_Boss[nCount].BossMotion.motionType = MOTIONTYPE_ACTION;//多分これしか機能していない
				//g_Boss[nCount].BossMotion.motionTypeBlend = MOTIONTYPE_NEUTRAL;
				//g_Boss[nCount].BossMotion.nFrameBlend = 10.0f;
				//g_Boss[nCount].BossMotion.nKey = 0;
				//g_Boss[nCount].BossMotion.NextKey = 1;
				SetMotion(MOTIONTYPE_ACTION, &g_Boss.BossMotion);
			}
		}
	}
	// 追いかける
	else if (fDistance <= BOSSHORMING_DIST)
	{
		if (g_Boss.BossMotion.motionType != MOTIONTYPE_ACTION)
		{//モーションの種類設定
			g_Boss.ActionType = BOSSACTION_RUN;
			//g_Boss[nCount].BossMotion.motionType = MOTIONTYPE_MOVE;//多分これしか機能していない
			//g_Boss[nCount].BossMotion.motionTypeBlend = MOTIONTYPE_NEUTRAL;
			//g_Boss[nCount].BossMotion.nFrameBlend = 10.0f;

			// 移動量の設定
			g_Boss.move.x = sinf(fAngle) * BOSSHORMING_MOVE;
			g_Boss.move.z = cosf(fAngle) * BOSSHORMING_MOVE;

			// 角度の目標設定
			g_Boss.rotDest.y = fAngle + D3DX_PI;

			if (g_Boss.BossMotion.motionType != MOTIONTYPE_MOVE)
			{
				SetMotion(MOTIONTYPE_MOVE, &g_Boss.BossMotion);
			}
		}
	}
	// 様子見
	else
	{
		g_Boss.ActionType = BOSSACTION_WELL;
		//g_Boss[nCount].BossMotion.motionType = MOTIONTYPE_NEUTRAL;
		//g_Boss[nCount].pMotion = MOTIONTYPE_NEUTRAL;
		if (g_Boss.BossMotion.motionType != MOTIONTYPE_NEUTRAL && g_Boss.BossMotion.motionType != MOTIONTYPE_ACTION)
		{
			SetMotion(MOTIONTYPE_NEUTRAL, &g_Boss.BossMotion);
		}
	}
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

	if (collisioncircle(g_Boss.BossMotion.aModel[12].pos, g_Boss.Radius * 1.5f, pPlayer->pos, PLAYER_RADIUS) == true)
	{
		HitPlayer(g_Boss.Status.fPower,g_Boss.Object.Pos);
	}
}

//===================================
//ボスの死亡フラグ取得処理
//===================================
bool DethBoss(void)
{
	return g_Boss.bUse;
}