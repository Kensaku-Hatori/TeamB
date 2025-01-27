//=============================
//
//　カメラ処理[camera.cpp]
//　Author:kaiti
//
//=============================
#include "camera.h"
#include "input.h"
#include "player.h"
//グローバル変数
Camera g_camera;

//=================
// カメラの初期化
//=================
void InitCamera(void)
{
	//視点・注視点・上方向を設定する
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -250.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf(((g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x))
							 + ((g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y))
							 + ((g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z)));
}
//===================
// カメラの終了処理
//===================
void UninitCamera(void)
{

}
//====================
// カメラの更新処理
//====================
void UpdateCamera(void)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	MODE pMode;
	pMode = GetMode();
	
	g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.x) * (pPlayer->pos.x - g_camera.posR.x);
	g_camera.posRDest.y = pPlayer->pos.y;
	g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.z) * (pPlayer->pos.z - g_camera.posR.z);

	g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y - D3DX_PI) * g_camera.fDistance;
	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y - D3DX_PI) * g_camera.fDistance;


	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.08f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 1.0f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.08f;

	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.08f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.08f;


	//タイトルとリザルトの時
	if (pMode == MODE_TITLE || pMode == MODE_RESULT)
	{//カメラの自動回転
		pPlayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//プレイヤーの位置を０に
		//回転
		g_camera.rot.y += 0.01f;

		g_camera.posV.y = 200.0f;
		g_camera.posR.y = 100.0f;
	}
	//それ以外
	else
	{

		////視点の旋回
		//if (GetKeyboardPress(DIK_Z) == true)
		//{
		//	g_camera.rot.y += 0.05f;
		//	//角度の正規化
		//	if (g_camera.rot.y > D3DX_PI)
		//	{
		//		g_camera.rot.y = -D3DX_PI;
		//	}
		//	if (g_camera.rot.y < -D3DX_PI)
		//	{
		//		g_camera.rot.y = D3DX_PI;
		//	}

		//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		//}
		if (GetKeyboardPress(DIK_C) == true)
		{
			g_camera.rot.y -= 0.05f;
			//角度の正規化
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y = -D3DX_PI;
			}
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y = D3DX_PI;
			}
			g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
		}

		////視点の上下
		//if (GetKeyboardPress(DIK_Y) == true)
		//{//上
		//	if (g_camera.posV.y <= 500)
		//	{
		//		g_camera.posV.y += 5;
		//	}
		//}
		if (GetKeyboardPress(DIK_N) == true)
		{//下
			if (g_camera.posV.y >= -500)
			{
				g_camera.posV.y -= 5;
			}
		}

		//注視点の上下
		//if (GetKeyboardPress(DIK_R) == true)
		//{//上
		//	g_camera.rot.x += 0.05f;
		//	//角度の正規化
		//	if (g_camera.rot.x > D3DX_PI)
		//	{
		//		g_camera.rot.x = -D3DX_PI;
		//	}
		//	if (g_camera.rot.x < -D3DX_PI)
		//	{
		//		g_camera.rot.x = D3DX_PI;
		//	}

		//	g_camera.posV.y -= sinf(g_camera.rot.x - D3DX_PI) * 1;

		//	g_camera.posR.y = g_camera.posV.y + sinf(g_camera.rot.x) * g_camera.fDistance;
		//}
	}
}
//================
// カメラの設定
//================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
					   &g_camera.posV,
					   &g_camera.posR,
					   &g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f), //視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, //アスペクト比
		10.0f,
		5000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}
//=================
//
//=================
Camera * GetCamera(void)
{
	return &g_camera;
}