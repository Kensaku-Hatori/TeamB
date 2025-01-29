//================================
//
//  リザルト表示処理[result.cpp]
//  Author:kaiti
//
//================================
#include "result.h"
#include "resultinfo.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "loadstage.h"
#include "loadmotion.h"
#include "model.h"
#include "meshfield.h"

//グローバル変数宣言

//===========
//初期化処理
//===========
void InitResult(void)
{
	InitMeshfield();

	InitCamera();

	InitLight();

	InitResultInfo();

	InitMotion();
	InitStageModel();

	LoadModelViewer();
}
//==========
//終了処理
//==========
void UninitResult(void)
{
	UninitMeshfield();

	UninitStageModel();

	UninitCamera();

	UninitLight();

	UninitResultInfo();
}
//==========
//更新処理
//==========
void UpdateResult(void)
{
	UpdateMeshfield();

	UpdateStageModel();

	UpdateCamera();

	UpdateLight();

	UpdateResultInfo();
}
//==========
//描画処理
//==========
void DrawResult(void)
{
	SetCamera();

	DrawMeshfield();

	DrawStageModel();

	DrawResultInfo();
}
