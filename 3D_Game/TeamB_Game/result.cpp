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
#include "model.h"

//グローバル変数宣言

//===========
//初期化処理
//===========
void InitResult(void)
{
	InitStageModel();

	LoadModelViewer();

	InitCamera();

	InitLight();

	InitResultInfo();

}
//==========
//終了処理
//==========
void UninitResult(void)
{
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

	DrawStageModel();

	DrawResultInfo();
}
