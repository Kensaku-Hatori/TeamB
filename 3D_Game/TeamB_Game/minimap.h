//==============================
//
//  ミニマップ処理[minimap.h]
//  Author:kaiti
//
//==============================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#include "main.h"
#include "enemy.h"

#define MINIMAP_X (250)
#define MINIMAP_Y (230)

#define MAPSIZE_PLAYER (30)
#define MAPSIZE_ENEMY (30)
#define MAPSIZE_SIGHT (float)(1000.0f)
#define ENEMYANGLE (atan2f(MAPSIZE_ENEMY,MAPSIZE_ENEMY))

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffMapEnemy;
	D3DXVECTOR3 MiniMappos;
	float fAngle,fDistance;
	bool bUse;
}MiniMapEnemy;

//プロトタイプ宣言
void InitMiniMap(void);
void UninitMiniMap(void);
void UpdateMiniMap(void);
void UpdateMiniMapSight(void);
void UpdateMiniMapEnemy(int Indx,D3DXVECTOR3 PosEnemy);
void DrawMiniMap(void);
void SetMapPlayer(int nStageNo);
int SetMapEnemy(D3DXVECTOR3 Pos);
void DeleteEnemyMiniMap(int Indx);
#endif