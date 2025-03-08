//================================
//
//　カメラ処理[camera.h]
//　Author:kaiti
//
//================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define CAMERA_DISTANCESPEED (float)(0.1f)
#include "main.h"

typedef struct
{
	D3DXVECTOR3 posV;//視点
	D3DXVECTOR3 posR;//注視点

	D3DXVECTOR3 posVDest;//視点
	D3DXVECTOR3 posRDest;//注視点
	
	D3DXVECTOR3 vecU;//上方向ベクトル
	D3DXMATRIX mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX mtxView;//ビューマトリックス
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 rotDest;
	float fDistance;//視点から注視点の距離
	bool bResete;
}Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void UpdateCameratoMousePos(void);
void UpdateCameratoJoyPadPos(void);
void SetCamera(void);
Camera * GetCamera(void);
void SetMouseWheel(int zDelta);
void ResetCameraPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR);
#endif