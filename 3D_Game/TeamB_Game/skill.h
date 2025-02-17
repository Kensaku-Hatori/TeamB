//================================
//
// 弾処理[skill.h]
// Author:kaiti
//
//================================
#ifndef _SKILL_H_
#define _SKILL_H_

#include "main.h"

#define MAX_SKILL (256)
#define SKILL_LIFE (30)
#define SKILL_SIZE (float)(2.5)
#define INTERVAL_IMPACT (30)
#define DISTANCE_HORMING (100)
#define INTERVAL_HORMING (100)
#define HORMING_SPEEDANIM (100)

typedef enum
{
	SKILLTYPE_NONE = 0,
	SKILLTYPE_HORMING,
	SKILLTYPE_MAX
}SKILLTYPE;
//ビルボードの構造体
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 StartPos;		// 最初の位置
	D3DXVECTOR3 move;			// 移動量
	D3DXVECTOR3 moveDest;		// 移動量
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 dir;			// 向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	SKILLTYPE ntype;
	int nIdxShadow;				// 影のインデックス保存用
	int nLife;					// 寿命
	int nCount, nCounter;
	int nIndxHorming;
	int AnimCounter;
	float fDistance;			// 距離
	float Speed;
	float fRotRatio;
	bool bHit;
	bool bUse;					// 使用しているかどうか
	bool bHorming;
}Skill;

//プロトタイプ宣言
void InitSkill(void);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);
void SetSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 rot, SKILLTYPE ntype,float fRotRatio);
void SerchHormingEnemy(int Indx);
void UpdateHormingPosition(int Indx);
void UpdateHormingAnim(int Indx);
Skill* GetSkill();
#endif