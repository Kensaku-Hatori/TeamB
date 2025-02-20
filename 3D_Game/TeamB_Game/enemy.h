//************************
// 
// 敵に関する処理[enemy.h]
// Hatori Kensaku
//
//************************
#ifndef ENEMY_H_
#define ENEMY_H_

#include "main.h"
#include "key.h"
#include "Object.h"
#include "status.h"
#include "loadmotion.h"

#define MAX_ENEMY (126)					// 敵の最大数
#define MAX_ENEMYPARTS (10)				// 敵の最大パーツ数
#define ENEMY_RADIUS (float)(8.0f)		// 敵の大きさ
#define ENEMY_RUNSPEED (float)(1.0f)	// 敵の走るスピード

#define ENEMY_HP (float)(150)			// HP
#define ENEMY_SPEED (float) (2.0f)		// 速度
#define ENEMY_AP (float)(10)			// 攻撃力

// 行動の距離
#define ATTACK_DIST (float)(50.0f)		// 攻撃
#define HOMING_DIST (float)(300.0f)		// ホーミング

//フレーム
#define ATTACK_FREAM (180)				// 攻撃a

//移動量
#define HOMING_MOVE (float)(0.2f)		// ホーミング
#define WELL_MOVE (float)(0.1f)			// 様子見

// 敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_KNOCKUP,
	ENEMYSTATE_MAX
}ENEMYSTATE;

// 敵の行動パターン
typedef enum
{
	ENEMYACTION_WELL,
	ENEMYACTION_RUN,
	ENEMYACTION_ATTACK,
	ENEMYACTION_MAX
}ENEMYACTION;

// 敵の種類
typedef enum
{
	ENEMYTYPE_SKELETON = 0,
	ENEMYTYPE_ZOMBIE,
	ENEMYTyPE_MIDBOSS,
	ENEMYTYPE_MAX
}ENEMYTYPE;

// 敵のバッファ・モーション格納
typedef struct
{
	OBJECTINFO EnemyMotion;
	int nNumParts;
}EnemyOrigin;

// 敵の構造体
typedef struct
{
	ENEMYSTATE state;
	ENEMYACTION ActionType;
	EnemyStatus Status;
	MOTIONTYPE pMotion;
	OBJECTINFO EnemyMotion;
	OBJECT Object;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 move;
	int nType;
	int Action;
	int nNumKey, nKey, nCounterMotion, nNextKey;
	int nNumModel;
	int IndxShadow;
	int nActionCount,nActionCounter;
	int statecount;
	float ShadowRadius;
	float ModelMinX, ModelMaxX;
	float Radius;
	bool bUse;
	bool bMotion;
	bool bHit;
	int IndxGuage[3];
	float fDistance;
	float fActionDistance;

	float fSightRange;
	float fSightAngle;
	bool bLockOn;

}ENEMY;

//*****************
// プロトタイプ宣言
//*****************
void InitEnemy(void);										// 敵の初期化処理
void UninitEnemy(void);										// 敵の終了処理
void UpdateEnemy(void);										// 敵の更新処理
void DrawEnemy(void);										// 敵の描画処理
ENEMY* GetEnemy();											// 敵の取得処理
int* GetNumEnemy(void);										// 敵の総数取得処理
void HitEnemy(float Atack,int Indx);						// 敵のヒット処理
void DeadEnemy(int Indx);									// 敵の死亡処理
void SetEnemy(D3DXVECTOR3 pos, int nType,D3DXVECTOR3 rot);	// 敵の設定処理
void UpdateAction(int nCount);								// 敵の行動パターン更新処理
void EnemyState(int Indx);									// 敵の状態更新処理
void SetEnemyPartsInfo(LoadInfo PartsInfo, int nType);		// 敵のバッファやモーション設定処理
void CollisionEnemy(void);									// 敵の当たり判定処理
void CollisionEnemyAction(int nCnt);						// 敵のアクション時の当たり判定処理
bool IsPlayerInsight(int Index);

#endif // !ENEMY_H_