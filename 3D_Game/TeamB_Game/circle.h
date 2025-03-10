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
#define MAX_CIRCLE (10)

//�A�j���[�V�����^�C�v
typedef enum
{
	ANIMETYPE_0 = 0,
	ANIMETYPE_MAX
}ANIMETYPE;

//�A�j���֌W
typedef struct
{
	bool bHalf;
}ANIME;

//circle
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	D3DXCOLOR AddCol;
	D3DXMATRIX mtxWorld;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 IndxBuff;
	LPDIRECT3DTEXTURE9 tex;
	ANIMETYPE type;
	ANIME Anime;
	int nDiviX;
	int nDiviY;
	int nMaxVtx;
	int nPolyNum;
	int frame;
	int nCntFrame;
	float fHeight;
	float fRadius;
	bool bGradation;
	bool bAnime;
	bool bUse;
}Circle;

//�v���g�^�C�v�錾
void InitCircle();
void UninitCircle();
void UpdateCircle();
void DrawCircle();
int SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int DiviX, int DiviY, float fHeight, float fRadius, bool bGradation, bool bAnime, int type);
void SetPositionCircle(int indx, D3DXVECTOR3  pos, D3DXVECTOR3 rot);
void SetAnime(int indx, ANIMETYPE type, int frame);
void DefAlpha(int indx, int frame);
void DeleteCircle(int indx);
#endif // !CIRCLE_H_

