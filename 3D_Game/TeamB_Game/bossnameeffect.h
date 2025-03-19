//*********************************************************
// 
// �{�X���[�r�[�̖��O[bossnameeffect.h]
// Author:Hatori
// 
//*********************************************************

#ifndef _BOSSNAMEEFFECT_H_
#define _BOSSNAMEEFFECT_H_

#include "main.h"
#define FADE_TIME (float)(120)

// �{�X���[�r�[�̖��O�̃t�F�[�h���
typedef enum
{
	NAMEFADE_NONE = 0,
	NAMEFADE_IN,
	NAMEFADE_OUT,
	NAMEFADE_MAX
}NAMEFADE;

// �{�X���[�r�[�̖��O�̍\����
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 Buff;
	LPDIRECT3DTEXTURE9 Tex;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Rot;
	D3DXVECTOR2 Scale;
	D3DXCOLOR Col;
	NAMEFADE Fade;
	float fAngle;
	float Length;
	int nLife;
	int FadeCounter;
	bool bUse;
}BOSSNAMEEFFECT;

//*****************
// �v���g�^�C�v�錾
//*****************
void InitBossNameEffect();
void UninitBossNameEffect();
void UpdateBossNameEffect();
void DrawBossNameEffect();
void SetBossNameEffect(D3DXVECTOR3 Pos,D3DXVECTOR3 Rot,D3DXVECTOR2 Scale,D3DXCOLOR Col,int nLife);
#endif // !_BOSSNAMEEFFECT_H_