//============================
//
// ポリゴン表示処理[Wall.h]
// Author:kaiti
//
//============================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

#define MAX_WALL (4)
#define WALL_HEIGHT (75)
#define WALL_WIDTH (75)

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	bool bUse;
}Wall;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float a);
void CollisionWall(void);
Wall* GetWall(void);

#endif