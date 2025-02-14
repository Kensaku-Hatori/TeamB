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
#include "meshwall.h"
//#include "meshcylinder.h"
#include "meshfield.h"
#include "fade.h"
#include "pause.h"
//#include "sound.h"
#include "particle.h"
#include "skill.h"
#include "ui.h"
#include "particleEditer.h"
#include "loadstage.h"
#include "model.h"
#include "enemy.h"
#include "Item.h"
#include "loadmotion.h"
#include "wave.h"
#include "impact.h"
#include "invisiblewall.h"
#include "Item.h"
#include "circle.h"
#include "arrow.h"
#include "boss.h"

//グローバル変数
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;  //ポーズ中かどうか

//=============
// 初期化処理
//=============
void InitGame(void)
{
	MODE Mode = GetMode();
	//メッシュフィールドの初期化
	InitMeshfield();

	//サークルの初期化
	InitCircle();

	//矢印の初期化
	InitArrow();

	//影の初期化
	InitShadow();

	//衝撃波の初期化
	InitImpact();

	////ブロックの初期化
	//InitBlock();

	//プレイヤーの初期化
	InitPlayer();

	//敵の初期化
	InitBoss();

	//敵の初期化
	InitEnemy();

	//魔法の初期化
	InitSkill();

	//エフェクトの初期化
	InitEffect();

	//パーティクルの初期化
	InitParticle();

	////爆発の初期化
	//InitExplosion();

	//メッシュシリンダーの初期化
	//InitMeshCylinder();

	////壁の初期化
	//InitWall();

	//メッシュ壁の初期化
	InitMeshWall();

	//アイテム初期化
	InitItem();
	
	//カメラの初期化
	InitCamera();

	//ライトの初期化
	InitLight();

	//UIの初期化
	InitUi();

	//ポーズの初期化
	InitPause();

	//ステージの初期化
	InitStageModel();

	//モーションの初期化
	InitMotion();

	//モデルビューワーの読込
	LoadModelViewer(Mode);

	//ウェーブの初期化処理
	InitWave(Mode);

	//ウェーブの読込処理
	LoadWave();

	// 見えない壁の初期化処理
	InitInvisibleWall();

	//各初期化
	g_gamestate = GAMESTATE_NORMAL;		//ゲームステート
	g_nCounterGameState = 0;			//ステートカウンター
	srand((int)time(0));				//シード値(アイテムrand)

	g_bPause = false;					//ポーズしていない状態へ
}

//===========
// 終了処理
//===========
void UninitGame(void)
{
	//ポーズの終了処理
	UninitPause();

	//メッシュフィールドの終了処理
	UninitMeshfield();

	//サークルの終了処理
	UninitCircle();

	//矢印の終了処理
	UninitArrow();

	//影の終了処理
	UninitShadow();

	//衝撃波の終了処理
	UninitImpact();

	//プレイヤーの終了処理
	UninitPlayer();

	//敵の終了処理
	UninitEnemy();

	//敵の終了処理
	UninitBoss();

	//魔法の終了処理
	UninitSkill();

	//エフェクトの終了処理
	UninitEffect();

	//UninitBlock();

	//UninitExplosion();

	//UninitMeshCylinder();

	//UninitWall();

	//メッシュ壁の終了処理
	UninitMeshWall();

	//アイテムの終了処理
	UninitItem();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//UIの終了処理
	UninitUi();

	//ステージの終了処理
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
			//メッシュフィールドの更新処理
			UpdateMeshfield();

			//サークルの更新処理
			UpdateCircle();

			//矢印の更新処理
			UpdateArrow();

			//影の更新処理
			UpdateShadow();

			//衝撃波の更新処理
			UpdateImpact();

			//プレイヤーの更新処理
			UpdatePlayer();

			// 見えない壁の更新処理
			UpdateInvisibleWall();

			//敵の更新処理
			UpdateEnemy();

			//敵の更新処理
			UpdateBoss();

			//魔法の更新処理
			UpdateSkill();

			//エフェクトの更新処理
			UpdateEffect();

			//パーティクルの更新処理
			UpdateParticle(true);

#ifdef _DEBUG

			//エディターの切り替え
			if (GetKeyboardPress(DIK_E) && GetKeyboardPress(DIK_F2))
			{
				InitParticleEditer();
				SetGameState(GAMESTATE_EFFECTEDITER);
			}
			//リザルトに飛ぶ
			if (KeyboardTrigger(DIK_1) == true || GetJoypadTrigger(JOYKEY_START) == true)
			{//Clear
				SetFade(MODE_RESULT);
				SetResult(RESULT_CLEAR);
			}
			if (KeyboardTrigger(DIK_2) == true || GetJoypadTrigger(JOYKEY_START) == true)
			{//over
				SetFade(MODE_RESULT);
				SetResult(RESULT_GAMEOVER);
			}

#endif // DEBUG

			////ブロックの更新処理
			//UpdateBlock();

			////爆発の更新処理
			//UpdateExplosion();

			////メッシュシリンダーの更新処理
			//UpdateMeshCylinder();

			////壁の更新処理
			//UpdateWall();

			//メッシュ壁の更新処理
			UpdateMeshWall();

			//アイテムの更新
			UpdateItem();

			//カメラの更新処理
			UpdateCamera();

			//ライトの更新処理
			UpdateLight();

			//UIの更新処理
			UpdateUi();

			//ステージの更新処理
			UpdateStageModel();

			//敵の数を取得する
			int* NumEnemy = GetNumEnemy();
			Player* pPlayer = GetPlayer();

			//全てのwaveが終わったなら
			if (GetFinish() == true)
			{
				g_gamestate = GAMESTATE_CLEAR;
			}

			//ゲームステート管理
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
		}
	}
	else
	{
	//パーティクルエディターの更新処理
		UpdateParticleEditer();
	}
}

//===========
// 描画処理
//===========
void DrawGame(void)
{
	//カメラの設定処理
	SetCamera();

	//メッシュフィールドの描画処理
	DrawMeshfield();

	//影の描画処理
	DrawShadow();

	////ブロックの描画処理
	//DrawBlock();

	////敵の描画処理
	//DrawEnemy();

	//爆発の描画処理
	//DrawExplosion();

	//魔法の描画処理
	DrawSkill();

	//メッシュシリンダーの描画処理
	//DrawMeshCylinder();

	////壁の描画処理
	//DrawWall();

	//メッシュ壁の描画処理
	DrawMeshWall();

	//ステージの描画処理
	DrawStageModel();

	//エフェクトの描画処理
	DrawEffect();

	//アイテムの描画処理
	DrawItemBillboard();

	//エディターではないなら
	if (g_gamestate != GAMESTATE_EFFECTEDITER)
	{
		//プレイヤーの描画処理
		DrawPlayer();

		//敵の描画処理
		DrawEnemy();

		//敵の描画処理
		DrawBoss();

		//矢印の描画処理
		DrawArrow();

		//サークルの描画処理
		DrawCircle();

		//UIの描画処理
		DrawUi();

		//衝撃波の描画処理
		DrawImpact();
	}

	//ポーズしているなら
	if (g_bPause == true)
	{//ポーズ中
		//ポーズの描画処理
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