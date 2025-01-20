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
#include "polygon.h"
#include "sound.h"

//グローバル変数宣言

//===========
//初期化処理
//===========
void InitResult(void)
{

	InitPolygon();

	InitCamera();

	InitLight();

	InitResultInfo();

}
//==========
//終了処理
//==========
void UninitResult(void)
{
	UninitPolygon();

	UninitCamera();

	UninitLight();

	UninitResultInfo();
}
//==========
//更新処理
//==========
void UpdateResult(void)
{
	UpdatePolygon();

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

	DrawPolygon();


	DrawResultInfo();
}
