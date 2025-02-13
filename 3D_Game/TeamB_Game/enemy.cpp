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
		g_Enemy[i].EnemyMotion.NextKey = 1;									// モーションの次のキー
		g_Enemy[i].EnemyMotion.bBlendMotion = true;
		g_Enemy[i].Object.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);			// 位置
		g_Enemy[i].Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 向き
		g_Enemy[i].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き(目標)
		g_Enemy[i].bUse = false;											// 使用しているかどうか
		g_Enemy[i].nActionCount = 0;										// アクションカウンター
		g_Enemy[i].nActionCounter = 0;										// アクションカウンター
		g_Enemy[i].Action = ENEMYACTION_WELL;								// 行動の種類
		g_Enemy[i].Radius = 4.4f;											// 半径

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

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_Enemy[EnemyCount].bUse == true)
		{
			//行動の更新
			UpdateAction(EnemyCount);

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
				g_Enemy[EnemyCount].statecount = 0;
			}
			g_Enemy[EnemyCount].statecount--;

			//移動量の更新(減衰)
			g_Enemy[EnemyCount].move.x = (0.0f - g_Enemy[EnemyCount].move.x) * 0.1f;
			g_Enemy[EnemyCount].move.y = (0.0f - g_Enemy[EnemyCount].move.y) * 0.1f;
			g_Enemy[EnemyCount].move.z = (0.0f - g_Enemy[EnemyCount].move.z) * 0.1f;

			//床判定
			if (g_Enemy[EnemyCount].Object.Pos.y < 0)
			{
				g_Enemy[EnemyCount].Object.Pos.y = 0;
			}

			g_Enemy[EnemyCount].Object.Rot.y += (g_Enemy[EnemyCount].rotDest.y - g_Enemy[EnemyCount].Object.Rot.y) * 0.05f;

			//影の更新
			SetPositionShadow(g_Enemy[EnemyCount].IndxShadow, g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].bUse);
			SetSizeShadow(g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].IndxShadow);

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
	Camera* pCamera = GetCamera();

	g_Enemy[Indx].Status.fHP -= (int)Atack;

	g_Enemy[Indx].Action = ENEMYACTION_WELL;
	g_Enemy[Indx].state = ENEMYSTATE_KNOCKUP;

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
void SetEnemy(D3DXVECTOR3 pos, int nType,D3DXVECTOR3 rot)
{
	MODE nMode = GetMode();

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_Enemy[EnemyCount].bUse == false)
		{
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

	g_Enemy[Indx].bUse = false;
	g_nNumEnemy--;
	SetPositionShadow(g_Enemy[Indx].IndxShadow,g_Enemy[Indx].Object.Pos,g_Enemy[Indx].bUse);

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

	//ロックオン解除
	if (pPlayer->bLockOn == true)
	{
		if (pPlayer->nLockOnEnemy == Indx)
		{
			pPlayer->bLockOn = false;
			pCamera->rot.y = 0.0f; //カメラ戻す
		}
	}
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
			//g_Enemy[nCount].EnemyMotion.motionType = MOTIONTYPE_ACTION;//多分これしか機能していない
			//g_Enemy[nCount].EnemyMotion.motionTypeBlend = MOTIONTYPE_NEUTRAL;
			//g_Enemy[nCount].EnemyMotion.nFrameBlend = 10.0f;
			//g_Enemy[nCount].EnemyMotion.nKey = 0;
			//g_Enemy[nCount].EnemyMotion.NextKey = 1;
			SetMotion(MOTIONTYPE_ACTION, &g_Enemy[nCount].EnemyMotion);
		}
	}
	//追いかける
	else if (fDistance <= HOMING_DIST)
	{
		if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_ACTION)
		{
			//モーションの種類設定
			g_Enemy[nCount].ActionType = ENEMYACTION_RUN;
			//g_Enemy[nCount].EnemyMotion.motionType = MOTIONTYPE_MOVE;//多分これしか機能していない
			//g_Enemy[nCount].EnemyMotion.motionTypeBlend = MOTIONTYPE_NEUTRAL;
			//g_Enemy[nCount].EnemyMotion.nFrameBlend = 10.0f;

			//移動量の設定
			g_Enemy[nCount].move.x = sinf(fAngle) * HOMING_MOVE;
			g_Enemy[nCount].move.z = cosf(fAngle) * HOMING_MOVE;

			//位置の更新
			g_Enemy[nCount].Object.Pos += g_Enemy[nCount].move;

			//角度の目標設定
			g_Enemy[nCount].rotDest.y = fAngle + D3DX_PI;

			if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_MOVE)
			{
				SetMotion(MOTIONTYPE_MOVE, &g_Enemy[nCount].EnemyMotion);
			}

		}
	}
	//様子見
	else
	{
		g_Enemy[nCount].ActionType = ENEMYACTION_WELL;
		//g_Enemy[nCount].EnemyMotion.motionType = MOTIONTYPE_NEUTRAL;
		//g_Enemy[nCount].pMotion = MOTIONTYPE_NEUTRAL;
		if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_NEUTRAL && g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_ACTION)
		{
			SetMotion(MOTIONTYPE_NEUTRAL, &g_Enemy[nCount].EnemyMotion);
		}
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
				pPlayer->Status.fHP -= g_Enemy[nCntEnemy].Status.fPower;
			}
		}
	}
}

//========================
// 距離の取得
//========================
float GetfDistance()
{
	return g_fDistance[0];
}