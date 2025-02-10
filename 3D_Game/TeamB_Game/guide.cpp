//=======================================================
// 
// 誘導する[guide.cpp]
// Author:Rio Ohno
// 
//=======================================================

#include "guide.h"
#include "circle.h"
#include "player.h"

//グローバル変数宣言
Guide g_Guide;					//誘導構造体

//===============
// 初期化処理
//===============
void InitGuide()
{
	g_Guide.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Guide.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Guide.bUse = false;
}

//===============
//終了処理
//===============
void UninitGuide()
{

}

//===============
//更新処理
//===============
void UpdateGuide()
{

}

//================
//描画処理
//================
void DrawGuide()
{

}

//================
//設定処理
//================
void SetGuide()
{
	//プレイヤーの情報取得
	Player* pPlayer = GetPlayer();

	//サークルの設定
	SetCircle(pPlayer->pos, pPlayer->rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), 16, 0, 20.0f, 25.0f, true, false);
}