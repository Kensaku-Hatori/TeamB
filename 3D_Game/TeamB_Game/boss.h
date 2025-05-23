//************************
// 
// 敵に関する処理[enemy.h]
// Hatori Kensaku
//
//************************
#ifndef BOSS_H_
#define BOSS_H_

#define BOSS_AP (200)
#define BOSS_HP (1000)
#define BOSS_SPEED (1)
#define	BOSSATTACK_DIST (10)
#define BOSSHORMING_DIST (300)
#define BOSSHORMING_MOVE (float)(-2.0f)
#define MAX_BOSSACTIONRANK (2)
#define BOSSACTION_JUSTIS (70)
#define MOVEEND_FLAME (180)
#define BOSS_SCORE (5000)

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

typedef struct
{
	BOSSACTION Action;
	float primary[BOSSACTION_MAX];
	int ActionEnd[BOSSACTION_MAX],ActionEndCounter;
	int routine, routinecount;
	bool bFinishAction;
}BossAi;

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
	BossAi BossAi;
	D3DXMATRIX mtxWand;				// 杖先のマトリックス
	int Action;
	int nNumKey, nKey, nCounterMotion, nNextKey;
	int nNumModel;
	int IndxShadow;
	int nActionCount, nActionCounter;
	int statecount;
	int CollModel;
	int MiniMapIndx;
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
void InitBoss(void);										// ボスの初期化処理
void UninitBoss(void);										// ボスの終了処理
void UpdateBoss(void);										// ボスの更新処理
void DrawBoss(void);										// ボスの描画処理
void NormalizeBossRot(void);
BOSS* GetBoss();											// ボスの取得処理

void HitBoss(float Atack);									// ボスのヒット処理
void DeadBoss();											// ボスの死亡処理

void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ボスの設定処理

void UpdateBossAction();									// ボスの行動パターン更新処理
void UpdateBossActionMove();
void BossState();											// ボスの状態更新処理
void SetBossPartsInfo(LoadInfo PartsInfo);					// ボスのバッファやモーション設定処理

void CollisionBosstoModel(void);							// ボスの当たり判定処理
void CollisionBoss(void);									// ボスの当たり判定処理
void CollisionBossAction(void);								// ボスのアクション時の当たり判定処理
void CollisionBosstoSkill(void);

void BossMatrixWand(void);
float Distance(D3DXVECTOR3 Pos, D3DXVECTOR3 Pos1);
void HormingPlayerMove(float Speed);
bool DethBoss(void);										// ボスの死亡フラグ取得処理
void Routine(void);
void EndAction(void);
#endif // !ENEMY_H_