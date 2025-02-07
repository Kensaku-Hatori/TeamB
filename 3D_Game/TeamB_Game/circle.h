//=======================================================
// 
// �T�[�N��[circle.h]
// Author:Rio Ohno
// 
//=======================================================

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "main.h"

//�}�N����`
#define MAX_CIRCLE (1)

//circle
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	LPDIRECT3DINDEXBUFFER9 IndxBuff;
	float fRadius;
	bool bAnime;
	bool bUse;
}Circle;

//�v���g�^�C�v�錾
void InitCircle();
void UninitCircle();
void UpdateCircle();
void DrawCircle();
void SetCircle();

#endif // !CIRCLE_H_

