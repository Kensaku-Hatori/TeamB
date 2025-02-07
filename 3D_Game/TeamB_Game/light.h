//================================
//
//　ウインドウ表示処理[light.h]
//　Author:kaiti
//
//================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

#define MAX_LIGHT (3)

//プロトタイプ宣言
void InitLight(void);
void UninitLight(void);
void UpdateLight(void);
void SetLight(D3DXVECTOR3 Dir, D3DXCOLOR Diffuse);
D3DLIGHT9* GetLight();
#endif