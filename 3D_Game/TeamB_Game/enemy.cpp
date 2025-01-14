//=================================
//
// 敵表示処理[Enemy.cpp]
// Author:kaiti
//
//=================================
#include "enemy.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"
#include "block.h"
#include "wall.h"
#include "player.h"
#include "score.h"
#include "game.h"
#include "particle.h"
#include "balltimer.h"
#include "polygon.h"
#include "killcount.h"
#include "tutorial.h"

//グローバル変数
Enemy g_Enemy[MAX_ENEMY];
D3DXVECTOR3 g_vtxMinEnemy;//敵の最小値
D3DXVECTOR3 g_vtxMaxEnemy;//敵の最大値

//ニュートラルモーション
static KEY_INFO g_aKeyNeutral[] =
{
	//キー０
	{40,
		{
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ0
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.85f},	//パーツ1
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.60f},	//パーツ2
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ3
			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.85f},	//パーツ4
			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.60f},	//パーツ5
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ6
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ7
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ8
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.10f},	//パーツ9
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ10
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ11
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}		//パーツ12
		}
	},
	//キー１
	{40,
		{
			{0.0f,0.0f,0.0f,0.13f,0.0f,0.0f},	//パーツ０
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.66f},	//パーツ１
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.44f},	//パーツ2
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ3
			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.66f},	//パーツ4
			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.44f},	//パーツ5
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ6
			{0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f},	//パーツ7
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ8
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.10f},	//パーツ9
			{0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f},	//パーツ10
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ11
			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}		//パーツ12
		}
	}
};

//===============
// 敵の初期化
//===============
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_Enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].nLife = 0;
		g_Enemy[nCntEnemy].nDamage = 0;

		//モーション関連
		g_Enemy[nCntEnemy].motionType = ENEMYMOTIONTYPE_NEUTRAL;
		g_Enemy[nCntEnemy].bLoopMotion = true;//ループ
		g_Enemy[nCntEnemy].nNumKey = 2;//キーの総数
		g_Enemy[nCntEnemy].nCntMotion = 0;//モーションカウンター
		g_Enemy[nCntEnemy].nKey = 0;//現在のキーNo
		g_Enemy[nCntEnemy].nNumModel = 13;//パーツの総数

		g_Enemy[nCntEnemy].bDamage = false;
		g_Enemy[nCntEnemy].bJump = false;//ジャンプ
		g_Enemy[nCntEnemy].bUse = false;

		//Xファイルの読み込み
		{
			D3DXLoadMeshFromX("data\\MODEL\\00_body04.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[0].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[0].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[0].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\02_armUR02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[1].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[1].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[1].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\02_armFR02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[2].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[2].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[2].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\03_handR02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[3].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[3].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[3].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\04_armUL02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[4].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[4].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[4].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\04_armFL02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[5].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[5].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[5].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\05_handL02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[6].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[6].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[6].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\06_legUR02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[7].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[7].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[7].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\06_legFR02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[8].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[8].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[8].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\07_footR02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[9].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[9].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[9].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\08_legUL02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[10].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[10].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[10].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\08_legFL02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[11].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[11].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[11].pMesh);

			D3DXLoadMeshFromX("data\\MODEL\\09_footL02.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[12].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[12].dwNumMat,
				&g_Enemy[nCntEnemy].aModel[12].pMesh);
		}

		//各パーツの階層構造設定	
		g_Enemy[nCntEnemy].aModel[0].nIdxModelParent = -1;			   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[0].pos = D3DXVECTOR3(0.0f, 11.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[1].nIdxModelParent = 0;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[1].pos = D3DXVECTOR3(-9.0f, 13.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[2].nIdxModelParent = 1;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[2].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[3].nIdxModelParent = 2;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[3].pos = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[4].nIdxModelParent = 0;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[4].pos = D3DXVECTOR3(9.0f, 13.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[5].nIdxModelParent = 4;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[5].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[6].nIdxModelParent = 5;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[6].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[7].nIdxModelParent = 0;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[7].pos = D3DXVECTOR3(-5.0f, 1.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[8].nIdxModelParent = 7;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[8].pos = D3DXVECTOR3(0.0f, -3.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[9].nIdxModelParent = 8;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[9].pos = D3DXVECTOR3(0.0f, -5.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[10].nIdxModelParent = 0;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[10].pos = D3DXVECTOR3(5.0f, 1.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[11].nIdxModelParent = 10;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[11].pos = D3DXVECTOR3(0.0f, -3.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

		g_Enemy[nCntEnemy].aModel[12].nIdxModelParent = 11;				   //親敵のインデックスを設定
		g_Enemy[nCntEnemy].aModel[12].pos = D3DXVECTOR3(0.0f, -5.0f, 0.0f);//位置(オフセット)の初期設定
		g_Enemy[nCntEnemy].aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定
		

		int nNumVtx;   //頂点数
		DWORD sizeFVF; //頂点フォーマットのサイズ
		BYTE* pVtxBuff;//頂点バッファへのポインタ

		for (int nCnt = 0; nCnt < g_Enemy[nCntEnemy].nNumModel; nCnt++)
		{
			//頂点数取得
			nNumVtx = g_Enemy[nCntEnemy].aModel[nCnt].pMesh->GetNumVertices();
			//頂点フォーマットのサイズ取得
			sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCntEnemy].aModel[nCnt].pMesh->GetFVF());
			//頂点バッファのロック
			g_Enemy[nCntEnemy].aModel[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//頂点座標を比較して敵の最小値、最大値を取得
				//最小値
				if (vtx.x < g_vtxMinEnemy.x)
				{
					g_vtxMinEnemy.x = vtx.x;
				}
				if (vtx.y < g_vtxMinEnemy.y)
				{
					g_vtxMinEnemy.y = vtx.y;
				}
				if (vtx.z < g_vtxMinEnemy.z)
				{
					g_vtxMinEnemy.z = vtx.z;
				}
				//最大値
				if (vtx.x > g_vtxMaxEnemy.x)
				{
					g_vtxMaxEnemy.x = vtx.x;
				}
				if (vtx.y > g_vtxMaxEnemy.y)
				{
					g_vtxMaxEnemy.y = vtx.y;
				}
				if (vtx.z > g_vtxMaxEnemy.z)
				{
					g_vtxMaxEnemy.z = vtx.z;
				}

				//頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			g_Enemy[nCntEnemy].size = D3DXVECTOR3(g_vtxMaxEnemy.x - g_vtxMinEnemy.x, g_vtxMaxEnemy.y - g_vtxMinEnemy.y, g_vtxMaxEnemy.z - g_vtxMinEnemy.z);

			//頂点バッファのアンロック
			g_Enemy[nCntEnemy].aModel[nCnt].pMesh->UnlockVertexBuffer();

			D3DXMATERIAL* pMat;//マテリアルへのポインタ
			pMat = (D3DXMATERIAL*)g_Enemy[nCntEnemy].aModel[nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntEnemy].aModel[nCnt].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_Enemy[nCntEnemy].aModel[nCnt].pTexture[nCnt]); //1
				}
			}
		}	
	}
}
//=================
// 敵の終了処理
//=================
void UninitEnemy(void)
{
	//敵の破棄
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		for (int nCnt = 0; nCnt < g_Enemy[nCntEnemy].nNumModel; nCnt++)
		{
			//メッシュの破棄
			if (g_Enemy[nCntEnemy].aModel[nCnt].pMesh != NULL)
			{
				g_Enemy[nCntEnemy].aModel[nCnt].pMesh->Release();
				g_Enemy[nCntEnemy].aModel[nCnt].pMesh = NULL;
			}
			//マテリアルの破棄
			if (g_Enemy[nCntEnemy].aModel[nCnt].pBuffMat != NULL)
			{
				g_Enemy[nCntEnemy].aModel[nCnt].pBuffMat->Release();
				g_Enemy[nCntEnemy].aModel[nCnt].pBuffMat = NULL;
			}
		}
	}
}
//==================
// 敵の更新処理
//==================
void UpdateEnemy(void)
{
	GAMESTATE Gamestate = GetGameSatate();
	TUTORIAL Tutorial = GetTutorialSatate();

	Player* pPlayer = GetPlayer();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			if (Gamestate == GAMESTATE_NORMAL || Tutorial == TUTORIAL_NORMAL)
			{
				SetPositionShadow(g_Enemy[nCntEnemy].nIdxShadow, g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].bUse);

				//移動
				if (pPlayer->type == PLAYERTYPE_HITO)
				{//追いかける
					//移動量
					g_Enemy[nCntEnemy].move.x = (pPlayer->pos.x - g_Enemy[nCntEnemy].pos.x) * 0.01f;
					g_Enemy[nCntEnemy].move.z = (pPlayer->pos.z - g_Enemy[nCntEnemy].pos.z) * 0.01f;

					g_Enemy[nCntEnemy].rotDest.y = pPlayer->rot.y - D3DX_PI;
				}
				else if (pPlayer->type == PLAYERTYPE_BALL)
				{//逃げる
					//移動量
					g_Enemy[nCntEnemy].move.x = (pPlayer->pos.x - g_Enemy[nCntEnemy].pos.x) * -0.017f;
					g_Enemy[nCntEnemy].move.z = (pPlayer->pos.z - g_Enemy[nCntEnemy].pos.z) * -0.017f;
					g_Enemy[nCntEnemy].rotDest.y = pPlayer->rot.y - D3DX_PI;
				}
				else if (pPlayer->type == PLAYERTYPE_SUPERBALL)
				{//逃げる
					//移動量
					g_Enemy[nCntEnemy].move.x = (pPlayer->pos.x - g_Enemy[nCntEnemy].pos.x) * -0.005f;
					g_Enemy[nCntEnemy].move.z = (pPlayer->pos.z - g_Enemy[nCntEnemy].pos.z) * -0.005f;
					g_Enemy[nCntEnemy].rotDest.y = pPlayer->rot.y - D3DX_PI;
				}
				////角度の正規化
				//if (g_Enemy[nCntEnemy].rotDest.y > D3DX_PI / 2)
				//{
				//	g_Enemy[nCntEnemy].rot.y -= D3DX_PI;
				//}
				//if (g_Enemy[nCntEnemy].rotDest.y < -g_Enemy[nCntEnemy].rot.y)
				//{
				//	g_Enemy[nCntEnemy].rot.y += D3DX_PI;
				//}

				g_Enemy[nCntEnemy].rot += (g_Enemy[nCntEnemy].rotDest - g_Enemy[nCntEnemy].rot) * 0.5f;

				g_Enemy[nCntEnemy].move.y -= 0.3f; //重力加算

				g_Enemy[nCntEnemy].posOld = g_Enemy[nCntEnemy].pos;//前回の位置を保存

				//位置を更新
				g_Enemy[nCntEnemy].pos.x += g_Enemy[nCntEnemy].move.x;
				g_Enemy[nCntEnemy].pos.y += g_Enemy[nCntEnemy].move.y;
				g_Enemy[nCntEnemy].pos.z += g_Enemy[nCntEnemy].move.z;

				//当たり判定
				//CollisionBlock();
				//CollisionWall();
				CollisionEnemyAndEnemy(nCntEnemy);
				CollisionBlockEnemy(nCntEnemy);

				//地面との判定
				if (g_Enemy[nCntEnemy].pos.y <= 0)
				{
					if (g_Enemy[nCntEnemy].bJump == true)
					{
						g_Enemy[nCntEnemy].motionType = ENEMYMOTIONTYPE_LANDING;
						g_Enemy[nCntEnemy].bJump = false;
					}
					g_Enemy[nCntEnemy].pos.y = 0.0;
					g_Enemy[nCntEnemy].move.y = 0.0;
				}

				//ダメージを受けていたら
				if (g_Enemy[nCntEnemy].bDamage == true)
				{
					g_Enemy[nCntEnemy].nDamage++;
					if (g_Enemy[nCntEnemy].nDamage >= 30)
					{
						g_Enemy[nCntEnemy].bDamage = false;
						g_Enemy[nCntEnemy].nDamage = 0;
					}
				}

				//移動量を更新
				//g_Enemy[nCntEnemy].move.x = 0.0f;
				//g_Enemy[nCntEnemy].move.y = 0.0f;
				//g_Enemy[nCntEnemy].move.z = 0.0f;

				//ライフが０
				if (g_Enemy[nCntEnemy].nLife <= 0)
				{
					SetExplosion(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot);
					g_Enemy[nCntEnemy].bUse = false;
					if (pPlayer->type == PLAYERTYPE_BALL)
					{
						pPlayer->nCntPin++;
					}
					pPlayer->nCntKill++;
					SetPositionShadow(g_Enemy[nCntEnemy].nIdxShadow, g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].bUse);
					AddScore(100);
					AddKillCount(1);
					g_Enemy[nCntEnemy].pos.y = 0.0f;
				}

				//移動制限
				if (g_Enemy[nCntEnemy].pos.x <= -POLYGON_X)
				{
					g_Enemy[nCntEnemy].pos.x = -POLYGON_X;
				}
				if (g_Enemy[nCntEnemy].pos.x >= POLYGON_X)
				{
					g_Enemy[nCntEnemy].pos.x = POLYGON_X;
				}
				if (g_Enemy[nCntEnemy].pos.z <= -POLYGON_Y)
				{
					g_Enemy[nCntEnemy].pos.z = -POLYGON_Y;
				}
				if (g_Enemy[nCntEnemy].pos.z >= POLYGON_Y)
				{
					g_Enemy[nCntEnemy].pos.z = POLYGON_Y;
				}
			}
			//モーション
			SetEnemyMotion(nCntEnemy);
		}
	}
}
//=============
// 敵の描画
//=============
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//計算用マトリックス
			D3DXMATRIX mtxRot, mtxTrans;
			//現在のマテリアル保存用
			D3DMATERIAL9 matDef;
			//マテリアルデータへのポインタ
			D3DXMATERIAL* pMat;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorld);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//全パーツの描画
			for (int nCntModel = 0; nCntModel < g_Enemy[nCntEnemy].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;
				D3DXMATRIX mtxParent;

				//パーツのワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//向きを反転
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntEnemy].aModel[nCntModel].rot.y, g_Enemy[nCntEnemy].aModel[nCntModel].rot.x, g_Enemy[nCntEnemy].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//位置を反映
				D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntEnemy].aModel[nCntModel].pos.x, g_Enemy[nCntEnemy].aModel[nCntModel].pos.y, g_Enemy[nCntEnemy].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//パーツの親のマトリックスの設定
				if (g_Enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_Enemy[nCntEnemy].aModel[g_Enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_Enemy[nCntEnemy].mtxWorld;
				}

				//パーツのワールドマトリックスの設定
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
					&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
					&mtxParent);

				//パーツのワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD,
					&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//パーツの描画
				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_Enemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntEnemy].aModel[nCntModel].dwNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					//テクスチャの設定
					pDevice->SetTexture(0, g_Enemy[nCntEnemy].aModel[nCntModel].pTexture[nCntModel]);
					//敵の描画
					g_Enemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}
			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
//============
// 敵の取得
//============
Enemy* GetEnemy(void)
{
	return &g_Enemy[0];
}
//===========
// 敵設定
//===========
void SetEnemy(D3DXVECTOR3 pos)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{
			g_Enemy[nCntEnemy].pos = pos;
			g_Enemy[nCntEnemy].nIdxShadow = SetShadow(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot);//影
			g_Enemy[nCntEnemy].nLife = ENEMY_LIFE;
			g_Enemy[nCntEnemy].bDamage = false;
			g_Enemy[nCntEnemy].nDamage = 0;
			g_Enemy[nCntEnemy].bUse = true;
			break;
		}
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
			g_Enemy[nCntEnemy].fDistance = sqrtf(((g_Enemy[nCntEnemy].pos.x - pPlayer->pos.x) * (g_Enemy[nCntEnemy].pos.x - pPlayer->pos.x))
											   + ((g_Enemy[nCntEnemy].pos.y - pPlayer->pos.y) * (g_Enemy[nCntEnemy].pos.y - pPlayer->pos.y))
											   + ((g_Enemy[nCntEnemy].pos.z - pPlayer->pos.z) * (g_Enemy[nCntEnemy].pos.z - pPlayer->pos.z)));

			float RADIUS = (PLAYER_RADIUS + ENEMY_RADIUS) * (PLAYER_RADIUS + ENEMY_RADIUS);

			if (g_Enemy[nCntEnemy].fDistance <= RADIUS)
			{
				if (pPlayer->type == PLAYERTYPE_BALL || pPlayer->type == PLAYERTYPE_SUPERBALL)
				{
					if (g_Enemy[nCntEnemy].bDamage == false)
					{
						SetParticle(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y + 20.0f, g_Enemy[nCntEnemy].pos.z));

						g_Enemy[nCntEnemy].move.y += 8.0f;

						g_Enemy[nCntEnemy].nLife--;

						if (pPlayer->type == PLAYERTYPE_SUPERBALL)
						{
							g_Enemy[nCntEnemy].nLife -= 10;
						}
						g_Enemy[nCntEnemy].bDamage = true;
					}
				}
				else if (pPlayer->type == PLAYERTYPE_HITO)
				{
					AddScore(-1);
					AddBallTimer(-1);
				}
			}
		}
	}
}
//======================
// 敵と敵の当たり判定
//======================
void CollisionEnemyAndEnemy(int nCntEnemy)
{
	for (int nCntEnemy2 = 0; nCntEnemy2 < MAX_ENEMY; nCntEnemy2++)
	{
		if (g_Enemy[nCntEnemy].bUse == true && g_Enemy[nCntEnemy2].bUse == true && nCntEnemy != nCntEnemy2)
		{
			//敵との距離
			g_Enemy[nCntEnemy].fDistance = sqrtf(((g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy2].pos.x) * (g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy2].pos.x))
										       + ((g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy2].pos.y) * (g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy2].pos.y))
											   + ((g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy2].pos.z) * (g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy2].pos.z)));

			float RADIUS = (ENEMYAND_RADIUS + ENEMYAND_RADIUS) * (ENEMYAND_RADIUS + ENEMYAND_RADIUS);
			if (g_Enemy[nCntEnemy].fDistance < RADIUS)
			{
				g_Enemy[nCntEnemy].pos.x = g_Enemy[nCntEnemy].posOld.x;
				g_Enemy[nCntEnemy].pos.z = g_Enemy[nCntEnemy].posOld.z;
			}
			else
			{
			}
		}
	}
}
//=================
// モーション設定
//=================
void SetEnemyMotion(int nCntEnemy)
{
	//全モデルの更新
	for (int nCnt = 0; nCnt < g_Enemy[nCntEnemy].nNumModel; nCnt++)
	{
		//次のキー
		int nNext = (g_Enemy[nCntEnemy].nKey + 1) % g_Enemy[nCntEnemy].nNumKey;
		//キー数を戻す
		if (g_Enemy[nCntEnemy].nKey >= g_Enemy[nCntEnemy].nNumKey || nNext >= g_Enemy[nCntEnemy].nNumKey)
		{
			g_Enemy[nCntEnemy].nKey = 0;
		}

		D3DXVECTOR3 posMotion, rotMotion, posSabun, rotSabun;

		//差分計算
		//pos
		posSabun.x = g_aKeyNeutral[nNext].aKey[nCnt].fPosX - g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fPosX;
		posSabun.y = g_aKeyNeutral[nNext].aKey[nCnt].fPosY - g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fPosY;
		posSabun.z = g_aKeyNeutral[nNext].aKey[nCnt].fPosZ - g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fPosZ;
		//rot
		rotSabun.x = g_aKeyNeutral[nNext].aKey[nCnt].fRotX - g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fRotX;
		rotSabun.y = g_aKeyNeutral[nNext].aKey[nCnt].fRotY - g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fRotY;
		rotSabun.z = g_aKeyNeutral[nNext].aKey[nCnt].fRotZ - g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fRotZ;

		float fDis = (float)g_Enemy[nCntEnemy].nCntMotion / g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].nFrame;

		//パーツの位置・向きを算出
		posMotion.x = (g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fPosX + posSabun.x * fDis);
		posMotion.y = (g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fPosY + posSabun.y * fDis);
		posMotion.z = (g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fPosZ + posSabun.z * fDis);

		rotMotion.x = (g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fRotX + rotSabun.x * fDis);
		rotMotion.y = (g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fRotY + rotSabun.y * fDis);
		rotMotion.z = (g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fRotZ + rotSabun.z * fDis);

		////カクカク
		////パーツの位置・向きを算出
		//posMotion.x = g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fPosX + posSabun.x * (g_Enemy[nCntEnemy].nCntMotion / g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].nFrame);
		//posMotion.y = g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fPosY + posSabun.y * (g_Enemy[nCntEnemy].nCntMotion / g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].nFrame);
		//posMotion.z = g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fPosZ + posSabun.z * (g_Enemy[nCntEnemy].nCntMotion / g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].nFrame);

		//rotMotion.x = g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fRotX + rotSabun.x * (g_Enemy[nCntEnemy].nCntMotion / g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].nFrame);
		//rotMotion.y = g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fRotY + rotSabun.y * (g_Enemy[nCntEnemy].nCntMotion / g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].nFrame);
		//rotMotion.z = g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].aKey[nCnt].fRotZ + rotSabun.z * (g_Enemy[nCntEnemy].nCntMotion / g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].nFrame);

		g_Enemy[nCntEnemy].aModel[nCnt].pos += posMotion;
		g_Enemy[nCntEnemy].aModel[nCnt].rot = rotMotion;
	}

	g_Enemy[nCntEnemy].nCntMotion++;

	if (g_Enemy[nCntEnemy].nCntMotion >= g_aKeyNeutral[g_Enemy[nCntEnemy].nKey].nFrame)
	{
		g_Enemy[nCntEnemy].nCntMotion = 0;

		g_Enemy[nCntEnemy].nKey++;
	}	
}