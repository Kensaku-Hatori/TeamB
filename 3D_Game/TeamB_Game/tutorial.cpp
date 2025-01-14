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
#include "balltimer.h"
#include "ballgauge.h"
#include "particle.h"
#include "killcount.h"

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
	SetBlock(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);

	InitPlayer();

	InitEnemy();
	SetEnemy(D3DXVECTOR3(150.0f, 300.0f, 150.0f));

	InitBiillboard();
	SetBiillboard(D3DXVECTOR3(0.0f, 50.0f, 100.0f));	// 移動
	SetBiillboard(D3DXVECTOR3(-350.0f, 50.0f, -50.0f)); // ジャンプ
	SetBiillboard(D3DXVECTOR3(130.0f, 50.0f, 100.0f));	// アクション
	SetBiillboard(D3DXVECTOR3(0.0f, 150.0f, 100.0f));	// タイトルに戻る
	SetBiillboard(D3DXVECTOR3(-130.0f, 50.0f, 100.0f));	// 視点移動
	SetBiillboard(D3DXVECTOR3(0.0f, 50.0f, -300.0f));	// ストライク

	InitEffect();

	InitParticle();

	InitExplosion();

	InitMeshCylinder();

	InitWall();

	SetWall(D3DXVECTOR3(0.0f, -WALL_HEIGHT, POLYGON_Y), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1.0f);//外 0
	SetWall(D3DXVECTOR3(0.0f, -WALL_HEIGHT, -POLYGON_Y), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);//外 1
	SetWall(D3DXVECTOR3(POLYGON_X, -WALL_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 1.0f);//外 2
	SetWall(D3DXVECTOR3(-POLYGON_X, -WALL_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 1.0f);//外 3

	InitMeshWall();

	SetMeshWall(D3DXVECTOR3(-3000.0f, -500.0f, 3000.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f));// 床
	SetMeshWall(D3DXVECTOR3(-3000.0f, 1500.0f, -3000.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f));// 天井

	InitCamera();

	InitLight();

	InitTimer();
	SetTimer(MAX_TUTORIALTIME);

	InitScore();
	SetScore(0);

	InitBallTimer();
	SetBallTimer(MAX_BALLTIME);

	InitBallGauge();

	InitKillCount();
	SetKillCount(0);

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

	UninitBallGauge();

	UninitBallTimer();

	UninitKillCount();
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

	UpdateBallGauge();

	UpdateBallTimer();

	UpdateKillCount();

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
		StopSound(SOUND_LABEL_GAME);
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

	DrawBallGauge();

#ifdef _DEBUG
	DrawBallTimer();
#endif

	DrawKillCount();
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