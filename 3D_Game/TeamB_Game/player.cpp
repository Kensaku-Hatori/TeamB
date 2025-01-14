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
#include "balltimer.h"
#include "motion.h"
#include "timer.h"
#include "polygon.h"
#include "sound.h"

//グローバル変数
Player g_player;
D3DXVECTOR3 g_vtxMinPlayer;//プレイヤーの最小値
D3DXVECTOR3 g_vtxMaxPlayer;//プレイヤーの最大値

////ニュートラルモーション
//static KEY_INFO g_aKeyNeutral[] =
//{
//	//キー０
//	{40,
//		{
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ0
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.85f},	//パーツ1
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.60f},	//パーツ2
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ3
//			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.85f},	//パーツ4
//			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.60f},	//パーツ5
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ6
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ7
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ8
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.10f},	//パーツ9
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ10
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ11
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}		//パーツ12
//		}
//	},
//	//キー１
//	{40,
//		{
//			{0.0f,0.0f,0.0f,0.13f,0.0f,0.0f},	//パーツ０
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.66f},	//パーツ１
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.44f},	//パーツ2
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ3
//			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.66f},	//パーツ4
//			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.44f},	//パーツ5
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ6
//			{0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f},	//パーツ7
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ8
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.10f},	//パーツ9
//			{0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f},	//パーツ10
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//パーツ11
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}		//パーツ12
//		}
//	}
//};

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
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.rot);//影
	g_player.type = PLAYERTYPE_HITO;
	g_player.fSpeed = PLAYER_HITOSPEED;
	g_player.nJump = PLAYER_HITOJUMP;
	g_player.nBallTime = MAX_BALLTIME;
	g_player.nCntKill = 0;
	g_player.nCntPin = 0;
	//モーション関連
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	g_player.bLoopMotion = true;//ループ
	g_player.nNumKey = 2;//キーの総数
	g_player.nCntMotion = 0;//モーションカウンター
	g_player.nKey = 0;//現在のキーNo
	g_player.nNumModel = 13;//パーツの総数

	g_player.bBall = true;
	g_player.bJump = false;//ジャンプ
	g_player.bUse = true;

	LoadPlayer();

#if 0
	//Xファイルの読み込み
	{
		D3DXLoadMeshFromX("data\\MODEL\\00_body02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[0].pBuffMat,
			NULL,
			&g_player.aModel[0].dwNumMat,
			&g_player.aModel[0].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\02_armUR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[1].pBuffMat,
			NULL,
			&g_player.aModel[1].dwNumMat,
			&g_player.aModel[1].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\02_armFR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[2].pBuffMat,
			NULL,
			&g_player.aModel[2].dwNumMat,
			&g_player.aModel[2].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\03_handR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[3].pBuffMat,
			NULL,
			&g_player.aModel[3].dwNumMat,
			&g_player.aModel[3].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\04_armUL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[4].pBuffMat,
			NULL,
			&g_player.aModel[4].dwNumMat,
			&g_player.aModel[4].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\04_armFL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[5].pBuffMat,
			NULL,
			&g_player.aModel[5].dwNumMat,
			&g_player.aModel[5].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\05_handL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[6].pBuffMat,
			NULL,
			&g_player.aModel[6].dwNumMat,
			&g_player.aModel[6].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\06_legUR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[7].pBuffMat,
			NULL,
			&g_player.aModel[7].dwNumMat,
			&g_player.aModel[7].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\06_legFR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[8].pBuffMat,
			NULL,
			&g_player.aModel[8].dwNumMat,
			&g_player.aModel[8].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\07_footR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[9].pBuffMat,
			NULL,
			&g_player.aModel[9].dwNumMat,
			&g_player.aModel[9].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\08_legUL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[10].pBuffMat,
			NULL,
			&g_player.aModel[10].dwNumMat,
			&g_player.aModel[10].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\08_legFL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[11].pBuffMat,
			NULL,
			&g_player.aModel[11].dwNumMat,
			&g_player.aModel[11].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\09_footL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[12].pBuffMat,
			NULL,
			&g_player.aModel[12].dwNumMat,
			&g_player.aModel[12].pMesh);
	}

	//各パーツの階層構造設定
	//{
	//	g_player.aModel[0].nIdxModelParent = -1;			   //親プレイヤーのインデックスを設定
	//	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 11.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[1].nIdxModelParent = 0;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[1].pos = D3DXVECTOR3(-9.0f, 13.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[2].nIdxModelParent = 1;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[2].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[3].nIdxModelParent = 2;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[3].pos = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[4].nIdxModelParent = 0;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[4].pos = D3DXVECTOR3(9.0f, 13.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[5].nIdxModelParent = 4;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[5].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[6].nIdxModelParent = 5;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[6].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[7].nIdxModelParent = 0;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[7].pos = D3DXVECTOR3(-5.0f, 1.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[8].nIdxModelParent = 7;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[8].pos = D3DXVECTOR3(0.0f, -3.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[9].nIdxModelParent = 8;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -5.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[10].nIdxModelParent = 0;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[10].pos = D3DXVECTOR3(5.0f, 1.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[11].nIdxModelParent = 10;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[11].pos = D3DXVECTOR3(0.0f, -3.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定

	//	g_player.aModel[12].nIdxModelParent = 11;				   //親プレイヤーのインデックスを設定
	//	g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -5.0f, 0.0f);//位置(オフセット)の初期設定
	//	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きの初期設定
	//}
#endif

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

		//SetEffect(g_player.pos,g_player.move, g_player.rot);

		if (g_player.bJump == true)
		{
			g_player.fSpeed /= 1.5;
		}
		//移動
		if (GetKeyboardPress(DIK_D) == true)
		{
			//if (g_player.type == PLAYERTYPE_HITO)
			//{
			//	g_player.motionType = MOTIONTYPE_MOVE;
			//}
			//else
			//{
			//	g_player.motionType = MOTIONTYPE_BALLMOVE;
			//}
			//g_player.motionType = MOTIONTYPE_MOVE;

			g_player.move.z += sinf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			//if (g_player.type == PLAYERTYPE_HITO)
			//{
			//	g_player.motionType = MOTIONTYPE_MOVE;
			//}
			//else
			//{
			//	g_player.motionType = MOTIONTYPE_BALLMOVE;
			//}
			//g_player.motionType = MOTIONTYPE_MOVE;

			g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.move.x += cosf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2;
		}
		if (GetKeyboardPress(DIK_W) == true)
		{
			//if (g_player.type == PLAYERTYPE_HITO)
			//{
			//	g_player.motionType = MOTIONTYPE_MOVE;
			//}
			//else
			//{
			//	g_player.motionType = MOTIONTYPE_BALLMOVE;
			//}
			//g_player.motionType = MOTIONTYPE_MOVE;

			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI;
		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			//if (g_player.type == PLAYERTYPE_HITO)
			//{
			//	g_player.motionType = MOTIONTYPE_MOVE;
			//}
			//else
			//{
			//	g_player.motionType = MOTIONTYPE_BALLMOVE;
			//}
			//g_player.motionType = MOTIONTYPE_MOVE;

			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
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

		//モード変更
		if (KeyboardTrigger(DIK_RETURN) == true)
		{
			//g_player.motionType = MOTIONTYPE_ACTION;

			if (g_player.type == PLAYERTYPE_HITO)
			{//人の時
				if (g_player.bBall == true && g_player.nBallTime > 0)
				{//ボール使用可能時
					g_player.type = PLAYERTYPE_BALL;
				}
			}
			else if (g_player.type == PLAYERTYPE_BALL)
			{//ボールの時
				g_player.type = PLAYERTYPE_HITO;
			}
		}

		//ジャンプ
		if (KeyboardTrigger(DIK_SPACE) == true)
		{// SPACE
			if (g_player.bJump == false)
			{
				//if (g_player.type == PLAYERTYPE_HITO)
				//{
				//	g_player.motionType = MOTIONTYPE_JUMP;
				//}
				//else
				//{
				//	g_player.motionType = MOTIONTYPE_BALLJUMP;
				//}
				//g_player.motionType = MOTIONTYPE_JUMP;

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
		//CollisionWall();
		CollisionEnemy();
		//CollisionPolygon();

		//地面との判定
		if (g_player.pos.y <= 0)
		{
			if (g_player.bJump == true)
			{
				//if (g_player.type == PLAYERTYPE_HITO)
				//{
				//	g_player.motionType = MOTIONTYPE_LANDING;
				//}
				//else
				//{
				//	g_player.motionType = MOTIONTYPE_BALLLANDING;
				//}
				g_player.bJump = false;
			}
			g_player.pos.y = 0.0;
			g_player.move.y = 0.0;
		}

		//移動量を更新
		g_player.move.x = 0.0f;
		g_player.move.z = 0.0f;

		//ボール状態なら
		if (g_player.type == PLAYERTYPE_BALL)
		{
			SetEffect(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 10.0f, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,0.0f,1.0f), EFFECT_LIFE, EFFECT_SIZE);
			g_player.fSpeed = PLAYER_BALLSPEED;
			g_player.nJump = PLAYER_BALLJUMP;
		}
		//人型なら
		else if (g_player.type == PLAYERTYPE_HITO)
		{
			g_player.fSpeed = PLAYER_HITOSPEED;
			g_player.nJump = PLAYER_HITOJUMP;
		}
		//スーパーボールなら
		else if (g_player.type == PLAYERTYPE_SUPERBALL)
		{
			SetEffect(D3DXVECTOR3(g_player.pos.x + 10.0f, g_player.pos.y + 5.0f, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.8f, 0.0f, 1.0f, 1.0f), EFFECT_LIFE, EFFECT_SIZE);
			SetEffect(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 5.0f, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f), EFFECT_LIFE, EFFECT_SIZE);
			SetEffect(D3DXVECTOR3(g_player.pos.x - 10.0f, g_player.pos.y + 5.0f, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.8f, 0.0f, 1.0f, 1.0f), EFFECT_LIFE, EFFECT_SIZE);
			g_player.fSpeed = PLAYER_SUPERBALLSPEED;
			g_player.nJump = PLAYER_HITOJUMP;
		}

		//１０体倒したら
		if (g_player.nCntPin >= PIN_CONDITION && g_player.type != PLAYERTYPE_SUPERBALL)
		{
			g_player.type = PLAYERTYPE_SUPERBALL;
			SetBallTimer(MAX_BALLTIME + 100);
			//PlaySound(SOUND_LABEL_BALL);
		}

		//もしボール時間が０になったら
		if (g_player.nBallTime <= 0)
		{
			if (g_player.type == PLAYERTYPE_SUPERBALL)
			{
				SetBallTimer(0);
				g_player.nCntPin = 0;
				StopSound(SOUND_LABEL_BALL);
			}
			g_player.type = PLAYERTYPE_HITO;
			g_player.bBall = false;
		}

#ifdef _DEBUG

		//位置を０に
		if (KeyboardTrigger(DIK_0) == true)
		{
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

		////次のキー
		//int nNext = (g_player.nKey + 1) % g_player.nNumKey;
		////キー数を戻す
		//if (g_player.nKey >= g_player.nNumKey || nNext >= g_player.nNumKey)
		//{
		//	g_player.nKey = 0;
		//}
		//
		//D3DXVECTOR3 posMotion, rotMotion, posSabun, rotSabun;
		//
		////差分計算
		////pos
		//posSabun.x = g_aKeyNeutral[nNext].aKey[nCnt].fPosX - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosX;
		//posSabun.y = g_aKeyNeutral[nNext].aKey[nCnt].fPosY - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosY;
		//posSabun.z = g_aKeyNeutral[nNext].aKey[nCnt].fPosZ - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosZ;
		////rot
		//rotSabun.x = g_aKeyNeutral[nNext].aKey[nCnt].fRotX - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotX;
		//rotSabun.y = g_aKeyNeutral[nNext].aKey[nCnt].fRotY - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotY;
		//rotSabun.z = g_aKeyNeutral[nNext].aKey[nCnt].fRotZ - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotZ;
		//
		//float fDis = (float)g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame;
		//
		////パーツの位置・向きを算出
		//posMotion.x = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosX + posSabun.x * fDis);
		//posMotion.y = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosY + posSabun.y * fDis);
		//posMotion.z = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosZ + posSabun.z * fDis);
		//
		//rotMotion.x = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotX + rotSabun.x * fDis);
		//rotMotion.y = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotY + rotSabun.y * fDis);
		//rotMotion.z = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotZ + rotSabun.z * fDis);

		////カクカク
		////パーツの位置・向きを算出
		//posMotion.x = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosX + posSabun.x * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//posMotion.y = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosY + posSabun.y * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//posMotion.z = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosZ + posSabun.z * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//
		//rotMotion.x = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotX + rotSabun.x * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//rotMotion.y = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotY + rotSabun.y * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//rotMotion.z = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotZ + rotSabun.z * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);

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