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

//ビルボードの構造体
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 StartPos;		// 最初の位置
	D3DXVECTOR3 move;			// 移動量
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 dir;			// 向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	int nIdxShadow;				// 影のインデックス保存用
	int nLife;					// 寿命
	float fDistance;			// 距離
	bool bHit;
	bool bUse;					// 使用しているかどうか
}Skill;

//プロトタイプ宣言
void InitSkill(void);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);
void SetSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 rot);
bool SkillCollision(D3DXVECTOR3 pos,float radius);

#endif