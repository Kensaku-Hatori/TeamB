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
#include "block.h"
#include "wall.h"
#include "enemy.h"
#include "motion.h"
#include "timer.h"
#include "polygon.h"
#include "sound.h"
#include "skill.h"

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

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.rot, 20.0f);//影の設定
	g_player.nJump = PLAYER_JUMP;
	//モーション関連
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	g_player.bLoopMotion = true;//ループ
	g_player.nNumKey = 2;//キーの総数
	g_player.nCntMotion = 0;//モーションカウンター
	g_player.nKey = 0;//現在のキーNo
	g_player.nNumModel = 13;//パーツの総数

	g_player.bJump = false;//ジャンプ
	g_player.bUse = true;

	//基礎ステータス
	g_player.Status.nHP = PLAYER_HP;
	g_player.Status.nMP = PLAYER_MP;
	g_player.Status.fSpeed = PLAYER_SPEED;


	g_nCntHealMP = 0;

	LoadPlayer();

	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファへのポインタ

		//頂点数取得
		nNumVtx = g_player.aModel[nCnt].pMesh->GetNumVertices();
		//頂点フォーマットのサイズ取得
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCnt].pMesh->GetFVF());
		//頂点バッファのロック
		g_player.aModel[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

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
		g_player.aModel[nCnt].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ
		pMat = (D3DXMATERIAL*)g_player.aModel[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_player.aModel[nCnt].pTexture[nCnt]); //1
			}
		}
	}
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
		if (g_player.aModel[nCnt].pMesh != NULL)
		{
			g_player.aModel[nCnt].pMesh->Release();
			g_player.aModel[nCnt].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_player.aModel[nCnt].pBuffMat != NULL)
		{
			g_player.aModel[nCnt].pBuffMat->Release();
			g_player.aModel[nCnt].pBuffMat = NULL;
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

		//移動
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_player.move.z += sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.x += cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2;
		}
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI;
		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y;
		}

		////角度の正規化
		//if (g_player.rotDest.y > D3DX_PI / 2)
		//{
		//	g_player.rot.y -= D3DX_PI;
		//}
		//if (g_player.rotDest.y < -g_player.rot.y)
		//{
		//	g_player.rot.y += D3DX_PI;
		//}

		g_player.rot += (g_player.rotDest - g_player.rot) * 0.5f;

		//魔法発射
		if (((KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)) && g_player.Status.nMP >= 50)
		{// MPが５０以上の時
			SetSkill(g_player.pos, g_player.move, g_player.rot);
			g_player.Status.nMP -= 50; //MP消費
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
		if (KeyboardTrigger(DIK_SPACE) == true)
		{// SPACE
			if (g_player.bJump == false)
			{
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

		//当たり判定
		g_player.bJump = !CollisionBlock();
		CollisionEnemy();

		//地面との判定
		if (g_player.pos.y <= 0)
		{
			if (g_player.bJump == true)
			{
				g_player.bJump = false;
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
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		//HP減らす
		if (KeyboardTrigger(DIK_9) == true)
		{
			g_player.Status.nHP -= 100;
		}
#endif

		//移動制限
		if (g_player.pos.x <= -POLYGON_X)
		{
			g_player.pos.x = -POLYGON_X;
		}
		if (g_player.pos.x >= POLYGON_X)
		{
			g_player.pos.x = POLYGON_X;
		}
		if (g_player.pos.z <= -POLYGON_Y)
		{
			g_player.pos.z = -POLYGON_Y;
		}
		if (g_player.pos.z >= POLYGON_Y)
		{
			g_player.pos.z = POLYGON_Y;
		}

		//モーション
		SetPlayerMotion();
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
		for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;
			D3DXMATRIX mtxParent;

			//パーツのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスの設定
			if (g_player.aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_player.mtxWorld;
			}

			//パーツのワールドマトリックスの設定
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
				&g_player.aModel[nCntModel].mtxWorld,
				&mtxParent);
			
			//パーツのワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD,
				&g_player.aModel[nCntModel].mtxWorld);
			
			//パーツの描画
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャの設定
				pDevice->SetTexture(0, g_player.aModel[nCntModel].pTexture[nCntModel]);
				//プレイヤーの描画
				g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}
//===================
// プレイヤーの取得
//===================
Player* GetPlayer(void)
{
	return &g_player;
}
//=================
// モーション設定
//=================
void SetPlayerMotion(void)
{
	//全モデルの更新
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		//次のキー
		int nNext = (g_player.nKey + 1) % g_player.aMotionInfo[g_player.motionType].nNumKey;
		//キー数を戻す
		if (g_player.nKey >= g_player.aMotionInfo[g_player.motionType].nNumKey || nNext >= g_player.aMotionInfo[g_player.motionType].nNumKey)
		{
			g_player.nKey = 0;
		}

		D3DXVECTOR3 posMotion, rotMotion, posSabun, rotSabun;

		//差分計算
		//pos
		posSabun.x = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fPosX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosX;
		posSabun.y = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fPosY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosY;
		posSabun.z = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fPosZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosZ;
		//rot
		rotSabun.x = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fRotX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX;
		rotSabun.y = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fRotY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY;
		rotSabun.z = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fRotZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ;

		float fDis = (float)g_player.nCntMotion / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;

		//パーツの位置・向きを算出
		posMotion.x = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosX + posSabun.x * fDis);
		posMotion.y = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosY + posSabun.y * fDis);
		posMotion.z = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosZ + posSabun.z * fDis);

		rotMotion.x = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX + rotSabun.x * fDis);
		rotMotion.y = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY + rotSabun.y * fDis);
		rotMotion.z = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ + rotSabun.z * fDis);


		g_player.aModel[nCnt].pos += posMotion;
		g_player.aModel[nCnt].rot = rotMotion;
	}

	g_player.nCntMotion++;

	if (g_player.nCntMotion >= g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame)
	{
		g_player.nCntMotion = 0;

		g_player.nKey++;

		//g_player.motionType = MOTIONTYPE_NEUTRAL;
	}
}
//=================================
// プレイヤーのファイル読み込み
//=================================
void LoadPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	int Index;
	int nNum_Parts;
	int nCntModel = 0;
	int nLoop;
	int nCntMotion = 0;
	int nCntParts = 0;
	int nCntKey = 0;

	FILE* pFile;
	pFile = fopen(MOTIONFILE_PLAYER, "r");

	if (pFile != NULL)
	{
		char aString[MAX_WORD];

		fscanf(pFile, "%s", &aString[0]);
		if (strcmp(aString, "SCRIPT") == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aString[0]);

				//モデル数
				if (strcmp(aString, "NUM_MODEL") == 0)
				{
					fscanf(pFile, "%d", &g_player.nNumModel);
				}
				//モデルファイル名
				else if (strcmp(aString, "MODEL_FILENAME") == 0)
				{
					fscanf(pFile, "%s", &aString[0]);

					const char* ModelName = {};
					ModelName = aString;

					D3DXLoadMeshFromX(ModelName,
									  D3DXMESH_SYSTEMMEM,
									  pDevice,
									  NULL,
									  &g_player.aModel[nCntModel].pBuffMat,
									  NULL,
									  &g_player.aModel[nCntModel].dwNumMat,
									  &g_player.aModel[nCntModel].pMesh);
					nCntModel++;
				}
				//キャラクター情報
				else if (strcmp(aString, "CHARACTERSET") == 0)
				{
					while (1)
					{
						fscanf(pFile, "%s", &aString[0]);

						//パーツ数
						if (strcmp(aString, "NUM_PARTS") == 0)
						{
							fscanf(pFile, "%d", &nNum_Parts);
						}
						//パーツ設定
						else if (strcmp(aString, "PARTSSET") == 0)
						{
							while (1)
							{
								fscanf(pFile, "%s", &aString[0]);

								//インデックス
								if (strcmp(aString, "INDEX") == 0)
								{
									fscanf(pFile, "%d", &Index);
								}
								//親モデルのインデックス
								else if (strcmp(aString, "PARENT") == 0)
								{
									fscanf(pFile, "%d", &g_player.aModel[Index].nIdxModelParent);
								}
								//位置
								else if (strcmp(aString, "POS") == 0)
								{
									fscanf(pFile, "%f", &g_player.aModel[Index].pos.x);
									fscanf(pFile, "%f", &g_player.aModel[Index].pos.y);
									fscanf(pFile, "%f", &g_player.aModel[Index].pos.z);
								}
								//向き
								else if (strcmp(aString, "ROT") == 0)
								{
									fscanf(pFile, "%f", &g_player.aModel[Index].rot.x);
									fscanf(pFile, "%f", &g_player.aModel[Index].rot.y);
									fscanf(pFile, "%f", &g_player.aModel[Index].rot.z);
								}
								else if (strcmp(aString, "END_PARTSSET") == 0)
								{
									break;
								}
							}
						}
						else if (strcmp(aString, "END_CHARACTERSET") == 0)
						{
							break;
						}
					}
				}
				//モーション
				else if (strcmp(aString, "MOTIONSET") == 0)
				{
					while (1)
					{
						fscanf(pFile, "%s", &aString[0]);
						//ループ			
						if (strcmp(aString, "LOOP") == 0)
						{
							fscanf(pFile, "%d", &nLoop);
						}
						//キー数
						else if (strcmp(aString, "NUM_KEY") == 0)
						{
							fscanf(pFile, "%d", &g_player.aMotionInfo[nCntMotion].nNumKey);
						}
						//キー情報
						else if (strcmp(aString, "KEYSET") == 0)
						{
							while (1)
							{
								fscanf(pFile, "%s", &aString[0]);
								//フレーム数
								if (strcmp(aString, "FRAME") == 0)
								{
									fscanf(pFile, "%d", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);								
								}
								//キー
								else if (strcmp(aString, "KEY") == 0)
								{
									while (1)
									{
										fscanf(pFile, "%s", &aString[0]);
										//位置
										if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
										}
										//向き
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
										}
										else if (strcmp(aString, "END_KEY") == 0)
										{
											nCntParts++;
											break;
										}
									}
								}
								else if (strcmp(aString, "END_KEYSET") == 0)
								{
									nCntKey++;
									nCntParts = 0;
									break;
								}
							}
						}
						else if (strcmp(aString, "END_MOTIONSET") == 0)
						{
							nCntMotion++;
							nCntKey = 0;
							break;
						}
					}
				}
				else if (strcmp(aString, "END_SCRIPT") == 0)
				{
					break;
				}
			}
		}		
		fclose(pFile);//ファイルを閉じる
	}
	else
	{
		return;
	}
}
