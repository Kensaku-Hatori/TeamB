//=========================================================
// 
// 敵のHPゲージ[HPgauge.h]
// Aothor:Rio Ohno
// 
//=========================================================

#ifndef HPGAUGE_H_
#define HPGAUGE_H_

#include "main.h"

//マクロ定義
#define MAX_HPGAUGE (32)		//ゲージの最大の数

//HPゲージ構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	LPDIRECT3DVERTEXBUFFER9 pVtxHPgaugeBuff;
	int nLife;
	bool bUse;
}HPgauge;

//プロトタイプ宣言
void InitHPgauge();
void UninitHPgauge();
void UpdateHPgauge();
void DrawHPgauge();

#endif // !HPGAUGE_H_
