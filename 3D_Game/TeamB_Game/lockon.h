//============================
//
// ロックオン処理[lockon.h]
// Author:kaiti
//
//============================
#ifndef _LOCKON_H
#define _LOCKON_H_

#include "main.h"

#define LOCKON_SIZE (20)

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	bool bUse;
}Lockon;

//プロトタイプ宣言
void InitLockon(void);
void UninitLockon(void);
void UpdateLockon(void);
void DrawLockon(void);
bool IsEnemyInsight(void);
bool EnemyDistanceSort(int EnemyCount);


#endif
