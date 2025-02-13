//************************
// 
// 敵に関する処理[enemy.h]
// Hatori Kensaku
//
//************************
#ifndef BOSS_H_
#define BOSS_H_

#define BOSS_AP (10)
#define BOSS_HP (100)
#define BOSS_SPEED (1)
#define	BOSSATTACK_DIST (50)
#define BOSSHORMING_DIST (150)
#define BOSSHORMING_MOVE (float)(-2.0f)

#include "main.h"
#include "key.h"
#include "Object.h"
#include "status.h"
#include "loadmotion.h"

// 敵の状態
typedef enum
{
	BOSSSTATE_NORMAL = 0,
	BOSSSTATE_KNOCKUP,
	BOSSSTATE_MAX
}BOSSSTATE;

// 敵の行動パターン
typedef enum
{
	BOSSACTION_WELL,
	BOSSACTION_RUN,
	BOSSACTION_ATTACK,
	BOSSACTION_MAX
}BOSSACTION;

// 敵のバッファ・モーション格納
typedef struct
{
	OBJECTINFO BossMotion;
	int nNumParts;
}BossOrigin;

// 敵の構造体
typedef struct
{
	BOSSSTATE state;
	BOSSACTION ActionType;
	BossStatus Status;
	MOTIONTYPE pMotion;
	OBJECTINFO BossMotion;
	OBJECT Object;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	int Action;
	int nNumKey, nKey, nCounterMotion, nNextKey;
	int nNumModel;
	int IndxShadow;
	int nActionCount, nActionCounter;
	int statecount;
	float ShadowRadius;
	float ModelMinX, ModelMaxX;
	float Radius;
	bool bUse;
	bool bMotion;
	bool bHit;
	int IndxGuage[3];
	float fDistance;

}BOSS;

//*****************
// プロトタイプ宣言
//*****************
void InitBoss(void);										// 敵の初期化処理
void UninitBoss(void);										// 敵の終了処理
void UpdateBoss(void);										// 敵の更新処理
void DrawBoss(void);										// 敵の描画処理
BOSS* GetBoss();											// 敵の取得処理
void HitBoss(float Atack);						// 敵のヒット処理
void DeadBoss();									// 敵の死亡処理
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 敵の設定処理
void UpdateBossAction();								// 敵の行動パターン更新処理
void BossState();									// 敵の状態更新処理
void SetBossPartsInfo(LoadInfo PartsInfo);		// 敵のバッファやモーション設定処理
void CollisionBoss(void);									// 敵の当たり判定処理
#endif // !ENEMY_H_