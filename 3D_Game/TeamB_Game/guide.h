//=======================================================
// 
// 誘導する[guide.h]
// Author:Rio Ohno
// 
//=======================================================

#ifndef GUIDE_H_
#define GUIDE_H_

#include "main.h"

//マクロ定義
#define GUIDE_WIDTH (float)(10.0f)
#define GUIDE_HEIGHT (float)(40.0f)
#define GUIDE_RADIUS (float)(25.0f)


//誘導構造体
typedef struct
{
	D3DXVECTOR3 Destpos;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Guide;

//プロトタイプ宣言
void InitGuide();
void UninitGuide();
void UpdateGuide();
void DrawGuide();
void SetGuide();

#endif // !GUIDE_H_
