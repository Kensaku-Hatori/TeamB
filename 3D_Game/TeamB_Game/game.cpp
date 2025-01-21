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
//#include "meshwall.h"
//#include "meshcylinder.h"
#include "meshfield.h"
#include "fade.h"
#include "pause.h"
//#include "sound.h"
//#include "enemy.h"
//#include "particle.h"
#include "skill.h"
#include "ui.h"

//グローバル変数
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;  //ポーズ中かどうか

//=============
// 初期化処理
//=============
void InitGame(void)
{
	//char cData[32];
	//strcpy(&cData[0], "data\\TEXTURE\\ranking.jpg");

	InitPolygon();

	//SetTexture(cData);
	//InitMeshfield();
	//SetMeshfield(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 0, 0, 0, 150, 150);
	

	InitShadow();

	//InitBlock();

	InitPlayer();

	//InitEnemy();

	InitSkill();

	//InitEffect();

	//InitParticle();

	//InitExplosion();

	//InitMeshCylinder();

	//InitWall();

	//InitMeshWall();
	
	InitCamera();

	InitLight();

	InitUi();

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

	//UninitEnemy();

	UninitSkill();

	//UninitEffect();

	//UninitParticle();

	//UninitBlock();

	UninitPolygon();
	//UninitMeshfield();

	//UninitExplosion();

	//UninitMeshCylinder();

	//UninitWall();

	//UninitMeshWall();

	UninitCamera();

	UninitLight();

	UninitUi();
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

	if (g_bPause == true)
	{//ポーズ中
		//ポーズの更新処理
		UpdatePause();
	}
	else if (g_bPause == false)
	{
		UpdatePolygon();
		//UpdateMeshfield();

		UpdateShadow();

		UpdatePlayer();

		//UpdateEnemy();

		UpdateSkill();

		//UpdateEffect();

		//UpdateParticle();

		//UpdateBlock();

		//UpdateExplosion();

		//UpdateMeshCylinder();

		//UpdateWall();

		//UpdateMeshWall();

		UpdateCamera();

		UpdateLight();

		UpdateUi();

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
//===========
// 描画処理
//===========
void DrawGame(void)
{
	SetCamera();

	DrawPolygon();
	//DrawMeshfield();

	DrawShadow();

	//DrawBlock();

	DrawPlayer();

	//DrawEnemy();

	//DrawExplosion();

	DrawSkill();

	//DrawEffect();

	//DrawParticle();

	//DrawMeshCylinder();

	//DrawWall();

	//DrawMeshWall();

	DrawUi();

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