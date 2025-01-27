//*************
// インクルード
///************
#include "enemy.h"
#include "camera.h"
#include "particle.h"
#include "wall.h"
#include "loadmotion.h"
#include "shadow.h"

//*******************
// グローバル変数宣言
//*******************
ENEMY g_Enemy[MAX_ENEMY];
EnemyOrigin g_EnemyOrigin[ENEMYTYPE_MAX];
int g_nNumEnemy;
int g_nTypeCount = 0;
int g_PartsNum = 0;

//***************
// 敵の初期化処理
//***************
void InitEnemy(void)
{
	g_nNumEnemy = -1;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_Enemy[i].Object.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
		g_Enemy[i].Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[i].bUse = false;
		g_Enemy[i].pMotion = MOTIONTYPE_NEUTRAL;
		g_Enemy[i].nActionCount = 0;
		g_Enemy[i].nActionCounter = 0;
		g_Enemy[i].Action = ENEMYACTION_WELL;
		g_Enemy[i].Status.fPower = 0.0f;
		g_Enemy[i].Status.fSpeed = 1.0f;
		g_Enemy[i].Status.nHP = 150;
		g_Enemy[i].state = ENEMYSTATE_NORMAL;
		g_Enemy[i].Radius = 4.4f;
	}
}
//*************
// 敵の終了処理
//*************
void UninitEnemy(void)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		for (int i1 = 0; i1 < MAX_ENEMYPARTS; i1++)
		{
			// メッシュの破棄
			if (g_Enemy[i].aModel[i1].pMesh != NULL)
			{
				g_Enemy[i].aModel[i1].pMesh = NULL;
			}
			// マテリアルの破棄
			if (g_Enemy[i].aModel[i1].pBuffMat != NULL)
			{
				g_Enemy[i].aModel[i1].pBuffMat = NULL;
			}
			for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
			{
				if (g_Enemy[i].aModel[i1].pTexture[TexCount] != NULL)
				{
					g_Enemy[i].aModel[i1].pTexture[TexCount] = NULL;
				}
			}
		}
	}
	for (int OriginCount = 0; OriginCount < ENEMYTYPE_MAX; OriginCount++)
	{
		for (int PartsCount = 0; PartsCount < MAX_PARTS; PartsCount++)
		{
			if (g_EnemyOrigin[OriginCount].EnemyOriginBuff[PartsCount].pMesh != NULL)
			{
				g_EnemyOrigin[OriginCount].EnemyOriginBuff[PartsCount].pMesh->Release();
				g_EnemyOrigin[OriginCount].EnemyOriginBuff[PartsCount].pMesh = NULL;
			}
			if (g_EnemyOrigin[OriginCount].EnemyOriginBuff[PartsCount].pBuffMat != NULL)
			{
				g_EnemyOrigin[OriginCount].EnemyOriginBuff[PartsCount].pBuffMat->Release();
				g_EnemyOrigin[OriginCount].EnemyOriginBuff[PartsCount].pBuffMat = NULL;
			}
			for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
			{
				if (g_EnemyOrigin[OriginCount].EnemyOriginBuff[PartsCount].pTexture != NULL)
				{
					g_EnemyOrigin[OriginCount].EnemyOriginBuff[PartsCount].pTexture[TexCount]->Release();
					g_EnemyOrigin[OriginCount].EnemyOriginBuff[PartsCount].pTexture[TexCount] = NULL;
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

		}
	}
}
//*************
// 敵の描画処理
//*************
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;				// 計算用マトリックス
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
				D3DXMatrixIdentity(&g_Enemy[EnemyCount].aModel[EnemyPartsCount].mtxWorld);

				// 向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[EnemyCount].aModel[EnemyPartsCount].rot.y, g_Enemy[EnemyCount].aModel[EnemyPartsCount].rot.x, g_Enemy[EnemyCount].aModel[EnemyPartsCount].rot.z);
				D3DXMatrixMultiply(&g_Enemy[EnemyCount].aModel[EnemyPartsCount].mtxWorld, &g_Enemy[EnemyCount].aModel[EnemyPartsCount].mtxWorld, &mtxRotModel);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTransModel, g_Enemy[EnemyCount].aModel[EnemyPartsCount].pos.x, g_Enemy[EnemyCount].aModel[EnemyPartsCount].pos.y, g_Enemy[EnemyCount].aModel[EnemyPartsCount].pos.z);
				D3DXMatrixMultiply(&g_Enemy[EnemyCount].aModel[EnemyPartsCount].mtxWorld, &g_Enemy[EnemyCount].aModel[EnemyPartsCount].mtxWorld, &mtxTransModel);


				if (g_Enemy[EnemyCount].aModel[EnemyPartsCount].Parent != -1)
				{
					mtxParent = g_Enemy[EnemyCount].aModel[g_Enemy[EnemyCount].aModel[EnemyPartsCount].Parent].mtxWorld;
				}
				else
				{
					mtxParent = g_Enemy[EnemyCount].Object.mtxWorld;
				}
				D3DXMatrixMultiply(&g_Enemy[EnemyCount].aModel[EnemyPartsCount].mtxWorld,
					&g_Enemy[EnemyCount].aModel[EnemyPartsCount].mtxWorld,
					&mtxParent);

				pDevice->SetTransform(D3DTS_WORLD,
					&g_Enemy[EnemyCount].aModel[EnemyPartsCount].mtxWorld);

				// マテリアルデータへのポインタ
				pMat = (D3DXMATERIAL*)g_Enemy[EnemyCount].aModel[EnemyPartsCount].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Enemy[EnemyCount].aModel[EnemyPartsCount].dwNumMat; nCntMat++)
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
					pDevice->SetTexture(0, g_Enemy[EnemyCount].aModel[EnemyPartsCount].pTexture[nCntMat]);

					// モデル(パーツ)の描画
					g_Enemy[EnemyCount].aModel[EnemyPartsCount].pMesh->DrawSubset(nCntMat);
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

	g_Enemy[Indx].Status.nHP -= (int)Atack;

	g_Enemy[Indx].Action = ENEMYACTION_WELL;
	g_Enemy[Indx].state = ENEMYSTATE_KNOCKUP;

	if (Atack >= 10)
	{// ダメージが最小値以上なら
		g_Enemy[Indx].statecount = (int)Atack * 3;
	}
	else
	{// ダメージが最小値以下なら
		g_Enemy[Indx].statecount = 10;
	}

	if (g_Enemy[Indx].Status.nHP <= 0.0f && g_Enemy[Indx].bUse == true)
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
			for (int PartsCount = 0; PartsCount < g_EnemyOrigin[nType].nNumParts; PartsCount++)
			{
				g_Enemy[EnemyCount].aModel[PartsCount].dwNumMat = g_EnemyOrigin[nType].EnemyOriginBuff[PartsCount].dwNumMat;
				g_Enemy[EnemyCount].aModel[PartsCount].pBuffMat = g_EnemyOrigin[nType].EnemyOriginBuff[PartsCount].pBuffMat;
				g_Enemy[EnemyCount].aModel[PartsCount].pMesh = g_EnemyOrigin[nType].EnemyOriginBuff[PartsCount].pMesh;
			}
			g_Enemy[EnemyCount].IndxShadow = SetShadow(g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].Object.Rot,g_Enemy[EnemyCount].Radius);
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
// 敵の脂肪処理
//*************
void DeadEnemy(int Indx)
{
	MODE nMode = GetMode();

	g_Enemy[Indx].bUse = false;
	g_nNumEnemy--;
	SetPositionShadow(g_Enemy[Indx].IndxShadow,g_Enemy[Indx].Object.Pos,g_Enemy[Indx].bUse);
	SetParticle(g_Enemy[Indx].Object.Pos, D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PARTICLE_NONE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 50);
}
//***************
// 敵の行動を更新
//***************
void UpdateAction(int nCount)
{

}
//*****************
// 敵の状態遷移処理

void EnemyState(int Indx)
{

}
void SetnNumParts(int nType,int nNumParts)
{
	g_EnemyOrigin[nType - 1].nNumParts = nNumParts;
}
void SetEnemyMesh(char* pFilePath, int Indx)
{
	HRESULT Hresult;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Xファイルの読み込み
	Hresult = D3DXLoadMeshFromX(pFilePath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_EnemyOrigin[g_nTypeCount].EnemyOriginBuff[Indx].pBuffMat,
		NULL,
		&g_EnemyOrigin[g_nTypeCount].EnemyOriginBuff[Indx].dwNumMat,
		&g_EnemyOrigin[g_nTypeCount].EnemyOriginBuff[Indx].pMesh);

	D3DXMATERIAL* pMat;//マテリアルへのポインタ
	pMat = (D3DXMATERIAL*)g_EnemyOrigin[g_nTypeCount].EnemyOriginBuff[Indx].pBuffMat->GetBufferPointer();
	for (int nCntBlockMat = 0; nCntBlockMat < (int)g_EnemyOrigin[g_nTypeCount].EnemyOriginBuff[Indx].dwNumMat; nCntBlockMat++)
	{
		if (pMat[nCntBlockMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntBlockMat].pTextureFilename,
				&g_EnemyOrigin[g_nTypeCount].EnemyOriginBuff[Indx].pTexture[nCntBlockMat]); //1
		}
	}

	if (FAILED(Hresult))
	{
		return;
	}
	if (Indx == g_EnemyOrigin[g_nTypeCount].nNumParts - 1)
	{
		g_nTypeCount++;
	}
}
void SetEnemyPartsInfo(MODELINFO ModelInfo, int Indx)
{

}
void EnemyMotion(MOTIONINFO* pMotionInfo)
{

}