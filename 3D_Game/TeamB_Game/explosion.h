//================================
//
// ビルボード処理[Explosion.h]
// Author:kaiti
//
//================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

#define MAX_EXPLOSION (128)

//ビルボードの構造体
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	int nCounterAnim;
	int nPattemAnim;
	bool bUse;
}Explosion;

//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 dir);

#endif