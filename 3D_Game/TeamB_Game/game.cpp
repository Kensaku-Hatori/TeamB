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
#include "particle.h"

//グローバル変数
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;  //ポーズ中かどうか

//=============
// 初期化処理
//=============
void InitGame(void)
{
	InitPolygon();

	InitShadow();

	InitBlock();

	InitPlayer();

	InitEnemy();

	InitEffect();

	InitParticle();

	InitExplosion();

	InitMeshCylinder();

	InitWall();

	InitMeshWall();
	
	InitCamera();

	InitLight();

	InitTimer();
	SetTimer(MAX_GAMETIME);

	InitScore();
	SetScore(0);

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

}
//===========
// 更新処理
//===========
void UpdateGame(void)
{
	int nTime = GetTimer();

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

		//リザルトに飛ぶ
		if (KeyboardTrigger(DIK_1) == true || GetJoypadTrigger(JOYKEY_START) == true)
		{
			SetFade(MODE_RESULT);
		}
	}
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