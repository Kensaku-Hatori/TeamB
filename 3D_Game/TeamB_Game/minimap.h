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
#define ENEMYANGLE (atan2f(30.0f,30.0f))

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
void UpdateMiniMapEnemy(int Indx,D3DXVECTOR3 PosEnemy);
void DrawMiniMap(void);
void SetMapPlayer(int nStageNo);
int SetMapEnemy(D3DXVECTOR3 Pos);
#endif