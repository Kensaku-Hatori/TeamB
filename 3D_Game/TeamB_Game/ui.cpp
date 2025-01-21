//================================
//
//  UI表示処理[ui.cpp]
//  Author:kaiti
//
//================================
#include "ui.h"
#include "timer.h"
#include "score.h"

//グローバル変数

//=============
// 初期化処理
//=============
void InitUi(void)
{
	InitTimer();
	SetTimer(0,0);

	InitScore();
	SetScore(0);
}
//===========
// 終了処理
//===========
void UninitUi(void)
{
	UninitTimer();

	UninitScore();
}
//===========
// 更新処理
//===========
void UpdateUi(void)
{
	UpdateTimer();

	UpdateScore();
}
//===========
// 描画処理
//===========
void DrawUi(void)
{
	DrawTimer();

	DrawScore();
}