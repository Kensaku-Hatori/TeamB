//=================================
//
// プレイヤー表示処理[player.cpp]
// Author:kaiti
//
//=================================

#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"
#include "wall.h"
#include "timer.h"
#include "polygon.h"
#include "sound.h"
#include "skill.h"
#include "animation.h"
#include "enemy.h"
#include "game.h"
#include"impact.h"

//グローバル変数
Player g_player;
D3DXVECTOR3 g_vtxMinPlayer;//プレイヤーの最小値
D3DXVECTOR3 g_vtxMaxPlayer;//プレイヤーの最大値

int g_nCntHealMP;
//=====================
// プレイヤーの初期化
//=====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 400.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.rot, 20.0f);//影の設定
	g_player.nJump = PLAYER_JUMP;

	//モーション関連
	g_player.bLoopMotion = true;//ループ
	g_player.nNumKey = 2;//キーの総数
	g_player.nCntMotion = 0;//モーションカウンター
	g_player.nKey = 0;//現在のキーNo
	g_player.nNumModel = 13;//パーツの総数

	g_player.bJump = false;//ジャンプ

	//基礎ステータス
	g_player.Status.fHP = PLAYER_HP;
	g_player.Status.nMP = PLAYER_MP;
	g_player.Status.fPower = PLAYER_MP;
	g_player.Status.fSpeed = PLAYER_SPEED;

	g_player.fDistance = PLAYER_RADIUS / 2;
	g_player.bLockOn = false;

	g_player.sightAngle = 0;
	g_player.sightRange = 0;

	g_nCntHealMP = 0;
}
//=======================
// プレイヤーの終了処理
//=======================
void UninitPlayer(void)
{
	//プレイヤーの破棄
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		//メッシュの破棄
		if (g_player.PlayerMotion.aModel[nCnt].pMesh != NULL)
		{
			g_player.PlayerMotion.aModel[nCnt].pMesh->Release();
			g_player.PlayerMotion.aModel[nCnt].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_player.PlayerMotion.aModel[nCnt].pBuffMat != NULL)
		{
			g_player.PlayerMotion.aModel[nCnt].pBuffMat->Release();
			g_player.PlayerMotion.aModel[nCnt].pBuffMat = NULL;
		}
	}
}
//=======================
// プレイヤーの更新処理
//=======================
void UpdatePlayer(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	if (g_player.bUse == true)
	{
		SetPositionShadow(g_player.nIdxShadow, g_player.pos, g_player.bUse);//影
		SetSizeShadow(g_player.pos, g_player.nIdxShadow, g_player.bJump);

		PlayerMove();

		// 角度の近道
		if (g_player.rotDest.y - g_player.rot.y >= D3DX_PI)
		{
			g_player.rot.y += D3DX_PI * 2.0f;
		}
		else if (g_player.rotDest.y - g_player.rot.y <= -D3DX_PI)
		{
			g_player.rot.y -= D3DX_PI * 2.0f;
		}

		g_player.rot += (g_player.rotDest - g_player.rot) * 0.5f;


		//魔法発射
		if ((KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_B) == true))
		{// MPが５０以上の時
			if (g_player.Status.nMP >= 50)
			{
				SetSkill(g_player.pos, g_player.move, g_player.rot);
				g_player.Status.nMP -= 50; //MP消費
			}
			SetMotion(MOTIONTYPE_ACTION,&g_player.PlayerMotion);
		}

		//MP回復
		if (g_player.Status.nMP < PLAYER_MP)
		{//MPが減っていたら
			g_nCntHealMP++;
		}
		if (g_nCntHealMP >= 60)
		{
			g_player.Status.nMP += 10;
			g_nCntHealMP = 0;
		}

		//ジャンプ
		if ((KeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A) == true))
		{// SPACE
			if (g_player.bJump == false)
			{
				SetMotion(MOTIONTYPE_JUMP, &g_player.PlayerMotion);
				g_player.bJump = true;
				g_player.move.y += g_player.nJump;
			}
		}

		g_player.move.y -= 0.3f; //重力加算

		//前回の位置を保存
		g_player.posOld = g_player.pos;

		//位置を更新
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;
		g_player.pos.z += g_player.move.z;

		CollisionEnemy();

		//ロックオン
		if ((KeyboardTrigger(DIK_R) == true || GetJoypadTrigger(JOYKEY_R1) == true))
		{
			g_player.bLockOn = IsEnemyInsight();
		}

		// HP0
		if (g_player.Status.fHP <= 0.0f)
		{
			SetGameState(GAMESTATE_GAMEOVER);
		}

		//地面との判定
		if (g_player.pos.y <= 0)
		{
			if (g_player.bJump == true)
			{
				g_player.bJump = false;
				if (g_player.PlayerMotion.motionType != MOTIONTYPE_LANDING)
				{
					SetMotion(MOTIONTYPE_LANDING, &g_player.PlayerMotion);
				}
			}
			g_player.pos.y = 0.0;
			g_player.move.y = 0.0;
		}

		//移動量を更新
		g_player.move.x = 0.0f;
		g_player.move.z = 0.0f;


#ifdef _DEBUG
		//位置を０に
		if (KeyboardTrigger(DIK_0) == true)
		{
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 400.0f);
			g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 400.0f);
		}
		//HP減らす
		if (KeyboardTrigger(DIK_9) == true)
		{
			g_player.Status.fHP -= 100;
			if (g_player.Status.fHP <= 0)
			{
				g_player.Status.fHP = 0;
			}
		}
		if (KeyboardTrigger(DIK_8) == true)
		{
			g_player.Status.nMP = PLAYER_MP;
			g_player.Status.fHP = PLAYER_HP;
		}
#endif
		UpdateMotion(&g_player.PlayerMotion);
	}
}
//===================
// プレイヤーの描画
//===================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	if (g_player.bUse == true)
	{
		//計算用マトリックス
		D3DXMATRIX mtxRot, mtxTrans;
		//現在のマテリアル保存用
		D3DMATERIAL9 matDef;
		//マテリアルデータへのポインタ
		D3DXMATERIAL* pMat;

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.mtxWorld);

		//向きを反転
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//全パーツの描画
		for (int nCntModel = 0; nCntModel < g_player.PlayerMotion.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;
			D3DXMATRIX mtxParent;

			//パーツのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_player.PlayerMotion.aModel[nCntModel].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.PlayerMotion.aModel[nCntModel].rot.y, g_player.PlayerMotion.aModel[nCntModel].rot.x, g_player.PlayerMotion.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player.PlayerMotion.aModel[nCntModel].mtxWorld, &g_player.PlayerMotion.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_player.PlayerMotion.aModel[nCntModel].pos.x, g_player.PlayerMotion.aModel[nCntModel].pos.y, g_player.PlayerMotion.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player.PlayerMotion.aModel[nCntModel].mtxWorld, &g_player.PlayerMotion.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスの設定
			if (g_player.PlayerMotion.aModel[nCntModel].Parent != -1)
			{
				mtxParent = g_player.PlayerMotion.aModel[g_player.PlayerMotion.aModel[nCntModel].Parent].mtxWorld;
			}
			else
			{
				mtxParent = g_player.mtxWorld;
			}

			//パーツのワールドマトリックスの設定
			D3DXMatrixMultiply(&g_player.PlayerMotion.aModel[nCntModel].mtxWorld,
				&g_player.PlayerMotion.aModel[nCntModel].mtxWorld,
				&mtxParent);
			
			//パーツのワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD,
				&g_player.PlayerMotion.aModel[nCntModel].mtxWorld);
			
			//パーツの描画
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_player.PlayerMotion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player.PlayerMotion.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャの設定
				pDevice->SetTexture(0, g_player.PlayerMotion.aModel[nCntModel].pTexture[nCntMat]);
				//プレイヤーの描画
				g_player.PlayerMotion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}
//======================
// プレイヤーの移動
//======================
void PlayerMove(void)
{
	Camera* pCamera;
	pCamera = GetCamera();

	//移動
	//左
	if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT))
	{
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_MOVE && g_player.PlayerMotion.motionType != MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
		}
		//前
		if (GetKeyboardPress(DIK_W)|| GetJoypadPress(JOYKEY_DOWN))
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
		}
		//後
		else if (GetKeyboardPress(DIK_S)|| GetJoypadPress(JOYKEY_UP))
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
		}
		else
		{
			g_player.move.x += cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2;
		}
	}
	//右
	else if (GetKeyboardPress(DIK_D)|| GetJoypadPress(JOYKEY_RIGET))
	{
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_MOVE && g_player.PlayerMotion.motionType != MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
		}

		//前
		if (GetKeyboardPress(DIK_W)|| GetJoypadPress(JOYKEY_DOWN))
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
		}
		//後
		else if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_UP))
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
		}
		else
		{
			g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z += sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2;
		}
	}
	//前
	else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_DOWN) == true)
	{
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_MOVE && g_player.PlayerMotion.motionType != MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
		}

		//左
		if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_DOWN))
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
		}
		//右
		else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_UP))
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
		}
		else
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI;
		}
	}
	//後
	else if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_UP))
	{
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_MOVE && g_player.PlayerMotion.motionType != MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
		}

		//左
		if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_DOWN))
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
		}
		//右
		else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_UP))
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
		}
		else
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y;
		}
	}
	//
	else
	{
		if (g_player.PlayerMotion.motionType == MOTIONTYPE_MOVE)
		{
			SetMotion(MOTIONTYPE_NEUTRAL, &g_player.PlayerMotion);
		}
	}

	//移動制限
	if (g_player.pos.x <= -945.0f)
	{
		g_player.pos.x = -945.0f;
	}
	if (g_player.pos.x >= 945.0f)
	{
		g_player.pos.x = 945.0f;
	}
	if (g_player.pos.z <= -945.0f)
	{
		g_player.pos.z = -945.0f;
	}
	if (g_player.pos.z >= 945.0f)
	{
		g_player.pos.z = 945.0f;
	}
}
//===================
// プレイヤーの取得
//===================
Player* GetPlayer(void)
{
	return &g_player;
}
void SetMesh(char* pFilePath, int Indx)
{

}

void SetPartsInfo(LoadInfo PartsInfo)
{
	g_player.PlayerMotion.nNumModel = PartsInfo.nNumParts;
	g_player.nNumModel = PartsInfo.nNumParts;
	for (int PartsCount = 0; PartsCount < g_player.PlayerMotion.nNumModel; PartsCount++)
	{
		g_player.PlayerMotion.aModel[PartsCount].nIndx = PartsInfo.PartsInfo[PartsCount].nIndx;
		g_player.PlayerMotion.aModel[PartsCount].Parent = PartsInfo.PartsInfo[PartsCount].Parent;
		g_player.PlayerMotion.aModel[PartsCount].pos = PartsInfo.PartsInfo[PartsCount].pos;
		g_player.PlayerMotion.aModel[PartsCount].OffSet = PartsInfo.PartsInfo[PartsCount].OffSet;
		g_player.PlayerMotion.aModel[PartsCount].rot = PartsInfo.PartsInfo[PartsCount].rot;

		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		HRESULT hresult = D3DXLoadMeshFromX(PartsInfo.cPartsPath[PartsCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.PlayerMotion.aModel[PartsCount].pBuffMat,
			NULL,
			&g_player.PlayerMotion.aModel[PartsCount].dwNumMat,
			&g_player.PlayerMotion.aModel[PartsCount].pMesh);

		if (FAILED(hresult))
		{
			return;
		}
		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファへのポインタ

		//頂点数取得
		nNumVtx = g_player.PlayerMotion.aModel[PartsCount].pMesh->GetNumVertices();
		//頂点フォーマットのサイズ取得
		sizeFVF = D3DXGetFVFVertexSize(g_player.PlayerMotion.aModel[PartsCount].pMesh->GetFVF());
		//頂点バッファのロック
		g_player.PlayerMotion.aModel[PartsCount].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してプレイヤーの最小値、最大値を取得
			//最小値
			if (vtx.x < g_vtxMinPlayer.x)
			{
				g_vtxMinPlayer.x = vtx.x;
			}
			if (vtx.y < g_vtxMinPlayer.y)
			{
				g_vtxMinPlayer.y = vtx.y;
			}
			if (vtx.z < g_vtxMinPlayer.z)
			{
				g_vtxMinPlayer.z = vtx.z;
			}
			//最大値
			if (vtx.x > g_vtxMaxPlayer.x)
			{
				g_vtxMaxPlayer.x = vtx.x;
			}
			if (vtx.y > g_vtxMaxPlayer.y)
			{
				g_vtxMaxPlayer.y = vtx.y;
			}
			if (vtx.z > g_vtxMaxPlayer.z)
			{
				g_vtxMaxPlayer.z = vtx.z;
			}
			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		g_player.size = D3DXVECTOR3(g_vtxMaxPlayer.x - g_vtxMinPlayer.x, g_vtxMaxPlayer.y - g_vtxMinPlayer.y, g_vtxMaxPlayer.z - g_vtxMinPlayer.z);

		//頂点バッファのアンロック
		g_player.PlayerMotion.aModel[PartsCount].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ
		pMat = (D3DXMATERIAL*)g_player.PlayerMotion.aModel[PartsCount].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.PlayerMotion.aModel[PartsCount].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_player.PlayerMotion.aModel[PartsCount].pTexture[nCntMat]); //1
			}
		}
	}
	for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++)
	{
		g_player.PlayerMotion.aMotionInfo[MotionCount] = PartsInfo.MotionInfo[MotionCount];
	}
	g_player.bUse = true;
}

void PlayerMotion(MOTIONINFO *pMotionInfo)
{
	for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++, pMotionInfo++)
	{
		g_player.PlayerMotion.aMotionInfo[MotionCount] = *pMotionInfo;
	}
	g_player.bUse = true;
}
//
//
//
bool IsEnemyInsight(void)
{
	ENEMY* pEnemy = GetEnemy();

	D3DXVECTOR3 playerFront;

	playerFront.x = -sinf(g_player.rot.y);
	playerFront.y = 0.0f;
	playerFront.z = -cosf(g_player.rot.y);

	D3DXVECTOR3 toEnemy;

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			toEnemy.x = pEnemy->Object.Pos.x - g_player.pos.x;
			toEnemy.y = 0.0f;
			toEnemy.z = pEnemy->Object.Pos.z - g_player.pos.z;

			D3DXVec3Normalize(&playerFront, &playerFront);

			D3DXVec3Normalize(&toEnemy, &toEnemy);

			float dotProduct = D3DXVec3Dot(&playerFront, &toEnemy);

			if (dotProduct > cosf(g_player.sightAngle * 0.5f))
			{
				float distanceSquared =
					(g_player.pos.x - pEnemy->Object.Pos.x) * (g_player.pos.x - pEnemy->Object.Pos.x) +
					(g_player.pos.y - pEnemy->Object.Pos.y) * (g_player.pos.y - pEnemy->Object.Pos.y) +
					(g_player.pos.z - pEnemy->Object.Pos.z) * (g_player.pos.z - pEnemy->Object.Pos.z);

				if (distanceSquared <= g_player.sightRange * g_player.sightRange)
				{
					EnemyDistanceSort(EnemyCount);
					return true;
				}
			}
		}
	}
	return false;
}
//
//
//
void EnemyDistanceSort(int EnemyCount)
{
	ENEMY* pEnemy = GetEnemy();

	//敵との距離
	pEnemy[EnemyCount].fDistance = sqrtf(((pEnemy[EnemyCount].Object.Pos.x - g_player.pos.x) * (pEnemy[EnemyCount].Object.Pos.x - g_player.pos.x))
									   + ((pEnemy[EnemyCount].Object.Pos.y - g_player.pos.y) * (pEnemy[EnemyCount].Object.Pos.y - g_player.pos.y))
									   + ((pEnemy[EnemyCount].Object.Pos.z - g_player.pos.z) * (pEnemy[EnemyCount].Object.Pos.z - g_player.pos.z)));

	float RADIUS = (g_player.fDistance + pEnemy[EnemyCount].Radius) * (g_player.fDistance + pEnemy[EnemyCount].Radius);

	if (pEnemy[EnemyCount].fDistance <= RADIUS)
	{

	}
}
