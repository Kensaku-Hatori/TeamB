//*********************************************************
// 
// ボスのムービー[bossmovie.cpp]
// Author:Hatori
// 
//*********************************************************

#include "bossmovie.h"
#include "meshfield.h"
#include "boss.h"
#include "camera.h"
#include "light.h"
#include "pause.h"
#include "wave.h"
#include "invisiblewall.h"
#include "shadow.h"
#include "player.h"
#include "sound.h"

//***********************************
// ボスのムービーに関する処理の初期化
//***********************************
void InitBossMovie()
{
	Camera* pCamera = GetCamera();
	MODE Mode = GetMode();

	InitBossNameEffect();

	//メッシュフィールドの初期化
	InitMeshfield();

	//敵の初期化
	InitBoss();

	//カメラの初期化
	InitCamera();

	//ライトの初期化
	InitLight();

	//ポーズの初期化
	InitPause();

	//ステージの初期化
	InitStageModel();

	//モーションの初期化
	InitMotion();

	InitShadow();

	InitPlayer();

	SetRotDest(D3DXVECTOR3(0.0f,D3DX_PI,0.0f));

	//モデルビューワーの読込
	LoadModelViewer(MODE_STAGEFOUR);

	//ウェーブの初期化処理
	InitWave(MODE_STAGEFOUR);

	//ウェーブの読込処理
	LoadWave();

	// 見えない壁の初期化処理
	InitInvisibleWall();

	//カメラの位置設定
	D3DXVECTOR3 CameraPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	ResetCameraPos(CameraPos, D3DXVECTOR3(0.0f,100.0f,300.0f));

	SetCameraWork(&pCamera->Anim, ANIMTYPE_TWO);

	StopSound();
	PlaySound(SOUND_LABEL_BOSSMOVIE);
}

//*************************************
// ボスのムービーに関する処理の終了処理
//*************************************
void UninitBossMovie()
{
	UninitBossNameEffect();
	UninitPlayer();
	UninitMeshfield();
	UninitBoss();
	UninitCamera();
	UninitLight();
	UninitPause();
	UninitStageModel();
	UninitShadow();
}

//*************************************
// ボスのムービーに関する処理の更新処理
//*************************************
void UpdateBossMovie()
{
	UpdateBossNameEffect();
	UpdateBoss();
	UpdateMovie();
	UpdatePlayer();
}

//*************************************
// ボスのムービーに関する処理の描画処理
//*************************************
void DrawBossMovie()
{
	//カメラの設定処理
	SetCamera();

	//メッシュフィールドの描画処理
	DrawMeshfield();

	DrawShadow();

	//敵の描画処理
	DrawBoss();

	//ステージの描画処理
	DrawStageModel();

	DrawPlayer();

	DrawBossNameEffect();
}