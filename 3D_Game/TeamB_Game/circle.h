//=======================================================
// 
// サークル[circle.h]
// Author:Rio Ohno
// 
//=======================================================

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "main.h"

//マクロ定義
#define MAX_CIRCLE (1)

//circle
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	LPDIRECT3DINDEXBUFFER9 IndxBuff;
	int nDiviX;
	int nDiviY;
	int nMaxVtx;
	int nPolyNum;
	float fRadius;
	bool bAnime;
	bool bUse;
}Circle;

//プロトタイプ宣言
void InitCircle();
void UninitCircle();
void UpdateCircle();
void DrawCircle();
void SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int DiviX, int DiviY, float fRadius, bool bAnime, bool bUse);

#endif // !CIRCLE_H_

