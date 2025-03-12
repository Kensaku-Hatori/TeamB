//=======================================================
// 
// 矢印[arrow.h]
// Author:Rio Ohno
// 
//=======================================================

#ifndef ARROW_H_
#define ARROW_H_

#include "main.h"

//マクロ定義
#define ARROW_TEX "data\\TEXTURE\\sirusi.png"					//矢印のテクスチャパス
#define MAX_ARROW (64)

//arrow
typedef struct
{
	D3DXVECTOR3 Destpos;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	D3DXMATRIX mtxWorld;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	LPDIRECT3DTEXTURE9 tex;
	float fHeight;
	float fWidth;
	float fRadius;
	bool bAnim;
	bool bUse;
}Arrow;

//プロトタイプ宣言
void InitArrow(void);
void UninitArrow(void);
void UpdateArrow(void);
void DrawArrow(void);
void SetArrow(D3DXVECTOR3 DestPos, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, float fRadius, bool bGradation, bool bAnim);
void SetPositonArrow(int nIdex, D3DXVECTOR3 pos);

#endif // !ARROW_H_
