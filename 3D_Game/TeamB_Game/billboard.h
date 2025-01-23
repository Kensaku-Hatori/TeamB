//================================
//
// ビルボード処理[Biillboard.h]
// Author:kaiti
//
//================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

#define MAX_BILLBOARD (10)

//ビルボードの構造体
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	bool bUse;
}Biillboard;

//プロトタイプ宣言
void InitBiillboard(void);
void UninitBiillboard(void);
void UpdateBiillboard(void);
void DrawBiillboard(void);
void SetBiillboard(D3DXVECTOR3 pos);

#endif