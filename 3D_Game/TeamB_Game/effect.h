//================================
//
// エフェクト処理[Effect.h]
// Author:kaiti
//
//================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

#define MAX_EFFECT (1280)
#define EFFECT_LIFE (25)
#define EFFECT_SIZE (10)

typedef enum
{
	EFFECTDRAW_NUM = 0,
	EFFECTDRAW_BILLBOARD,
	EFFECTDRAW_MAX
}EFFECTDRAW;

//ビルボードの構造体
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//位置
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	float fRadius;
	int nLife;
	bool bUse;
}Effect;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR color, int nLife, float fRadius);

#endif