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
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "loadstage.h"
//グローバル変数
int g_nTimeTitle; //タイトルからランキングへの時間

//============
//初期化処理
//============
void InitTitle(void)
{
	g_nTimeTitle = 0;

	InitPolygon();

	InitCamera();

	InitLight();

	InitTitleInfo();

	//LoadModelViewer();
}
//==========
//終了処理
//==========
void UninitTitle(void)
{
	UninitPolygon();

	UninitCamera();

	UninitLight();


	UninitTitleInfo();
}
//==========
//更新処理
//==========
void UpdateTitle(void)
{
	Camera* pCamera;
	pCamera = GetCamera();

	UpdatePolygon();

	UpdateCamera();

	pCamera->rot.y += 0.01f;

	UpdateLight();


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
	SetCamera();

	DrawPolygon();


	DrawTitleInfo();
}