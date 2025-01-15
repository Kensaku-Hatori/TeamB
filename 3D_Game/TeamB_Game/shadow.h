//================================
//
// 影表示処理[shadow.h]
// Author:kaiti
//
//================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

#define MAX_SHADOW (128)

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	bool bUse;
}Shadow;

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos,bool bUse);
Shadow* GetShadow(void);

#endif