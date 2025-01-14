//================================
//
//  ゲーム画面表示処理[game.cpp]
//  Author:kaiti
//
//================================
#include "game.h"
#include "result.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "player.h"
#include "shadow.h"
#include "wall.h"
#include "explosion.h"
#include "effect.h"
#include "block.h"
#include "meshwall.h"
#include "meshcylinder.h"
#include "fade.h"
#include "timer.h"
#include "pause.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "balltimer.h"
#include "ballgauge.h"
#include "particle.h"
#include "killcount.h"

//グローバル変数
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;  //ポーズ中かどうか
int g_nEnemyTime;
int nEnemyX, nEnemyZ;

//=============
// 初期化処理
//=============
void InitGame(void)
{
	InitPolygon();

	InitShadow();

	InitBlock();
	//柱
	SetBlock(D3DXVECTOR3(300.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(450.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(600.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(300.0f, 0.0f, 450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(450.0f, 0.0f, 450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(600.0f, 0.0f, 450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(300.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(450.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(600.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);	

	SetBlock(D3DXVECTOR3(-650.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(-550.0f, -25.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(-450.0f, -50.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);	
	SetBlock(D3DXVECTOR3(-450.0f, -75.0f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(-450.0f, -100.0f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);	
	SetBlock(D3DXVECTOR3(-550.0f, -125.0f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);
	SetBlock(D3DXVECTOR3(-650.0f, -150.0f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_PILLAR);

	//ブロック
	SetBlock(D3DXVECTOR3(-100.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);
	SetBlock(D3DXVECTOR3(100.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);
	SetBlock(D3DXVECTOR3(-100.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);
	SetBlock(D3DXVECTOR3(100.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);

	SetBlock(D3DXVECTOR3(-111.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);
	SetBlock(D3DXVECTOR3(-241.0f, -20.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);
	SetBlock(D3DXVECTOR3(-316.0f, -5.0f, 390.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);
	SetBlock(D3DXVECTOR3(-420.0f, -50.0f, 490.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);
	SetBlock(D3DXVECTOR3(-516.0f, -10.0f, 290.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);

	SetBlock(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_NORMAL);

	//壁
	SetBlock(D3DXVECTOR3(-650.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_WALL);
	SetBlock(D3DXVECTOR3(-650.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_WALL);

	SetBlock(D3DXVECTOR3(450.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_WALL);
	SetBlock(D3DXVECTOR3(400.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_WALL);

	InitPlayer();

	InitEnemy();
	SetEnemy(D3DXVECTOR3(150.0f, 300.0f, 150.0f));

	g_nEnemyTime = MAX_ENEMYTIME;
	nEnemyX = 0;
	nEnemyZ = 0;

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
	
	SetMeshWall(D3DXVECTOR3(-3000.0f, -500.0f, 3000.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f));// 0
	SetMeshWall(D3DXVECTOR3(-3000.0f, 1500.0f, -3000.0f), D3DXVECTOR3(-D3DX_PI / 2, 0.0f, 0.0f));// 1

	InitCamera();

	InitLight();

	InitTimer();
	SetTimer(MAX_GAMETIME);

	InitScore();
	SetScore(0);

	InitBallTimer();
	SetBallTimer(MAX_BALLTIME);

	InitBallGauge();

	InitKillCount();
	SetKillCount(0);

	InitPause();

	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;

	g_bPause = false;  //ポーズ解除
}
//===========
// 終了処理
//===========
void UninitGame(void)
{
	UninitPause();

	UninitShadow();

	UninitPlayer();

	UninitEnemy();

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
void UpdateGame(void)
{
	int nTime = GetTimer();

	//敵出現用
	int x,a;
	float kake;
	srand((unsigned int)time(NULL));
	x = rand() % 5 + 1;//
	a = rand() % 2 + 1;//掛ける値
	if (a == 1)
	{//１なら
		kake = -100;
	}
	else
	{//それ以外
		kake = 100;
	}

	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{//ポーズキーが押された
		StopSound(SOUND_LABEL_GAME);
		PlaySound(SOUND_LABEL_PAUSE);
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{//ポーズ中
		//ポーズの更新処理
		UpdatePause();
	}
	else if (g_bPause == false)
	{
		UpdatePolygon();

		UpdateShadow();

		UpdatePlayer();

		UpdateEnemy();

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

		switch (g_gamestate)
		{
		case GAMESTATE_NORMAL:
			break;
		case GAMESTATE_TIMEOVER:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 30)
			{
				g_gamestate = GAMESTATE_NONE;
				//モードをリザルトにする
				SetFade(MODE_RESULT);
			}
			break;
		}

		//出現時間
		g_nEnemyTime--;
		if (nTime <= MAX_GAMETIME / 2)
		{
			g_nEnemyTime--;
		}

		if (g_nEnemyTime <= 0)
		{//０の時
			srand((unsigned int)time(NULL));
			nEnemyZ = rand() % 5 + 1;
			//出現させる
			SetEnemy(D3DXVECTOR3(nEnemyX * kake + nTime, 300.0f, nEnemyZ * kake + nTime));
			if (nTime <= MAX_GAMETIME / 2)
			{
				SetEnemy(D3DXVECTOR3(nEnemyX / kake + nTime, 300.0f, nEnemyZ * kake - nTime));
			}
			g_nEnemyTime = MAX_ENEMYTIME;
		}

		//リザルトに飛ぶ
		if (KeyboardTrigger(DIK_1) == true || GetJoypadTrigger(JOYKEY_START) == true)
		{
			SetFade(MODE_RESULT);
		}
	}
	//今回の値を保存
	nEnemyX = x;
}
//===========
// 描画処理
//===========
void DrawGame(void)
{
	SetCamera();

	DrawPolygon();

	DrawShadow();

	DrawBlock();

	DrawPlayer();

	DrawEnemy();

	DrawExplosion();

	DrawEffect();

	DrawParticle();

	DrawMeshCylinder();

	DrawWall();

	DrawMeshWall();

	DrawTimer();

	DrawScore();

	DrawBallGauge();
#ifdef _DEBUG
	DrawBallTimer();
#endif
	DrawKillCount();

	if (g_bPause == true)
	{//ポーズ中
		//ポーズ
		DrawPause();
	}
}
//===============
// ゲームの状態
//===============
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
}
//=====================
// ゲームの状態の取得
//=====================
GAMESTATE GetGameSatate(void)
{
	return g_gamestate;
}
//=======================
// ポーズの有効無効設定
//=======================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}