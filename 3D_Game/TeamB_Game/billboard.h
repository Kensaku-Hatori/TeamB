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
	D3DXVECTOR3 origin;				//原点
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	int textype;					//テクスチャの種類
	int nWidth;						//幅
	int nHeight;					//高さ
	bool bUse;						//使用しているかどうか
}Biillboard;

//プロトタイプ宣言
void InitBiillboard(void);
void UninitBiillboard(void);
void UpdateBiillboard(void);
void DrawBiillboard(void);
void SetBiillboard(D3DXVECTOR3 pos);

#endif