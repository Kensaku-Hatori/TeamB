//=============================
//
//　カメラ処理[camera.cpp]
//　Author:kaiti
//
//=============================

//インクルード
#include "camera.h"
#include "input.h"
#include "player.h"
#include "mouse.h"
#include "lockon.h"

//グローバル変数
Camera g_camera;

//=================
// カメラの初期化
//=================
void InitCamera(void)
{
	//視点・注視点・上方向を設定する
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, 300.0f);
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
	//各種情報取得
	Player* pPlayer = GetPlayer();				//プレイヤー
	Lockon* pLockon = GetLockOn();				//ロックオン
	MODE pMode = GetMode();						//ゲームモード

	// 角度の近道
	if (g_camera.rotDest.y >= D3DX_PI)
	{
		g_camera.rotDest.y -= D3DX_PI * 2.0f;
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rotDest.y <= -D3DX_PI)
	{
		g_camera.rotDest.y += D3DX_PI * 2.0f;
		g_camera.rot.y += D3DX_PI * 2.0f;
	}
	// 角度の近道
	if (g_camera.rotDest.x >= D3DX_PI)
	{
		g_camera.rotDest.x -= D3DX_PI * 2.0f;
	}
	else if ((g_camera.rotDest.x) <= -D3DX_PI)
	{
		g_camera.rotDest.x += D3DX_PI * 2.0f;
	}
	
	g_camera.rot += (g_camera.rotDest - g_camera.rot) * 0.3f;

	////プレイヤーがロックオンしているなら
	//if (pPlayer->bLockOn == true)
	//{
	//	g_camera.posRDest.x = pLockon->pos.x + sinf(pPlayer->rot.x) * (pLockon->pos.x - g_camera.posR.x);
	//	g_camera.posRDest.y = pLockon->pos.y;
	//	g_camera.posRDest.z = pLockon->pos.z + cosf(pPlayer->rot.z) * (pLockon->pos.z - g_camera.posR.z);

	//	g_camera.posVDest.x = pLockon->pos.x + sinf(g_camera.rotDest.y - D3DX_PI) * g_camera.fDistance;
	//	g_camera.posVDest.z = pLockon->pos.z + cosf(g_camera.rotDest.y - D3DX_PI) * g_camera.fDistance;
	//}
	//else
	//{
	//	g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.x) * (pPlayer->pos.x - g_camera.posR.x);
	//	g_camera.posRDest.y = pPlayer->pos.y;
	//	g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.z) * (pPlayer->pos.z - g_camera.posR.z);

	//	g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rotDest.y - D3DX_PI) * g_camera.fDistance;
	//	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rotDest.y - D3DX_PI) * g_camera.fDistance;
	//}

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
		g_camera.rotDest.y += 0.01f;
	}
	//それ以外
	else
	{
#ifdef _DEBUG

		//視点の上下
		if (GetKeyboardPress(DIK_UP) == true)
		{//上
			if (g_camera.posV.y <= 500)
			{
				g_camera.posV.y += 5;
			}
		}
		if (GetKeyboardPress(DIK_DOWN) == true)
		{//下
			if (g_camera.posV.y >= -500)
			{
				g_camera.posV.y -= 5;
			}
		}
#endif

		Player* pPlayer = GetPlayer();
		if (pPlayer->bLockOn == false)
		{
			UpdateCameratoMousePos();
			UpdateCameratoJoyPadPos();
		}
		else
		{
			SetCursorPos(640, 360);
		}


		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;
	}
}

//=============================
//マウスによるカメラ操作処理
//=============================
void UpdateCameratoMousePos(void)
{
	static POINT SetMousePos = { (LONG)SCREEN_WIDTH / (LONG)2.0f,(LONG)SCREEN_HEIGHT / (LONG)2.0f };
	POINT MousePos;
	GetCursorPos(&MousePos);
	D3DXVECTOR2 DiffMouse = D3DXVECTOR2((FLOAT)MousePos.x - (FLOAT)SetMousePos.x,
		(FLOAT)MousePos.y - (FLOAT)SetMousePos.y);
	
	const FLOAT MouseSensitivity = 0.0008f;
	DiffMouse *= MouseSensitivity;
	g_camera.rotDest.x += DiffMouse.y;
	g_camera.rotDest.y += DiffMouse.x;

	SetCursorPos((int)SetMousePos.x, (int)SetMousePos.y);
}

//====================================
//ジョイパッドによるカメラ操作処理
//====================================
void UpdateCameratoJoyPadPos(void)
{
	XINPUT_STATE* pStick = GetJoyStickAngle();
	if (GetJoyStickR() == true)
	{
		float fStickAngleX = (float)pStick->Gamepad.sThumbRX * pStick->Gamepad.sThumbRX;
		float fStickAngleY = (float)pStick->Gamepad.sThumbRY * pStick->Gamepad.sThumbRY;

		float DeadZone = 10920.0f;
		float fMag = sqrtf(fStickAngleX + fStickAngleY);

		if (fMag > DeadZone)
		{
			if (pStick->Gamepad.sThumbRX < -DeadZone)
			{
				g_camera.rot.y += 0.03f;
			}
			else if (pStick->Gamepad.sThumbRX > DeadZone)
			{
				g_camera.rot.y -= 0.03f;
			}
		}
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
//カメラの情報取得処理
//=================
Camera * GetCamera(void)
{
	return &g_camera;
}

void SetMouseWheel(int zDelta)
{
	g_camera.fDistance += zDelta * CAMERA_DISTANCESPEED;
}

//=============================
//カメラの視点、注視点の設定
//=============================
void ResetCameraPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	g_camera.posV = posV;				//視点
	g_camera.posR = posR;				//注視点
	g_camera.posVDest = posV;				//視点
	g_camera.posRDest = posR;				//注視点

	int i = 0;
}
