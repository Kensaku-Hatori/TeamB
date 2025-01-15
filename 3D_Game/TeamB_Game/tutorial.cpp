//======================================
//
//  ゲーム画面表示処理[Tutorial.cpp]
//  Author:kaiti
//
//======================================
#include "tutorial.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "player.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "explosion.h"
#include "effect.h"
#include "block.h"
#include "meshwall.h"
#include "meshcylinder.h"
#include "fade.h"
#include "timer.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "particle.h"

//グローバル変数
TUTORIAL g_tutorial = TUTORIAL_NONE;
int g_nCounterTUTORIAL = 0;

//=============
// 初期化処理
//=============
void InitTutorial(void)
{
	InitPolygon();

	InitShadow();

	InitBlock();

	InitPlayer();

	InitEnemy();

	InitBiillboard();

	InitEffect();

	InitParticle();

	InitExplosion();

	InitMeshCylinder();

	InitWall();


	InitMeshWall();

	InitCamera();

	InitLight();

	InitTimer();
	SetTimer(MAX_TUTORIALTIME);

	InitScore();
	SetScore(0);

	g_tutorial = TUTORIAL_NORMAL;
	g_nCounterTUTORIAL = 0;
}
//===========
// 終了処理
//===========
void UninitTutorial(void)
{
	UninitShadow();

	UninitPlayer();

	UninitEnemy();

	UninitBiillboard();

	UninitEffect();

	UninitParticle();

	UninitBlock();

	UninitPolygon();

	UninitExplosion();

	UninitMeshCylinder();

	UninitWall();

	UninitMeshWall();

	UninitCamera();

	UninitLight();

	UninitTimer();

	UninitScore();
}
//===========
// 更新処理
//===========
void UpdateTutorial(void)
{
	int nTime = GetTimer();
	Enemy *pEnemy = GetEnemy();

	UpdatePolygon();

	UpdateShadow();

	UpdatePlayer();

	UpdateEnemy();
	//敵の無限湧き
	if (pEnemy->bUse == false)
	{
		SetEnemy(D3DXVECTOR3(150.0f, 300.0f, 150.0f));
	}

	UpdateBiillboard();

	UpdateEffect();

	UpdateParticle();

	UpdateBlock();

	UpdateExplosion();

	UpdateMeshCylinder();

	UpdateWall();

	UpdateMeshWall();

	UpdateCamera();

	UpdateLight();

	UpdateTimer();

	UpdateScore();

	switch (g_tutorial)
	{
	case TUTORIAL_NORMAL:
		break;
	case TUTORIAL_TIMEOVER:
		g_nCounterTUTORIAL++;
		if (g_nCounterTUTORIAL >= 30)
		{
			g_tutorial = TUTORIAL_NONE;
			//モードをリザルトにする
			SetFade(MODE_TITLE);
		}
		break;
	}
	//タイトルに飛ぶ
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{
		SetFade(MODE_TITLE);
	}
}
//===========
// 描画処理
//===========
void DrawTutorial(void)
{
	SetCamera();

	DrawPolygon();

	DrawMeshCylinder();

	DrawWall();

	DrawMeshWall();

	DrawShadow();

	DrawBlock();

	DrawBiillboard();

	DrawPlayer();

	DrawEnemy();

	DrawExplosion();

	DrawEffect();

	DrawParticle();

	DrawTimer();

	DrawScore();
}
//===============
// ゲームの状態
//===============
void SetTutorialState(TUTORIAL state)
{
	g_tutorial = state;
}
//=====================
// ゲームの状態の取得
//=====================
TUTORIAL GetTutorialSatate(void)
{
	return g_tutorial;
}