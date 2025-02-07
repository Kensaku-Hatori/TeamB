//=======================================================
// 
// �U������[guide.h]
// Author:Rio Ohno
// 
//=======================================================

#ifndef GUIDE_H_
#define GUIDE_H_

#include "main.h"

//�}�N����`
#define GUIDE_WIDTH (float)(10.0f)
#define GUIDE_HEIGHT (float)(40.0f)
#define GUIDE_RADIUS (float)(25.0f)

//circle
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	LPDIRECT3DINDEXBUFFER9 IndxBuff;
}Circle;

//arrow
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
}Arrow;

//�U���\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	bool bUse;
}Guide;

//�v���g�^�C�v�錾
void InitGuide();
void UninitGuide();
void UpdateGuide();
void DrawGuide();
void SetGuide();

#endif // !GUIDE_H_
