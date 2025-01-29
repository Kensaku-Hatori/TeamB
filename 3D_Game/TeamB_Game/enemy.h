#ifndef ENEMY_H_
#define ENEMY_H_

#include "main.h"
#include "key.h"
#include "Object.h"
#include "status.h"
#include "loadmotion.h"

#define MAX_ENEMY (126)
#define MAX_ENEMYPARTS (10)
#define ENEMY_RADIUS (float)(8.0f)
#define ENEMY_RUNSPEED (float)(1.0f)

#define ENEMY_HP (float)(150)		// HP
#define ENEMY_SPEED (float) (2.0f)	// 速度
#define ENEMY_AP (float)(10)		// 攻撃力

typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_KNOCKUP,
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef enum
{
	ENEMYACTION_WELL,
	ENEMYACTION_RUN,
	ENEMYACTION_ATACK,
	ENEMYACTION_MAX
}ENEMYACTION;

typedef enum
{
	ENEMYTYPE_SKELETON = 0,
	ENEMYTYPE_BOSS,
	ENEMYTYPE_MAX
}ENEMYTYPE;

typedef struct
{
	OBJECTINFO EnemyMotion;
	int nNumParts;
}EnemyOrigin;

typedef struct
{
	ENEMYSTATE state;
	OBJECTINFO EnemyMotion;
	OBJECT Object;
	MOTIONTYPE pMotion;
	int nType;
	EnemyStatus Status;
	D3DXVECTOR3 move;
	int Action;
	int nNumKey, nKey, nCounterMotion, nNextKey;
	int nNumModel;
	int IndxShadow;
	int nActionCount,nActionCounter;
	int statecount;
	float ModelMinX, ModelMaxX;
	float Radius;
	bool bUse;
	bool bMotion;
	bool bHit;
	int IndxGuage[3];
	float fDistance;

}ENEMY;

//*****************
// プロトタイプ宣言
//*****************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY* GetEnemy();
int* GetNumEnemy(void);
void HitEnemy(float Atack,int Indx);
void DeadEnemy(int Indx);
void SetEnemy(D3DXVECTOR3 pos, int nType,D3DXVECTOR3 rot);
void UpdateAction(int nCount);
void EnemyState(int Indx);
void SetnNumParts(int nType,int nNumParts);
void SetEnemyMesh(char* pFilePath, int Indx);
void SetEnemyPartsInfo(LoadInfo PartsInfo, int nType);
void EnemyMotion(MOTIONINFO* pMotionInfo);
void CollisionEnemy(void);
#endif // !ENEMY_H_