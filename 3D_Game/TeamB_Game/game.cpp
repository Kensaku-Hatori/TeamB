//================================
//
//  ゲーム画面表示処理[game.cpp]
//  Author:kaiti
//
//================================

#include "game.h"
#include "result.h"
#include "resultinfo.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "player.h"
#include "shadow.h"
//#include "wall.h"
//#include "explosion.h"
//#include "effect.h"
//#include "block.h"
#include "meshwall.h"
//#include "meshcylinder.h"
#include "meshfield.h"
#include "fade.h"
#include "pause.h"
//#include "sound.h"
//#include "enemy.h"
#include "particle.h"
#include "skill.h"
#include "ui.h"
#include "particleEditer.h"
#include "loadstage.h"
#include "model.h"

//グローバル変数
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;  //ポーズ中かどうか

//=============
// 初期化処理
//=============
void InitGame(void)
{
	InitMeshfield();

	InitShadow();

	//InitBlock();

	InitPlayer();

	//InitEnemy();

	InitSkill();

	InitEffect();

	InitParticle();

	//InitExplosion();

	//InitMeshCylinder();

	//InitWall();

	InitMeshWall();
	
	InitCamera();

	InitLight();

	InitUi();

	InitPause();

	InitStageModel();

	LoadModelViewer();

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

	//UninitEnemy();

	UninitSkill();

	UninitEffect();

	//UninitBlock();

	UninitMeshfield();

	//UninitExplosion();

	//UninitMeshCylinder();

	//UninitWall();

	UninitMeshWall();

	UninitCamera();

	UninitLight();

	UninitUi();

	UninitStageModel();
}
//===========
// 更新処理
//===========
void UpdateGame(void)
{
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{//ポーズキーが押された
		g_bPause = g_bPause ? false : true;
	}

	if (g_gamestate != GAMESTATE_EFFECTEDITER)
	{
		if (g_bPause == true)
		{//ポーズ中
			//ポーズの更新処理
			UpdatePause();
		}
		else if (g_bPause == false)
		{
			UpdateMeshfield();

			UpdateShadow();

			UpdatePlayer();

			//UpdateEnemy();

			UpdateSkill();

			UpdateEffect();

			UpdateParticle(true);

			if (GetKeyboardPress(DIK_E) && GetKeyboardPress(DIK_F2))
			{
				InitParticleEditer();
				SetGameState(GAMESTATE_EFFECTEDITER);
			}

			//UpdateBlock();

			//UpdateExplosion();

			//UpdateMeshCylinder();

			//UpdateWall();

			UpdateMeshWall();

			UpdateCamera();

			UpdateLight();

			UpdateUi();

			UpdateStageModel();

			switch (g_gamestate)
			{
			case GAMESTATE_NORMAL:
				break;
			case GAMESTATE_CLEAR:
				g_nCounterGameState++;
				if (g_nCounterGameState >= 30)
				{
					g_gamestate = GAMESTATE_NONE;
					//モードをリザルトにする
					SetFade(MODE_RESULT);
					SetResult(RESULT_CLEAR);
				}
				break;
			case GAMESTATE_GAMEOVER:
				g_nCounterGameState++;
				if (g_nCounterGameState >= 30)
				{
					g_gamestate = GAMESTATE_NONE;
					//モードをリザルトにする
					SetFade(MODE_RESULT);
					SetResult(RESULT_GAMEOVER);
				}
				break;
			case GAMESTATE_EFFECTEDITER:
				break;
			}

			//リザルトに飛ぶ
			if (KeyboardTrigger(DIK_1) == true || GetJoypadTrigger(JOYKEY_START) == true)
			{
				SetFade(MODE_RESULT);
				SetResult(RESULT_CLEAR);
			}
			if (KeyboardTrigger(DIK_2) == true || GetJoypadTrigger(JOYKEY_START) == true)
			{
				SetFade(MODE_RESULT);
				SetResult(RESULT_GAMEOVER);
			}
		}
	}
	else
	{
		UpdateParticleEditer();
	}
}
//===========
// 描画処理
//===========
void DrawGame(void)
{
	SetCamera();

	DrawMeshfield();

	DrawShadow();

	//DrawBlock();


	//DrawEnemy();

	//DrawExplosion();

	DrawSkill();

	DrawEffect();

	//DrawMeshCylinder();

	//DrawWall();

	DrawMeshWall();

	DrawStageModel();

	if (g_gamestate != GAMESTATE_EFFECTEDITER)
	{
		DrawPlayer();
		DrawUi();
	}

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