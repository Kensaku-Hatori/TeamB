#ifndef _BOSSNAMEEFFECT_H_
#define _BOSSNAMEEFFECT_H_

#include "main.h"

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 Buff;
	LPDIRECT3DTEXTURE9 Tex;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Rot;
	D3DXVECTOR2 Scale;
	D3DXCOLOR Col;
	float fAngle;
	float Length;
	int nLife;
	bool bUse;
}BOSSNAMEEFFECT;

void InitBossNameEffect();
void UninitBossNameEffect();
void UpdateBossNameEffect();
void DrawBossNameEffect();
void SetBossNameEffect(D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,D3DXVECTOR2 Scale,D3DXCOLOR Col,int nLife);
#endif // !_BOSSNAMEEFFECT_H_