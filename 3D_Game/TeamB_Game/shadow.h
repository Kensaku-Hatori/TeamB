//================================
//
// �e�\������[shadow.h]
// Author:kaiti
//
//================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

#define MAX_SHADOW (128)

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	bool bUse;
}Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos,bool bUse);
Shadow* GetShadow(void);

#endif