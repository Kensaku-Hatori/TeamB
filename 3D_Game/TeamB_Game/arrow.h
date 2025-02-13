//=======================================================
// 
// ���[arrow.h]
// Author:Rio Ohno
// 
//=======================================================

#ifndef ARROW_H_
#define ARROW_H_

#include "main.h"

//�}�N����`
#define ARROW_TEX "data\\TEXTURE\\sirusi.png"					//���̃e�N�X�`���p�X

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

//�v���g�^�C�v�錾
void InitArrow();
void UninitArrow();
void UpdateArrow();
void DrawArrow();
void SetArrow(D3DXVECTOR3 DestPos, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, float fRadius, bool bAnim);
void SetPositonArrow(D3DXVECTOR3 pos);
viod TrackingArrow();

#endif // !ARROW_H_
