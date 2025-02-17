//================================
//
// ビルボード処理[Biillboard.h]
// Author:kaiti
//
//================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

#define MAX_BILLBOARD (10)								//ビルボードの数

//ビルボードの構造体
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR2 origin;									//原点
	D3DXMATRIX mtxWorld;								//ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffBiillboard;			//頂点情報
	LPDIRECT3DTEXTURE9 pTextureBiillboard;
	int nIndexShadow;									//影のインデックス
	int textype;										//テクスチャの種類
	int nWidth;											//幅
	int nHeight;										//高さ
	bool bShadow;										//影をつけるかどうか
	bool bUse;											//使用しているかどうか
}Biillboard;

//プロトタイプ宣言
void InitBiillboard(void);
void UninitBiillboard(void);
void UpdateBiillboard(void);
void DrawBiillboard(void);
void SetBiillboard(D3DXVECTOR3 pos, int nWidth, int nHeigh, int textype, D3DXVECTOR2 origin, bool bShadow);
void SetBillTexture(int Indx);
#endif