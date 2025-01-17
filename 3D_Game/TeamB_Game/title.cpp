//==============================
//
//  選択処理[Title.h]
//  Author:kaiti
//
//==============================
#include "title.h"
#include "titleinfo.h"
#include "ranking.h"
#include "fade.h"
#include "sound.h"
//グローバル変数
int g_nTimeTitle; //タイトルからランキングへの時間

//============
//初期化処理
//============
void InitTitle(void)
{
	g_nTimeTitle = 0;

	InitTitleInfo();

}
//==========
//終了処理
//==========
void UninitTitle(void)
{
	UninitTitleInfo();

}
//==========
//更新処理
//==========
void UpdateTitle(void)
{
	UpdateTitleInfo();

	g_nTimeTitle++;
	if (g_nTimeTitle >= MAX_TITLE)
	{
		SetRankMode(RANKMODE_TITLE);
		SetFade(MODE_RANK);
		g_nTimeTitle = 0;
	}

}
//===========
//描画処理
//===========
void DrawTitle(void)
{
	DrawTitleInfo();

}