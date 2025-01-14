//================================
//
// �r���{�[�h����[Explosion.h]
// Author:kaiti
//
//================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

#define MAX_EXPLOSION (128)

//�r���{�[�h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	int nCounterAnim;
	int nPattemAnim;
	bool bUse;
}Explosion;

//�v���g�^�C�v�錾
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 dir);

#endif