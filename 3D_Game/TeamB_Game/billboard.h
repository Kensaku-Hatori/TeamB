//================================
//
// �r���{�[�h����[Biillboard.h]
// Author:kaiti
//
//================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

#define MAX_BILLBOARD (10)

//�r���{�[�h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	bool bUse;
}Biillboard;

//�v���g�^�C�v�錾
void InitBiillboard(void);
void UninitBiillboard(void);
void UpdateBiillboard(void);
void DrawBiillboard(void);
void SetBiillboard(D3DXVECTOR3 pos);

#endif