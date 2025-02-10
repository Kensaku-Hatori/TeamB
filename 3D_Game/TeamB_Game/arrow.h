//=======================================================
// 
// 矢印[arrow.h]
// Author:Rio Ohno
// 
//=======================================================

#ifndef ARROW_H_
#define ARROW_H_

#include "main.h"

//arrow
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
}Arrow;

//プロトタイプ宣言
void InitArrow();
void UninitArrow();
void UpdateArrow();
void DrawArrow();
void SetArrow();

#endif // !ARROW_H_
