//******************************************
//
// 見えない壁との当たり判定[invisiblewall.h]
// Hatori Kensaku
//
//******************************************
#ifndef INVISIBLEWALL_H_
#define INVISIBLEWALL_H_

#include "main.h"
#include "player.h"
#include "fade.h"

// 一ステージに出したい見えない壁の種類
typedef enum
{
	WALLTYPE_ENTRANCE = 0,
	WALLTYPE_EXIT,
	WALLTYPE_MAX
}WALLTYPE;

// 見えない壁との当たり判定に必要な構造体
typedef struct
{
	D3DXVECTOR3 Top, Left, Right, Bottom, Center;
	D3DXVECTOR3 norTop, norLeft, norRight, norBottom,norWall;
	MODE MoveStageNum;
	D3DXVECTOR3 PlayerPos;
}Invisiblewall;

void InitInvisibleWall();											// 見えない壁の初期化処理
void UpdateInvisibleWall();											// 見えない壁の更新処理
void CollisionInvisibleWall(Invisiblewall Box, D3DXVECTOR3 Point,D3DXVECTOR3 &NextPoint);	// 見えない壁との当たり判定
D3DXVECTOR2 Gettest();	// デバック用
#endif // !INVISIBLEWALL_H_